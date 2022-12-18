#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    shared_ptr<region> s(new region(100,100,1.1));
    region = make_shared<Region>(ui->widget->height(),ui->widget->width(),1.);
    region->setupRegion(-1,1.9);
    ui->widget->setRegion(region);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, ui->widget, &Draw::animate);

    compute = true;
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
    exit(0);
}

// main -------------------------------------------------------

void MainWindow::simulate()
{
    if (!ui->widget->region->paused)
        ui->widget->region->fluid->simulate(ui->widget->region->dt, ui->widget->region->gravity, ui->widget->region->numIters);
    ui->widget->region->frameNr++;
}

void MainWindow::update()
{
    simulate();
    //    draw();
    //requestAnimationFrame(update());
}

void MainWindow::on_pushButton_clicked()
{
    int regionNr = ui->comboBox->currentIndex();
    ui->widget->region->showStreamlines = ui->checkBox_streamlines->isChecked();
    ui->widget->region->showVelocityVectors = ui->checkBox_velocityVectors->isChecked();
    ui->widget->region->showTracer= ui->checkBox_tracer->isChecked();
    ui->widget->region->overRelaxation = ui->lineEdit_overrelaxation->text().toDouble();
    ui->widget->region->resolution = ui->lineEdit_resolution->text().toInt();
    ui->widget->region->fluid->density = ui->lineEdit_density->text().toDouble();
    ui->widget->region->showObstaclePosition = ui->checkBox_objectposition->isChecked();

    ui->widget->region->updateRegionSize(ui->widget->height(),ui->widget->width());

    if(compute)
    {
        timer->start(1);
        ui->widget->region->setupRegion(regionNr, ui->widget->region->overRelaxation,ui->widget->region->resolution,ui->widget->region->fluid->density);

        ui->checkBox_streamlines->setChecked(ui->widget->region->showStreamlines);
        ui->checkBox_velocityVectors->setChecked(ui->widget->region->showVelocityVectors);
        ui->checkBox_tracer->setChecked(ui->widget->region->showTracer);
        ui->checkBox_objectposition->setChecked(ui->widget->region->showObstaclePosition);

        compute=false;
        //        ui->widget->region->paused=false;
        ui->pushButton->setText("Stop");
        ui->widget->region->paused = false;
        ui->checkBox_pause->setChecked(false);
        update();
        //setToolTip(ui->comboBox->currentText());
    }
    else
    {
        timer->stop();
        //        ui->widget->region->paused=true;
        compute=true;
        ui->pushButton->setText("Run");
        ui->widget->region->paused = true;
        ui->checkBox_pause->setChecked(false);
        update();
    }
    update();
}

void MainWindow::on_checkBox_streamlines_clicked(bool checked)
{
    ui->widget->region->showStreamlines = checked;
}


void MainWindow::on_checkBox_overrelaxation_clicked(bool checked)
{
    ui->widget->region->overRelaxation = (!checked)?1.0:ui->lineEdit_overrelaxation->text().toDouble();
}


void MainWindow::on_checkBox_pause_clicked(bool checked)
{
    ui->widget->region->paused = checked;
}


void MainWindow::on_checkBox_velocityVectors_clicked(bool checked)
{
    ui->widget->region->showVelocityVectors = checked;
}


void MainWindow::on_checkBox_tracer_clicked(bool checked)
{
    ui->widget->region->showTracer = checked;
}


void MainWindow::on_checkBox_objectposition_clicked(bool checked)
{
    ui->widget->region->showObstaclePosition= checked;
}

void MainWindow::on_comboBox_scalars_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0: // no selection
    {
        ui->widget->region->showPressure = false;
        ui->widget->region->showVelocity = false;
        ui->widget->region->showXVelocity = false;
        ui->widget->region->showYVelocity = false;
        break;
    }
    case 1: // pressure
    {
        ui->widget->region->showPressure = true;
        ui->widget->region->showVelocity = false;
        ui->widget->region->showXVelocity = false;
        ui->widget->region->showYVelocity = false;
        break;
    }
    case 2: // velocity magnitude
    {
        ui->widget->region->showPressure = false;
        ui->widget->region->showVelocity = true;
        ui->widget->region->showXVelocity = false;
        ui->widget->region->showYVelocity = false;
        break;
    }
    case 3: // x-velocity
    {
        ui->widget->region->showPressure = false;
        ui->widget->region->showVelocity = false;
        ui->widget->region->showXVelocity = true;
        ui->widget->region->showYVelocity = false;
        break;
    }
    case 4: // y-velocity
    {
        ui->widget->region->showPressure = false;
        ui->widget->region->showVelocity = false;
        ui->widget->region->showXVelocity = false;
        ui->widget->region->showYVelocity = true;
        break;
    }
    }
}


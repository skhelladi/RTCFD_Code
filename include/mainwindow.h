#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>
#include "region.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void simulate();
    void update();
    shared_ptr<Region> region;

private slots:
    void on_pushButton_clicked();

    void on_checkBox_velocities_clicked(bool checked);

    void on_checkBox_streamlines_clicked(bool checked);

    void on_checkBox_pressure_clicked(bool checked);

    void on_checkBox_overrelaxation_clicked(bool checked);

    void on_checkBox_pause_clicked(bool checked);

    void on_checkBox_velocityVectors_clicked(bool checked);

    void on_checkBox_tracer_clicked(bool checked);

    void on_checkBox_objectposition_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    bool compute;
};
#endif // MAINWINDOW_H

cmake_minimum_required(VERSION 3.5)

project(RTCFD_Code VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_DIR "/opt/Qt/5.15.2/gcc_64/lib/cmake/Qt5")
set(CMAKE_PREFIX_PATH "/opt/Qt/5.15.2/gcc_64")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
#find_package(Qt5 COMPONENTS Gui REQUIRED)
#target_link_libraries(mytarget Qt5::Gui)

# OpenMP
FIND_PACKAGE(OpenMP REQUIRED)

if(OPENMP_FOUND)
    message("OpenMP found")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


include_directories("${PROJECT_SOURCE_DIR}/include")

#set(TS_FILES RTCFD_Code_en_US.ts)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        include/mainwindow.h
        src/mainwindow.ui
        src/fluid.cpp
        include/fluid.h
        src/region.cpp
        include/region.h
        src/draw.cpp
        include/draw.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RTCFD_Code
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET RTCFD_Code APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
   if(ANDROID)
       add_library(RTCFD_Code SHARED
           ${PROJECT_SOURCES}
       )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
   else()
       add_executable(RTCFD_Code
           ${PROJECT_SOURCES}
       )
   endif()

endif()

target_link_libraries(RTCFD_Code PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui -O3 -fopenmp)

set_target_properties(RTCFD_Code PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS RTCFD_Code
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RTCFD_Code)
endif()

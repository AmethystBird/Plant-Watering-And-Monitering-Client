cmake_minimum_required(VERSION 3.5)

project(PlantWateringAndMonitoringSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Azure IoT SDK C settings
#set(use_mqtt ON CACHE  BOOL "Set mqtt on" FORCE )
#set(skip_samples ON CACHE  BOOL "Set slip_samples on" FORCE )
#set(BUILD_TESTING OFF CACHE  BOOL "Set BUILD_TESTING off" FORCE )

# Add Azure IoT SDK C
#add_subdirectory(azure-iot-sdk-c out)

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Mqtt)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Mqtt Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Mqtt Network)
#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Mqtt)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Charts)           #ADDED THIS
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Charts)      #ADDED THIS
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)             #ADDED THIS
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)        #ADDED THIS
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui)              #ADDED THIS
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)         #ADDED THIS

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

#Conditionally use the SDK trusted certs in the samples
#if(${use_sample_trusted_cert})
#    add_definitions(-DSET_TRUSTED_CERT_IN_SAMPLES)
#    include_directories(${PROJECT_SOURCE_DIR}/certs)
#    set(iothub_c_files ${iothub_c_files} ${PROJECT_SOURCE_DIR}/certs/certs.c)
#endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PlantWateringAndMonitoringSystem
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PlantWateringAndMonitoringSystem APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PlantWateringAndMonitoringSystem SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PlantWateringAndMonitoringSystem
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(PlantWateringAndMonitoringSystem PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries(PlantWateringAndMonitoringSystem PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Mqtt)
target_link_libraries(
    PlantWateringAndMonitoringSystem PUBLIC
    Qt${QT_VERSION_MAJOR}::Charts   #ADDED THIS
    Qt${QT_VERSION_MAJOR}::Core     #ADDED THIS
    Qt${QT_VERSION_MAJOR}::Gui      #ADDED THIS
    Qt${QT_VERSION_MAJOR}::Mqtt
    Qt${QT_VERSION_MAJOR}::Network
)

set_target_properties(PlantWateringAndMonitoringSystem PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS PlantWateringAndMonitoringSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PlantWateringAndMonitoringSystem)
endif()

cmake_minimum_required(VERSION 3.6)
project(GUI)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES    main.cpp
                    mainwindow.cpp
                    cardinformationwindow.cpp
                    eventhandler.cpp
                    src/Calculator.cpp
                    src/CardInformation.hpp
        )
add_executable(GUI ${SOURCE_FILES})

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

qt5_use_modules(GUI Core Widgets Gui)
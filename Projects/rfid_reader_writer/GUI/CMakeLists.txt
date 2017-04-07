cmake_minimum_required(VERSION 3.6)
project(GUI)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)


set(SOURCE_FILES
                    main.cpp
                    mainwindow.cpp
                    cardinformationwindow.cpp
                    eventhandler.cpp
                    src/Calculator.cpp
                    src/CardInformation.hpp src/LogFile.cpp)
set(TESTCALCULATOR_FILES
                    src/Calculator.cpp
                    src/CardInformation.hpp
                    src/Tester/TestCalculator.cpp
                    src/Tester/TestCards.h )
set(TESTEVENTHANDLER_FILES
                    eventhandler.cpp
                    src/Calculator.cpp
                    src/Tester/TestCards.h
                    src/Tester/TestEventhandler.cpp
                    )

set(TESTLOGFILE_FILES
                    src/LogFile.cpp
                    src/Tester/TestLogFile.cpp
                    src/Calculator.cpp)
set(TESTJOBFILE_FILES
                    src/Calculator.cpp
                    src/JobFile.cpp
                    src/Tester/TestJobFile.cpp)


find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(GUI ${SOURCE_FILES})

add_executable(CalculatorTest ${TESTCALCULATOR_FILES})
target_link_libraries(CalculatorTest /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so)
set_target_properties(CalculatorTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY testBin)
add_test(NAME CalculatorTestRofl WORKING_DIRECTORY testBin
                             COMMAND testBin/Calculator)

add_executable( EventHandlerTest ${TESTEVENTHANDLER_FILES})
target_link_libraries(EventHandlerTest /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so)
set_target_properties(EventHandlerTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY testBin)
add_test(NAME EventHandlerTest WORKING_DIRECTORY testBin
                              COMMAND testBin/EventHandlerTest)

add_executable( LogfileTest ${TESTLOGFILE_FILES})
target_link_libraries(LogfileTest /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so)
set_target_properties(LogfileTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY testBin)
add_test(NAME LogfileTest WORKING_DIRECTORY testBin
        COMMAND testBin/LogfileTest)

add_executable( JobFileTest ${TESTJOBFILE_FILES})
target_link_libraries( JobFileTest /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so)
set_target_properties( JobFileTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY testBin)
add_test(NAME JobFileTest WORKING_DIRECTORY testBin
        COMMAND testBin/JobFileTest)


##Setup CMake to run tests
#enable_testing()
#
##Prep ourselves for compiling boost
#find_package(Boost COMPONENTS unit_test_framework REQUIRED)
#include_directories (${Boost_INCLUDE_DIRS})
#
##I like to keep test files in a separate source directory called test
#file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/Tester/*.cpp)
#foreach(testSrc ${TEST_SRCS})
#    #Extract the filename without an extension (NAME_WE)
#    get_filename_component(testName ${testSrc} NAME_WE)
#
#    #Add compile target
#    add_executable(${testName} ${testSrc})
#
#    #link to Boost libraries AND your targets and dependencies
#    target_link_libraries(${testName} ${Boost_LIBRARIES} [YOUR TARGETS/LIBRARIES])
#
#    #I like to move testing binaries into a testBin directory
#    set_target_properties(${testName} PROPERTIES
#            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/testBin)
#
#    #Finally add it to test execution -
#    #Notice the WORKING_DIRECTORY and COMMAND
#    add_test(NAME ${testName}
#            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin
#            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )
#endforeach(testSrc)




qt5_use_modules(GUI Core Widgets Gui)
qt5_use_modules(CalculatorTest Core)
qt5_use_modules(EventHandlerTest Core Widgets)
qt5_use_modules(LogfileTest Core )
qt5_use_modules(JobFileTest Core )


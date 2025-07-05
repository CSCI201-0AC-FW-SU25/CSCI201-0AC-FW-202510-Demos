cmake_minimum_required(VERSION 3.10)

# set the project name
project(Test)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(student SHARED ../07_02_25/clock.cpp) #add the name of your cpp file in front of the .cpp and after the / on this line
#if you are testing more than 1 class copy the line above and change student to another name
 
# Link runTests with what we want to test and the GTest and pthread library

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -Wl,--wrap=main")


add_executable(runTests tests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} student pthread) #add the library names you created above for any additional classes after student on this line

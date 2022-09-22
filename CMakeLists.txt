cmake_minimum_required(VERSION 3.1)

project(DriverDevTutorial VERSION 0.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)
set(ENV{PROJECT_ROOT_DIRECTORY} ${PROJECT_SOURCE_DIR}/../)
set(CMAKE_CXX_STANDARD 11)

set(dependecies main.cpp)

add_subdirectory(devices)
add_subdirectory(drivers)
set(libraries devices
    drivers)

add_executable(badgerloop ${dependecies})
target_link_libraries(badgerloop PRIVATE ${libraries})


# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name and language
project(Project1_YZ CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the output directories for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Can automatically find and configure OpenCV or other libraries if needed
find_package(OpenCV REQUIRED)

# Add both vidDisplay.cpp and filters.cpp to the executable
#add_executable(Project1_YZ ./src/vidDisplay.cpp ./src/filter.cpp)
#add_executable(time_YZ ./src/timeBlur.cpp ./src/filter.cpp)
#add_executable(faceDetect_YZ ./src/faceDetect.cpp ./src/showFaces.cpp)
add_executable(Project1_YZ ./src/vidDisplay.cpp ./src/filter.cpp ./src/faceDetect.cpp)

# Link OpenCV libraries
target_link_libraries(Project1_YZ ${OpenCV_LIBS})
#target_link_libraries(time_YZ ${OpenCV_LIBS})
#target_link_libraries(faceDetect_YZ ${OpenCV_LIBS})


# Ensure the OpenCV include directories are available to all targets
include_directories(${OpenCV_INCLUDE_DIRS})
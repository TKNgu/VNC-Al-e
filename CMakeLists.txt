#Cmake version.
cmake_minimum_required (VERSION 3.10.2)

# C++ std 14.
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_EXE_LINKER_FLAGS "-no-pie")
set (CMAKE_EXE_LINKER_FLAGS)

# The Maxtrix
project (TheMatrix VERSION 1.0.0 LANGUAGES CXX C DESCRIPTION "Sample matrix")

# Source code
file (GLOB SRC src/*.cpp)

include_directories (
    src/
)

link_directories (
    lib/local/include/
)

# Build sample
add_executable (${CMAKE_PROJECT_NAME} ${SRC})
target_link_libraries (${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

# Run 
add_custom_target (run ${CMAKE_PROJECT_NAME}
    DEPENDS ${SAMPLE}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
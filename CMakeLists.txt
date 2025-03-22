cmake_minimum_required(VERSION 3.10)
project(SimulationProject)

set(CMAKE_CXX_STANDARD 17)

# Ensure CMake can find vcpkg libraries
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Locate MongoDB C++ libraries
find_package(bsoncxx REQUIRED CONFIG)
find_package(mongocxx REQUIRED CONFIG)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(Simulation ${SOURCES})

# Link MongoDB C++ driver
target_link_libraries(Simulation PRIVATE 
    $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>
    $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>
)
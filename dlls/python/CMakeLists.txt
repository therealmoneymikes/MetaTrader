cmake_minimum_required(VERSION 3.12)
project(priceplotdllapp)

# Set the C++ standard (pybind11 requires C++17 or later)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#CMP0148 Policy NEW - Due to the deprecation of FindPythonInterp and FindPython Libs modules
#This updates the code tp make sure we use FindPython instead
##If you need FindPythonInterp and FindPython Lib set CMP0148 to OLD
cmake_policy(SET CMP0148 NEW)


# Add the path to the pybind11 CMake configuration directory
set(pybind11_DIR "C:/Users/Michael Roberts/AppData/Local/Programs/Python/Python312/Lib/site-packages/pybind11/share/cmake/pybind11")

# Find pybind11 (must use the correct directory for pybind11Config.cmake)
find_package(pybind11 REQUIRED)

# Add the Python interpreter and development files
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Include necessary directories
include_directories(
    ${Python3_INCLUDE_DIRS}          # Include Python headers
    ${CMAKE_CURRENT_SOURCE_DIR}      # Include the current directory
)

# Create the module out of the DLL cpp wrapper file priceplotwrapper to target with pybind11
##This will create python shared library (.pyd for windows, .so Mac/Linux)
pybind11_add_module(priceplotdll priceplotwrapper.cpp)

# Link the Python libraries
target_link_libraries(priceplotdll PRIVATE Python3::Python)
target_include_directories(priceplotdll PRIVATE "C:/Users/Michael Roberts/AppData/Local/Programs/Python/Python312/Lib/site-packages/pybind11/include")

# Set the DLL output properties
set_target_properties(priceplotdll PROPERTIES
    OUTPUT_NAME "priceplotdll" # Name of the DLL
    PREFIX ""                  # Remove "lib" prefix on Windows
    SUFFIX ".dll"              # Ensure the output file is .dll
)

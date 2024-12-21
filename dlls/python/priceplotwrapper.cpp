
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <Python.h>
#include <pybind11/pybind11.h>

//C:\Users\Michael Roberts\AppData\Local\Programs\Python\Python312\Lib\site-packages\pybind11\include - pybind11.h
//C:\Users\Michael Roberts\AppData\Local\Programs\Python\Python312\include - Python.h
namespace py = pybind11;


std::string read_python_file(const std::string& file_path){
    std::ifstream file(file_path); //Create ifstream file variable to store the file path
    if(!file.is_open()){
        throw std::runtime_error("Error open the Python file: " + file_path);
    }

    std::stringstream file_buffer;//Create a buffer object
    file_buffer << file.rdbuf();
    return file_buffer.str();//Return the contents of the python file as a string

}

void execute_python_code(const py::error_already_set& error){
    try {
        py::exec(python_code); //This executes the python dll code directly
    } catch (const std::exception& error) {
        std::cerr << "Error executing Python DLL Code: " << error.what() << std::endl;
    }
}
//The first argument will be the name of module that import 
PYBIND11_MODULE(price_plot_dll_mod, m) {
    m.def("read_python_file", &read_python_file, "Read the contents of the Python file and returns its content as a string");
    m.def("execute_python_code", &execute_python_code, "Execute Python code from a string");
}
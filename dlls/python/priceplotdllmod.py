import price_plot_dll_mod



file_path = "priceplotdll.py" #The file is root of the python folder

# Call the read_python_file function from the priceplotwrapper file
python_code = price_plot_dll_mod.read_python_file(file_path)

# Call the execute Python code stored in the C++ wrapper
price_plot_dll_mod.execute_python_code(python_code)


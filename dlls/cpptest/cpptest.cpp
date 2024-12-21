#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


int main() {
    const std::string file_path = "C:/Users/Michael Roberts/Downloads/test.txt.txt";
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return 1;
    }
    std::cout << "File opened successfully.\n";
    std::stringstream file_buffer;
    file_buffer << file.rdbuf();
    std::cout << file_buffer.str();
    return 0;
}

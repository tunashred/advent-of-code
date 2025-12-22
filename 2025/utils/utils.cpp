#include <sstream>
#include <fstream>

#include "utils.hpp"

std::stringstream read_file(std::string_view file_name) {
    std::ifstream file{file_name.data(), std::ios::in};
    if (!file) {    
        throw std::runtime_error("Error opening file!");
    }

    file.seekg(0, std::ios::end);
    std::streamsize file_size = file.tellg();
    std::string temp_buffer(file_size, '\0');

    file.seekg(0, std::ios::beg);
    if (!file.read(temp_buffer.data(), file_size)) {
        throw std::runtime_error("Error reading file!");
    }

    std::stringstream stream(std::move(temp_buffer));

    file.close();
    return stream;
}

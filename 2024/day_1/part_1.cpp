#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string_view>
#include <cmath>

// TODO: move this to a utils dir inside 2024 dir
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

int main() {
    std::stringstream input{read_file("../../day_1/in.input")};

    std::vector<int> list_1, list_2;
    int num_1, num_2;
    std::string line;
    
    while (std::getline(input, line)) {
        std::stringstream line_stream(line);

        line_stream >> num_1 >> num_2;
        list_1.emplace_back(num_1);
        list_2.emplace_back(num_2);
    }

    sort(list_1.begin(), list_1.end());
    sort(list_2.begin(), list_2.end());

    int result = 0;
    for (int i = 0; i < list_1.size(); i++) {
        result += abs(list_1[i] - list_2[i]);
    }

    std::cout << result << '\n';

    return 0;
}

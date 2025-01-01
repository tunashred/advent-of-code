#include <iostream>
#include <fstream>
#include <regex>
#include <string>

std::tuple<int, int> extract_pair(std::string str) {
    int first, second;
    int i = 4;
    int start = i;
    
    while(str[i++] != ',') {}
    first = std::stoi(std::string(str.begin() + start, str.begin() + i));
    start = i;

    while(str[i++] != ')') {}
    second = std::stoi(std::string(str.begin() + start, str.begin() + i));

    return std::make_tuple(first, second);
}

int main() {
    std::ifstream file("../../day_3/in.input", std::ios::in | std::ios::binary | std::ios::ate);
    long result = 0;
    bool execute_instructions = true;

    if (!file) {
        std::cerr << "Couldn't open the file!" << '\n';
        return 1;
    }

    std::streamsize size = file.tellg();
    std::string buffer;
    buffer.resize(size);
    file.seekg(0, std::ios::beg);

    if (!file.read(buffer.data(), size)) {
        std::cerr << "Couldn't read file contents!" << '\n';
        return 1;
    }

    std::regex pattern(R"((don't)|(do)|(mul\([1-9][0-9]*,[1-9][0-9]*\)))");

    for (std::sregex_iterator it(buffer.begin(), buffer.end(), pattern), end_it; it != end_it; it++) {
        std::smatch match = *it;
        
        if (match[0].str() == "do") {
            execute_instructions = true;
        } else if (match[0].str() == "don't") {
            execute_instructions = false;
        } else {
            if (execute_instructions) {
                std::tuple<int, int> nums = extract_pair(match[0].str());
                result += std::get<0>(nums) * std::get<1>(nums);
            }
        }
    }

    std::cout << result << '\n';

    return 0;
}

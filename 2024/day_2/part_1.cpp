#include <iostream>
#include <sstream>

#include "utils.hpp"

int main() {
    std::stringstream stream{read_file("../../day_2/in.input")};
    std::string line;
    int result = 0;

    while (std::getline(stream, line)) {
        std::stringstream line_stream(line);
        int current, next;
        bool is_valid = true;
        bool increasing_order = true;

        line_stream >> current >> next;
        if (abs(current - next) > 3 || current == next) {
            continue;
        }
        if (current > next) {
            increasing_order = false;
        }
        current = next;
        
        while (line_stream >> next) {
            if (abs(current - next) > 3 || current == next) {
                is_valid = false;
                break;
            }
            if ((current < next && !increasing_order) || (current > next && increasing_order)) {
                is_valid = false;
                break;
            }
            current = next;
        }

        if (is_valid) {
            std::cout << line_stream.str() << "\n";
            result++;
        }
    }

    std::cout << result << '\n';

    return 0;
}

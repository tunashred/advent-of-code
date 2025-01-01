#include <iostream>
#include <sstream>
#include <vector>

#include "utils.hpp"

bool is_safe(std::vector<int>& level) {
    int current = level[0], next = level[1];
    bool is_valid = true;
    bool increasing_order = true;

    if (abs(current - next) > 3 || current == next) {
        return false;
    }
    if (current > next) {
        increasing_order = false;
    }
    current = next;

    for (int i = 2; i < level.size(); i++) {
        next = level[i];

        if (abs(current - next) > 3 || current == next) {
            return false;
        }
        if ((current < next && !increasing_order) || (current > next && increasing_order)) {
            return false;
        }
        current = next;
    }
    return true;
}

int main() {
    std::stringstream stream{read_file("../../day_2/in.input")};
    std::string line;
    int result = 0;
    std::vector<int> level;
    std::vector<int> maybe_fixed_level;

    while (std::getline(stream, line)) {
        std::stringstream line_stream(line);
        int num;

        while (line_stream >> num) {
            level.push_back(num);
        }

        if (!is_safe(level)) {
            for (int i = 0; i < level.size(); i++) {
                maybe_fixed_level.clear();
                for (int j = 0; j < level.size(); j++) {
                    if (j != i) {
                        maybe_fixed_level.push_back(level[j]);
                    }
                }
                if (is_safe(maybe_fixed_level)) {
                    result++;
                    break;
                }

            }
        } else {
            result++;
        }

        level.clear();
    }

    std::cout << result << '\n';

    return 0;
}

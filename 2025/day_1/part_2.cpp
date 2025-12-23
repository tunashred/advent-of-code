#include <iostream>
#include <sstream>

#include "utils.hpp"

int counter = 0;

int carried_add(int current_pos, int clicks) {
    counter += clicks / 100;
    clicks = clicks % 100;
    
    if (current_pos + clicks == 100) {
        counter++;
        return 0;
    } else if (current_pos + clicks <= 100) {
        return current_pos + clicks;
    }

    int res = clicks - (100 - current_pos);
    if (res == 0 || clicks > (100 - current_pos)) {
        counter++;
    }
    return res;
}

int carried_subtract(int current_pos, int clicks) {
    counter += clicks / 100;
    clicks = clicks % 100;
    if (clicks == 0) {
        return current_pos;
    }
    
    if (current_pos - clicks == 0) {
        counter++;
        return 0;
    } else if (current_pos - clicks >= 0) {
        return current_pos - clicks;
    }

    if (clicks > current_pos && current_pos != 0) {
        counter++;
    }
    clicks -= current_pos;
    int res = 100 - clicks;
    if (res == 0) {
        counter++;
    }
    return res;
}

int main() {
    std::stringstream stream{read_file("../../day_1/in.input")};
    std::string line;
    int current = 50;

    int left_clicks  = 0,
        right_clicks = 0;

    while (std::getline(stream, line)) {
        if (line[0] == 'L') {
            // substr vs string_view for converting to int
            left_clicks = std::stoi(line.substr(1, line.size() - 1));
            current = carried_subtract(current, left_clicks);
        } else if (line[0] == 'R') {
            right_clicks = std::stoi(line.substr(1, line.size() - 1));
            current = carried_add(current, right_clicks);
        } else {
            throw std::runtime_error("wtf is this?");
        }
    }

    std::cout << counter << '\n';

    return 0;
}

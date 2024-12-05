#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string_view>
#include <cmath>

#include "utils.hpp"

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

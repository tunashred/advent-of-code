#include <iostream>
#include <regex>

#include "utils.hpp"

bool has_odd_number_of_digits(const std::string& number) {
    return number.size() % 2;
}

std::tuple<long, long> bump_range(const std::tuple<long, long>& range) {
    std::string min_str = std::to_string(std::get<0>(range)),
                max_str = std::to_string(std::get<1>(range));

    if (min_str.size() >= max_str.size()) {
        return {0, 0}; // not sure if this is the way
    }

    min_str = "1" + std::string(min_str.size(), '0');

    if (has_odd_number_of_digits(min_str)) {
        std::tuple<long, long> new_range(std::stol(min_str), std::get<1>(range));
        return bump_range(new_range);
    }

    return {static_cast<long>(pow(10, min_str.size())),
            std::get<1>(range)};
}

std::tuple<long, long> extract_range(const std::string& range) {
    std::tuple<long, long> ret {0, 0};
    int i = 0;

    while (range[i++] != '-') { }
    std::string min_str = range.substr(0, i - 1);
    std::string max_str = range.substr(i, range.size());

    bool min_odd = has_odd_number_of_digits(min_str),
         max_odd = has_odd_number_of_digits(max_str);

    if (min_odd && max_odd) {
        return ret;
    }

    uint64_t min = std::stol(min_str),
             max = std::stol(max_str);
             
    std::get<0>(ret) = std::stol(min_str);
    std::get<1>(ret) = std::stol(max_str);

    if (min_odd) {
        std::get<0>(ret) = static_cast<long>(pow(10, min_str.size()));
    }
    if (max_odd) {
        max = std::stol(std::string(max_str.size() - 1, '9'));
        if (max < std::get<0>(ret)) {
            throw std::runtime_error("wtf");
        }
        std::get<1>(ret) = max;
    }

    return ret;
}

bool is_in_range(const uint64_t& num, const std::tuple<long, long>& range) {
    return num >= std::get<0>(range);
}

long sum_invalid_numbers(const std::string& range) {
    long min, max;
    std::tie(min, max) = extract_range(range);
    uint64_t sum = 0;

    while (min != 0 && max != 0) {
        std::string min_str = std::to_string(min),
                    max_str = std::to_string(max);
        
        std::string sequence_str = min_str.substr(0, min_str.size() / 2);
        std::string invalid_id = sequence_str + sequence_str;
        int sequence = std::stoi(sequence_str);

        while (std::stol(invalid_id) <= max) {
            
            if (is_in_range(std::stol(invalid_id), {min, max})) {
                sum += std::stol(invalid_id);
            }
            
            sequence++;
            sequence_str = std::to_string(sequence);
            invalid_id = sequence_str + sequence_str;
        }
        std::tie(min, max) = bump_range({min, max});
    }
    return sum;
}

int main() {
    std::stringstream stream{read_file("../../day_2/in.input")};
    std::string input(stream.rdbuf()->str());

    long result = 0;

    std::regex const expr{R"([0-9]*-[0-9]*)"};
    std::smatch matches;

    auto it = std::sregex_iterator(input.begin(), input.end(), expr);
    auto end = std::sregex_iterator();

    for (; it != end; it++) {
        auto match = *it;
        auto element = match[0].str();

        uint64_t left, right;
        std::tie(left, right) = extract_range(element);

        result += sum_invalid_numbers(element);
    }

    std:: cout << result << "\n";

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> digitWords {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

int getDigit(std::string_view line, int index) {
    if(isdigit(line[index])) {
        return line[index] - '0';
    }

    for(int i = 0; i < digitWords.size(); i++) {
        std::string &word = digitWords[i];

        if(line.substr(index, word.size()) == word) {
            return i;
        }
    }

    return -1;
}

int main() {
    std::ifstream myfile("../input.txt");
    std::string line;
    int sum = 0;

    while(getline(myfile, line)) {
        int digit, firstDigit = -1, lastDigit = -1;
        for(int i = 0; i < line.size(); i++) {
            digit = getDigit(line, i);

            if(digit == -1) {
                continue;
            }

            if(firstDigit == -1) {
                firstDigit = digit;
            }
            else {
                lastDigit = digit;
            }
        }

        if(lastDigit == -1) {
            lastDigit = firstDigit;
        }
        sum += firstDigit * 10 + lastDigit;
    }

    std::cout << sum << "\n";

    return 0;
}

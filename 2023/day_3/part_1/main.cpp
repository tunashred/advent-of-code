#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <set>

typedef struct RangeSet {
    std::vector<int> numbers;
    std::vector<std::pair<int, int>> numberRange;
    std::set<std::pair<int, int>> symbolPosition;

    void addNumber(int number, int from, int to) {
        numbers.push_back(number);
        numberRange.emplace_back(from, to);
    }

    void addSymbolPosition(int line, int position) {
        symbolPosition.insert(std::make_pair(line, position));
    }

    void loadNumber(std::string::iterator left, std::string::iterator right, const std::regex& rx) {
        if(left == right || left >= right) {
            std::cout << "Iterators are not valid for loading number.\n";
            return;
        }

        std::sregex_iterator it(left, right, rx);
        std::sregex_iterator end;

        while(it != end) {
            std::smatch match = *it;
            size_t firstPos = match.position();
            size_t lastPos = firstPos + match.length() - 1;

            int number = std::stoi(match.str());
            this->addNumber(number, firstPos, lastPos);

            it++;
        }
    }

    void loadSymbol(int lineNumber, std::string::iterator left, std::string::iterator right, const std::regex& rx) {
        if(left == right || left >= right) {
            std::cout << "Iterators are not valid for loading symbol.\n";
            return;
        }

        std::sregex_iterator it(left, right, rx);
        std::sregex_iterator end;

        while(it != end) {
            std::smatch match = *it;
            size_t pos = match.position();
            this->addSymbolPosition(lineNumber, pos);
            it++;
        }
    }

    void clearNums() {
        this->numbers.clear();
        this->numberRange.clear();
    }

    void clearSymbols(int currentLine) {
        std::vector<std::pair<int, int>> toClear;
        for(const auto &symPos : symbolPosition) {
            for(int i = 0; i < this->numbers.size(); i++) {
                if(symPos.first < currentLine - 1) {
                    toClear.push_back(symPos);
                    break;
                }
            }
        }
        for(auto const &pair : toClear) {
            this->symbolPosition.erase(pair);
        }
    }
} RangeSet;


int main() {
    std::ifstream myfile("../input.txt");
    std::regex rx_number("\\d+");
    std::regex rx_symbol("[^0-9A-Za-z.]");
    std::vector<int> validNums;

    RangeSet ranges;
    std::sregex_iterator end;
    int lineNumber = -1;

    while(myfile.good()) {
        std::string line1, line2;
        getline(myfile, line1);
        getline(myfile, line2);
        lineNumber++;

//        std::cout << "Line 1 is: " << line1 << "\n";
//        std::cout << "Line 2 is: " << line2 << "\n\n";

        ranges.loadNumber(line1.begin(), line1.end(), rx_number);

        ranges.loadSymbol(lineNumber, line1.begin(), line1.end(), rx_symbol);
        ranges.loadSymbol(lineNumber + 1, line2.begin(), line2.end(), rx_symbol);

        // loading into this array the valid numbers
        for(int i = 0; i < ranges.numbers.size(); i++) {
            for(const auto &pair : ranges.symbolPosition) {
                int symbolLine = pair.first;
                int pos = pair.second;

                if(ranges.numberRange[i].first - 1 <= pos
                && pos <= ranges.numberRange[i].second + 1
                && symbolLine + 1 >= lineNumber) {
                    validNums.push_back(ranges.numbers[i]);
                    break;
                }
            }
        }

//        for(auto pair : ranges.symbolPosition) {
//            std::cout << "Symbol found at line " << pair.first << ", position " << pair.second <<  "\n";
//        }

//        for(size_t i = 0; i < ranges.numbers.size(); i++) {
//            std::cout << "Number: " << ranges.numbers[i] << " from " << ranges.numberRange[i].first
//                                                                 << " to " << ranges.numberRange[i].second << "\n";
//        }
//        std::cout << "\n";

        // rewinding so as for the next getlines,
        // line1 becomes the former line2
        // and line2 becomes the upcoming line
        std::streamoff line2len = line2.length() + 1;
        myfile.seekg(-line2len, std::ios::cur);

        ranges.clearSymbols(lineNumber);
        ranges.clearNums();
    }

//    for(int x : validNums) {
//        std::cout << x << " ";
//    }
//    std::cout << "\n";

    size_t sum = 0;
    for(int num : validNums) {
        sum += num;
    }
    std::cout << sum;

    myfile.close();
    return 0;
}

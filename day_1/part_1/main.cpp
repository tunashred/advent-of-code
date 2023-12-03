#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream myfile("../input.txt");
    std::string buffer;
    int i, j;
    int firstDigit, lastDigit;
    int sum = 0;
    while(getline(myfile, buffer)) {
        i = 0;
        j = (int) buffer.size() - 1;
        firstDigit = 0;
        lastDigit = 0;

        while(!firstDigit || !lastDigit) {
            if(isdigit(buffer[i]) && !firstDigit) {
                firstDigit = buffer[i] - '0';
            }
            else {
                i++;
            }

            if(isdigit(buffer[j]) && !lastDigit) {
                lastDigit = buffer[j] - '0';
            }
            else {
                j--;
            }
        }
        sum += firstDigit * 10 + lastDigit;
    }

    std::cout << sum << "\n";
    return 0;
}

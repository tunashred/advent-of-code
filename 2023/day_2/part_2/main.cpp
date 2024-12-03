#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main() {
    int maxRed = -69, maxGreen = -420, maxBlue = -1337;
    int ans = 0;

    std::ifstream myfile("../input.txt");
    std::string line;
    std::string token;

    while(getline(myfile, line)) {
        std::istringstream games(line);

        while(getline(games, token, ' ')) {
            int cubes = stoi(token.substr(0, token.size() - 1));

            switch(token.back()) {
                case 'r':
                    if(cubes > maxRed) {
                        maxRed = cubes;
                    }
                    break;

                case 'g':
                    if(cubes > maxGreen) {
                        maxGreen = cubes;
                    }
                    break;

                case 'b':
                    if(cubes > maxBlue) {
                        maxBlue = cubes;
                    }
                    break;

                default:
                    break;
            }
        }
        ans += maxRed * maxGreen * maxBlue;
        maxRed = maxGreen = maxBlue = -69;
    }

    std::cout << ans << "\n";

    return 0;
}

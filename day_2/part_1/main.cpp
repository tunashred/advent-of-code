#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main() {
    int maxRed = 12, maxGreen = 13, maxBlue = 14;
    int ans = 0;
    int gameID = 1;
    bool isValid = true;

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
                        isValid = false;
                    }
                    break;

                case 'g':
                    if(cubes > maxGreen) {
                        isValid = false;
                    }
                    break;

                case 'b':
                    if(cubes > maxBlue) {
                        isValid = false;
                    }
                    break;

                default:
                    break;
            }
            if(!isValid) {
                break;
            }
        }
        if(isValid) {
            ans += gameID;
        }
        gameID++;
        isValid = true;
    }

    std::cout << ans << "\n";
    
    return 0;
}

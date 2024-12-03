#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>

int main() {
    std::ifstream myfile("../input.txt");
    int aux;
    std::vector<int> winnerNums;
    std::vector<int> myNums;
    int sum = 0;
    std::string line;

    while(getline(myfile, line)) {
        size_t pipePos = line.find('|');

        std::istringstream iss(line.substr(0, pipePos));
        while(iss >> aux) {
            winnerNums.push_back(aux);
        }

        // gotta do this cuz it does not work otherwise for me ;/
        iss.clear();
        iss.seekg(0);
        iss.str(line.substr(pipePos + 1));

        while(iss >> aux) {
            myNums.push_back(aux);
        }

        sort(myNums.begin(), myNums.end());
        sort(winnerNums.begin(), winnerNums.end());
        // storing the common elements in a vector
        std::vector<int> myWinnerNums( std::min(myNums.size(), winnerNums.size()) );
        auto st = std::set_intersection(winnerNums.begin(), winnerNums.end(),
                                                myNums.begin(), myNums.end(), myWinnerNums.begin());

        // getting rid of duplicates using std::set
        std::set<int> unique_myWinnerNums;
        unsigned size = std::distance(myWinnerNums.begin(), st); // does not work with just myWinnerNums.size()
        for(int i = 0; i < size; i++) {
            unique_myWinnerNums.insert(myWinnerNums[i]);
        }
        // moving them back into my vector to finish my job
        myWinnerNums.assign(unique_myWinnerNums.begin(), unique_myWinnerNums.end());

        float gamePoints = 0.5;
        st = myWinnerNums.begin();
        while(st != myWinnerNums.end()) {
            gamePoints *= 2;
            st++;
        }

        sum += gamePoints;

        winnerNums.clear();
        myNums.clear();
    }

    myfile.close();
    return 0;
}

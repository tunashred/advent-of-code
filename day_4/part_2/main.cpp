#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
#include <numeric>

int main() {
    std::ifstream myfile("../input.txt");
    int aux;
    std::vector<int> winnerNums;
    std::vector<int> myNums;
    std::string line;
    unsigned cardIndex = 1;
    int totalCards;

    // counting the lines from the file to find the initial numbers of cards
    unsigned givenCards = std::count(std::istreambuf_iterator<char>(myfile),
                                     std::istreambuf_iterator<char>(), '\n');
    myfile.seekg(0);
    // using this vector to count the stratch cards copies
    std::vector<int> cards(givenCards, 1);

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

        int wonCards = myWinnerNums.size();

        auto left = cards.begin() + cardIndex;
        auto right = cards.begin() + cardIndex;
        if(cardIndex + wonCards < givenCards) {
            right += wonCards;
        }
        else {
            right = cards.end();
        }
        
        int current_copies = cards[cardIndex - 1];
        std::for_each(left, right, [current_copies](int &n) {n += current_copies; });

        cardIndex++;
        winnerNums.clear();
        myNums.clear();
    }

    totalCards = std::accumulate(cards.begin(), cards.end(), 0);
    std::cout << totalCards << "\n";
    
    myfile.close();
    return 0;
}

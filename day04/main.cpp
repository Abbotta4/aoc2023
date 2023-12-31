#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <regex>
#include <cmath>
#include <numeric>

std::vector<std::string> readInput(std::string const& fileName) {
    std::vector<std::string> input;
    std::string tmp;
    std::ifstream file;
    file.open(fileName);
    while (file) {
        std::getline(file, tmp);
        input.push_back(tmp);
    }
    file.close();
    input.pop_back(); // remove empty line at end
    return input;
}

int getMatches(std::string const& card) {
    std::regex cre("Card [0-9 ]+: ([0-9 ]+)\\| ([0-9 ]+)");
    std::regex nre("[0-9]+");

    std::smatch sm;
    std::regex_search(card, sm, cre);
    std::string lnumbers = sm[1];
    std::string rnumbers = sm[2];
    
    std::sregex_token_iterator tok(lnumbers.begin(), lnumbers.end(), nre, 0);
    std::set<int> winningNumbers;
    while (tok != std::sregex_token_iterator()) {
        winningNumbers.insert(std::stoi(*tok));
        ++tok;
    }
    tok = std::sregex_token_iterator(rnumbers.begin(), rnumbers.end(), nre, 0);
    std::set<int> playerNumbers;
    while (tok != std::sregex_token_iterator()) {
        playerNumbers.insert(std::stoi(*tok));
        ++tok;
    }

    std::vector<int> matches;
    std::set_intersection(winningNumbers.begin(), winningNumbers.end(),
                          playerNumbers.begin(), playerNumbers.end(),
                          std::back_inserter(matches));

    return matches.size();

}

int main() {
    auto cards = readInput("input.txt");
    int sum = 0;
    for (auto card: cards) {
        int matches = getMatches(card);
        sum += matches > 0 ? std::pow(2, matches-1) : 0;
    }
    std::cout << sum << std::endl;

    std::map<int, int> copies;
    for (int i = 0; i < cards.size(); ++i)
        copies[i] = 1;
    for (int i = 0; i < cards.size(); ++i) {
        int matches = getMatches(cards[i]);
        for (int j = 1; j <= matches; ++j) {
            copies[i+j] += copies[i];
        }            
    }

    sum = std::accumulate(copies.begin(), copies.end(), 0, [](int a, std::pair<int,int> b){ return a + b.second; });
    std::cout << sum << std::endl;

    return 0;
}

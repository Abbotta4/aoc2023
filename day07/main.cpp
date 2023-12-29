#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <set>
#include <algorithm>
#include <cctype>
#include <utility>

std::vector<std::string> readInput(std::string const& fileName) {
    std::vector<std::string> input;
    std::string tmp;
    std::ifstream file;
    file.open(fileName);
    while (std::getline(file, tmp))
        input.push_back(tmp);
    file.close();
    return input;
}

bool isXOfAKind(std::string const& hand, int x, bool jokers) {
    std::set<char> s;
    for (char c: hand)
        s.insert(c);
    for (char c: s) {
        if (std::count(hand.begin(), hand.end(), c) + (jokers && c != 'J' ? std::count(hand.begin(), hand.end(), 'J') : 0) == x)
            return true;
    }
    return false;
}

bool isFullHouse(std::string const& hand, bool jokers) {
    std::set<char> s;
    for (char c: hand)
        s.insert(c);
    return s.size() == (2 + (jokers && s.contains('J') ? 1 : 0)) && isXOfAKind(hand, 3, jokers) && !isXOfAKind(hand, 4, jokers);
}

bool isTwoPair(std::string const& hand, bool jokers) {
    std::set<char> s;
    for (char c: hand)
        s.insert(c);
    return s.size() == (3 + (jokers && s.contains('J') ? 1 : 0)) && !isXOfAKind(hand, 3, jokers);
}

int getHandStrength(std::string const& hand, bool jokers) {
    if (isXOfAKind(hand, 5, jokers))
        return 7;
    else if (isXOfAKind(hand, 4, jokers))
        return 6;
    else if (isFullHouse(hand, jokers))
        return 5;
    else if (isXOfAKind(hand, 3, jokers))
        return 4;
    else if (isTwoPair(hand, jokers))
        return 3;
    else if (isXOfAKind(hand, 2, jokers))
        return 2;
    return 1;
}

int getCardStrength(char const& card, bool jokers) {
    switch (card) {
    case 'A':
        return 14;
    case 'K':
        return 13;
    case 'Q':
        return 12;
    case 'J':
        return jokers ? 1 : 11;
    case 'T':
        return 10;
    }
    return static_cast<int>(card) - '0';
}

bool compareHands(std::string const& first, std::string const& second, bool jokers) {
    int firstHandStrength = getHandStrength(first, jokers);
    int secondHandStrength = getHandStrength(second, jokers);

    if (firstHandStrength == secondHandStrength) {
        for (int card = 0; card < 5; ++card) {
            int firstCardStrength = getCardStrength(first[card], jokers);
            int secondCardStrength = getCardStrength(second[card], jokers);
            if (firstCardStrength != secondCardStrength)
                return firstCardStrength < secondCardStrength;
        }
        return false;
    }
    return firstHandStrength < secondHandStrength;
}

std::vector<std::pair<std::string, int>> getHands(std::vector<std::string> input) {
    std::vector<std::pair<std::string, int>> ret;
    std::regex const r("([2-9TJQKA]{5}) ([0-9]+)");
    for (auto hand: input) {
        std::smatch m;
        std::regex_match(hand, m, r);
        ret.push_back(std::pair(m[1], std::stoi(m[2])));
    }
    return ret;
}

int getWinnings(std::vector<std::pair<std::string, int>> hands) {
    int winnings = 0;
    for (int i = 0; i < hands.size(); ++i)
        winnings += (i + 1) * hands[i].second;
    return winnings;
}

int main() {
    auto hands = getHands(readInput("input.txt"));

    std::sort(hands.begin(), hands.end(), [](auto a, auto b){ return compareHands(a.first, b.first, false); });
    std::cout << getWinnings(hands) << std::endl;

    std::sort(hands.begin(), hands.end(), [](auto a, auto b){ return compareHands(a.first, b.first, true); });
    std::cout << getWinnings(hands) << std::endl;

    return 0;
}

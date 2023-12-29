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

bool isFiveOfAKind(std::string const& hand) {
    std::set<char> s;
    for (char c: hand)
        s.insert(c);
    return s.size() == 1;
}

bool isFourOfAKind(std::string const& hand) {
    std::set<char> s;
    for (char c: hand)
        s.insert(c);
    for (char c: s) {
        if (std::count(hand.begin(), hand.end(), c) == 4)
            return true;
    }
    return false;
}

bool isThreeOfAKind(std::string const& hand) {
    std::set<char> s;
    for (char c: hand)
        s.insert(c);
    for (char c: s) {
        if (std::count(hand.begin(), hand.end(), c) == 3)
            return true;
    }
    return false;
}

bool isFullHouse(std::string const& hand) {
    std::set<char> s;
    for (char c: hand)
        s.insert(c);
    return s.size() == 2 && isThreeOfAKind(hand) && !isFourOfAKind(hand);
}

bool isTwoPair(std::string const& hand) {
    std::set<char> s;
    for (char c: hand)
        s.insert(c);
    return s.size() == 3 && !isThreeOfAKind(hand);
}

bool isOnePair(std::string const& hand) {
    std::set<char> s;
    for (char c: hand)
        s.insert(c);
    return s.size() < 5;
}

int getHandStrength(std::string const& hand) {
    if (isFiveOfAKind(hand))
        return 7;
    else if (isFourOfAKind(hand))
        return 6;
    else if (isFullHouse(hand))
        return 5;
    else if (isThreeOfAKind(hand))
        return 4;
    else if (isTwoPair(hand))
        return 3;
    else if (isOnePair(hand))
        return 2;
    return 1;
}

int getCardStrength(char const& card) {
    switch (card) {
    case 'A':
        return 14;
    case 'K':
        return 13;
    case 'Q':
        return 12;
    case 'J':
        return 11;
    case 'T':
        return 10;
    }
    return static_cast<int>(card) - '0';
}

bool compareHands(std::string const& first, std::string const& second) {
    int firstHandStrength = getHandStrength(first);
    int secondHandStrength = getHandStrength(second);

    if (firstHandStrength == secondHandStrength) {
        for (int card = 0; card < 5; ++card) {
            int firstCardStrength = getCardStrength(first[card]);
            int secondCardStrength = getCardStrength(second[card]);
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

int main() {
    auto hands = getHands(readInput("input.txt"));
    std::sort(hands.begin(), hands.end(), [](auto a, auto b){ return compareHands(a.first, b.first); });

    int winnings = 0;
    for (int i = 0; i < hands.size(); ++i) {
        std::cout << hands[i].first << " is strength " << getHandStrength(hands[i].first) << ", " << hands[i].second << " * " << i+1 << std::endl;
        winnings += (i + 1) * hands[i].second;
    }

    std::cout << winnings << std::endl;

    return 0;
}

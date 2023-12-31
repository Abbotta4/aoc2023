#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

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

std::map<std::string, std::pair<std::string, std::string>> buildMap(std::vector<std::string>::iterator it, std::vector<std::string>::iterator const& end) {
    std::map<std::string, std::pair<std::string, std::string>> network;
    std::regex const r("([A-Z]{3}) = \\(([A-Z]{3}), ([A-Z]{3})\\)");
    std::smatch m;
    for (; it != end; ++it) {
        std::regex_match(*it, m, r);
        network[m[1]] = std::pair<std::string, std::string>(m[2], m[3]);
    }
    return network;
}

int stepsRequired(std::string instructions, std::map<std::string, std::pair<std::string, std::string>> network) {
    std::string position = "AAA";
    for (int i = 0; true; ++i) {
        char t = instructions[i % instructions.size()];
        position = (t == 'L' ? network[position].first : network[position].second);
        if (position == "ZZZ")
            return i + 1;
    }
}

int main() {
    auto input = readInput("input.txt");
    std::string instructions = input[0];
    auto network = buildMap(input.begin() + 2, input.end());

    std::cout << stepsRequired(instructions, network) << std::endl;

    return 0;
}

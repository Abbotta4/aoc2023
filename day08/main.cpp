#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <numeric>

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

std::map<std::string, std::pair<std::string, std::string>> buildMap(std::vector<std::string>::iterator it, std::vector<std::string>::iterator const& end) {
    std::map<std::string, std::pair<std::string, std::string>> network;
    std::regex const r("([A-Z0-9]{3}) = \\(([A-Z0-9]{3}), ([A-Z0-9]{3})\\)");
    std::smatch m;
    for (; it != end; ++it) {
        std::regex_match(*it, m, r);
        network[m[1]] = std::pair<std::string, std::string>(m[2], m[3]);
    }
    return network;
}

std::pair<std::string, int> stepsRequired(std::string const& instructions, std::map<std::string, std::pair<std::string, std::string>> const& network, std::string const& start, bool ghostNav) {
    std::string position = start;
    for (int i = 0; true; ++i) {
        char t = instructions[i % instructions.size()];
        position = (t == 'L' ? network.at(position).first : network.at(position).second);
        if ((position == "ZZZ" && !ghostNav) || (position[2] == 'Z' && ghostNav))
            return std::pair(position, i + 1);
    }
}

int main() {
    auto input = readInput("input.txt");
    std::string instructions = input[0];
    auto network = buildMap(input.begin() + 2, input.end());

    std::cout << stepsRequired(instructions, network, "AAA", false).second << std::endl;
    
    std::vector<std::string> ghosts;
    for (auto const& [key, val]: network) {
        if (key[2] == 'A')
            ghosts.push_back(key);
    }

    std::vector<int> steps;
    for (auto const& ghost: ghosts)
        steps.push_back(stepsRequired(instructions, network, ghost, true).second);

    std::cout << std::accumulate(steps.begin(), steps.end(), (long)1, [](long a, long b){ return std::lcm(a, b); }) << std::endl;

    return 0;
}

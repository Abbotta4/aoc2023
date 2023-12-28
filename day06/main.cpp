#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <tuple>
#include <cmath>

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

std::tuple<int, int> quad(int a, int b, int c) {
    int lower = std::floor((-1*b+std::sqrt(std::pow(b, 2)-4*a*c))/(2*a)+1);
    int upper = std::ceil((-1*b-std::sqrt(std::pow(b, 2)-4*a*c))/(2*a)-1);
    return std::tuple(lower, upper);
}

int getProductWins(int time, int dist) {
    auto [lower, upper] = quad(-1, time, -1*dist);
    return upper - lower + 1;
}

int main() {
    auto input = readInput("input.txt");
    std::vector<int> times;
    std::vector<int> dists;
    std::regex const r("([0-9]+)");

    for(std::sregex_token_iterator tok(input[0].begin(), input[0].end(), r, 0); tok != std::sregex_token_iterator(); ++tok)
        times.push_back(std::stol(*tok));
    for(std::sregex_token_iterator tok(input[1].begin(), input[1].end(), r, 0); tok != std::sregex_token_iterator(); ++tok)
        dists.push_back(std::stol(*tok));

    int j = 0;
    for (int i = 0; i < times.size(); ++i)
        j = j == 0 ? getProductWins(times[i], dists[i]) : j * getProductWins(times[i], dists[i]);

    std::cout << j << std::endl;

    return 0;
}

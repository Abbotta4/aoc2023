#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <regex>

std::vector<std::string> readInput(std::string fileName) {
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

bool checkGame(std::string game) {
    std::regex r("([0-9]+ [a-z]+)");
    std::sregex_token_iterator smti(game.begin(), game.end(), r);

    while(smti != std::sregex_token_iterator()) { // default constructor makes the end-of-sequence iterator
        std::string pull = *smti;
        int number = std::stoi(pull.substr(0, pull.find(" ")));
        std::string color = pull.substr(pull.find(" ")+1);
        if (color == "red" && number > 12)
            return false;
        else if (color == "green" && number > 13)
            return false;
        else if (color == "blue" && number > 14)
            return false;
        ++smti;
    }

    return true;
}

int getPower(std::string game) {
    std::regex r("([0-9]+ [a-z]+)");
    std::sregex_token_iterator smti(game.begin(), game.end(), r);
    int red = 0;
    int blue = 0;
    int green = 0;

    while(smti != std::sregex_token_iterator()) { // default constructor makes the end-of-sequence iterator
        std::string pull = *smti;
        int number = std::stoi(pull.substr(0, pull.find(" ")));
        std::string color = pull.substr(pull.find(" ")+1);
        if (color == "red")
            red = std::max(red, number);
        else if (color == "green")
            green = std::max(green, number);
        else if (color == "blue")
            blue = std::max(blue, number);
        ++smti;
    }

    return red * blue * green;
}

int main() {
    auto games = readInput("input.txt");
    std::regex id("Game ([0-9]+):");
    std::smatch sm;
    int sum = 0;
    for (std::string game: games) {
        std::regex_search(game, sm, id);
        if (checkGame(game))
            sum += std::stoi(sm[1]);
    }
    std::cout << sum << std::endl;

    int power = 0;
    for (std::string game: games) {
        power += getPower(game);
    }
    std::cout << power << std::endl;

    return 0;
}

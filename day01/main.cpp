#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

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
    return input;
}

int findNumber(std::string input) {
    int number = 0;
    std::string::iterator it = input.begin();
    while (it != input.end()) {
        int cASCII = static_cast<int>(*it);
        if (cASCII >= 48 && cASCII <= 57) {
            number += 10 * (cASCII - 48);
            break;
        }
        ++it;
    }
    std::string::reverse_iterator rit = input.rbegin();
    while (rit != input.rend()) {
        int cASCII = static_cast<int>(*rit);
        if (cASCII >= 48 && cASCII <= 57) {
            number += cASCII - 48;
            break;
        }
        ++rit;
    }

    return number;
}

int main() {
    int sum = 0;
    std::vector<std::string> input = readInput("input.txt");
    for (std::string s: input)
        sum += findNumber(s);
    std::cout << sum;
    return 0;
}

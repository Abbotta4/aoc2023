#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cctype>
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

bool checkNumber(std::vector<std::string> const& schematic, int const& row, int const& column) {
    std::set<char> symbols = {'#','%','&','*','+','-','/','=','@', '$'};
    int digits = 0;
    for (auto it = std::next(schematic[row].begin(), column); it != schematic[row].end(); ++it) {
        if (!std::isdigit(*it))
            break;
        ++digits;
    }

    if (column - 1 >= 0 && symbols.contains(schematic[row][column-1]))
        return true;
    for (int i = (column - 1 >= 0 ? -1 : 0); i < digits + (column + 1 >= 0 ? 1 : 0); ++i) {
        if (row - 1 >= 0 && symbols.contains(schematic[row-1][column+i]))
            return true;
        if (row + 1 < schematic.size() && symbols.contains(schematic[row+1][column+i]))
            return true;
    }

    if (column + 1 >= 0 && symbols.contains(schematic[row][column+digits]))
        return true;
    return false;
}

int main() {
    auto schematic = readInput("input.txt");
    int sum = 0;
    for (auto row = schematic.begin(); row != schematic.end(); row = std::next(row)) {
        for (auto col = row->begin(); col != row->end(); col = std::next(col)) {
            if (std::isdigit(*col)) {
                const int pos = std::distance(row->begin(), col);
                const std::regex re("[^0-9]");
                std::match_results<std::string::iterator> mr;
                const bool found = std::regex_search(col, row->end(), mr, re);
                const std::string number = row->substr(pos, mr.position());
                if (checkNumber(schematic, std::distance(schematic.begin(), row), std::distance(row->begin(), col)))
                    sum += std::stoi(number);
                col = std::next(col, mr.position()-1);
            }
        }
    }
    std::cout << sum << std::endl;

    return 0;
}

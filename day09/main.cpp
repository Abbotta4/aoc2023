#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <stack>
#include <algorithm>

std::vector<std::vector<int>> readInput(std::string const& fileName) {
    std::vector<std::vector<int>> input;
    std::string line;
    std::ifstream file;
    std::regex const r("[0-9-]+");
    file.open(fileName);
    while (std::getline(file, line)) {
        std::vector<int> nums;
        for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), r); i != std::sregex_iterator(); ++i)
             nums.push_back(std::stoi(i->str()));
         input.push_back(nums);
    }
    file.close();
    return input;
}

bool equal(std::vector<int> const& values) {
    const int tmp = values[0];
    for (int i: values) {
        if (tmp != i)
            return false;
    }
    return true;
}

int extrapolate(std::vector<int> const& values) {
    std::vector<int> changes = values;
    std::vector<int> temp;
    std::stack<int> finalNum;
    while (!equal(changes)) {
        finalNum.push(changes.back());
        for (int i = 0; i < changes.size()-1; ++i)
            temp.push_back(changes[i+1] - changes[i]);
        changes = temp;
        temp.clear();
    }

    int ret = changes.back();
    while (!finalNum.empty()) {
        ret += finalNum.top();
        finalNum.pop();
    }

    return ret;
}

int main() {
    auto input = readInput("input.txt");

    int valSum = 0;
    for (auto const& line: input)
        valSum += extrapolate(line);
    std::cout << valSum << std::endl;

    valSum = 0;
    for (auto line: input) {
        std::reverse(line.begin(), line.end());
        valSum += extrapolate(line);
    }
    std::cout << valSum << std::endl;

    return 0;
}

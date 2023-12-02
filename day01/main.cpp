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

int findNumberOrText(std::string input) {
    std::regex one_re("one");
    std::regex two_re("two");
    std::regex thr_re("three");
    std::regex for_re("four");
    std::regex fiv_re("five");
    std::regex six_re("six");
    std::regex sev_re("seven");
    std::regex eit_re("eight");
    std::regex nin_re("nine");
    
    int number = 0;
    std::string::iterator it = input.begin();
    while (it != input.end()) {
        int cASCII = static_cast<int>(*it);
        if (std::regex_search(input.begin(), it, one_re)) {
            number += 10 * 1;
            break;
        } else if (std::regex_search(input.begin(), it, two_re)) {
            number += 10 * 2;
            break;
        } else if (std::regex_search(input.begin(), it, thr_re)) {
            number += 10 * 3;
            break;
        } else if (std::regex_search(input.begin(), it, for_re)) {
            number += 10 * 4;
            break;
        } else if (std::regex_search(input.begin(), it, fiv_re)) {
            number += 10 * 5;
            break;
        } else if (std::regex_search(input.begin(), it, six_re)) {
            number += 10 * 6;
            break;
        } else if (std::regex_search(input.begin(), it, sev_re)) {
            number += 10 * 7;
            break;
        } else if (std::regex_search(input.begin(), it, eit_re)) {
            number += 10 * 8;
            break;
        } else if (std::regex_search(input.begin(), it, nin_re)) {
            number += 10 * 9;
            break;
        } else if (cASCII >= 48 && cASCII <= 57) {
            number += 10 * (cASCII - 48);
            break;
        }
        ++it;
    }
    std::string::reverse_iterator rit = input.rbegin();
    while (rit != input.rend()) {
        int cASCII = static_cast<int>(*rit);
        if (std::regex_search(rit.base(), input.end(), one_re)) {
            number += 1;
            break;
        } else if (std::regex_search(rit.base(), input.end(), two_re)) {
            number += 2;
            break;
        } else if (std::regex_search(rit.base(), input.end(), thr_re)) {
            number += 3;
            break;
        } else if (std::regex_search(rit.base(), input.end(), for_re)) {
            number += 4;
            break;
        } else if (std::regex_search(rit.base(), input.end(), fiv_re)) {
            number += 5;
            break;
        } else if (std::regex_search(rit.base(), input.end(), six_re)) {
            number += 6;
            break;
        } else if (std::regex_search(rit.base(), input.end(), sev_re)) {
            number += 7;
            break;
        } else if (std::regex_search(rit.base(), input.end(), eit_re)) {
            number += 8;
            break;
        } else if (std::regex_search(rit.base(), input.end(), nin_re)) {
            number += 9;
            break;
        } else if (cASCII >= 48 && cASCII <= 57) {
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
    for (std::string s: input) {
        sum += findNumber(s);
    }
    std::cout << sum << std::endl;
    sum = 0;
    for (std::string s: input) {
        sum += findNumberOrText(s);
    }
    std::cout << sum << std::endl;
    
    return 0;
}

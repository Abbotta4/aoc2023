#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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


std::map<long, long> parseMap(std::vector<std::string>::const_iterator it, std::vector<std::string>::const_iterator const& end) {
    std::regex re("([0-9]+)");
    std::map<long, long> m;
    while (it->size() > 1 and it != end) {
        std::sregex_token_iterator tok(it->begin(), it->end(), re, 0);
        long dstRangeStart = std::stol(*tok++);
        long srcRangeStart = std::stol(*tok++);
        long range = std::stol(*tok++);

        m[srcRangeStart] = dstRangeStart - srcRangeStart;
        m.try_emplace(srcRangeStart + range, 0);

        ++it;
    }
    return m;
}

long getDest(long const& src, std::map<long, long> const& m) {
    std::map<long, long>::const_iterator it = m.begin();
    while (it->first < src && it != m.end())
        ++it;
    if (it == m.begin())
        return src;
    --it;
    return src + it->second;
}

std::vector<std::map<long, long>> getMaps(std::vector<std::string> input) {
    std::map<long, long> seedToSoil;
    std::map<long, long> soilToFertilizer;
    std::map<long, long> fertilizerToWater;
    std::map<long, long> waterToLight;
    std::map<long, long> lightToTemperature;
    std::map<long, long> temperatureToHumidity;
    std::map<long, long> humidityToLocation;

    seedToSoil = parseMap(input.begin()+3, input.begin()+18);
    soilToFertilizer = parseMap(input.begin()+20, input.begin()+32);
    fertilizerToWater = parseMap(input.begin()+34, input.begin()+72);
    waterToLight = parseMap(input.begin()+74, input.begin()+98);
    lightToTemperature = parseMap(input.begin()+100, input.begin()+129);
    temperatureToHumidity = parseMap(input.begin()+131, input.begin()+162);
    humidityToLocation = parseMap(input.begin()+164, input.end());

    std::vector<std::map<long, long>> ret;
    ret.push_back(seedToSoil);
    ret.push_back(soilToFertilizer);
    ret.push_back(fertilizerToWater);
    ret.push_back(waterToLight);
    ret.push_back(lightToTemperature);
    ret.push_back(temperatureToHumidity);
    ret.push_back(humidityToLocation);

    return ret;
}
    
long findLowest(std::vector<std::map<long, long>> maps, std::vector<long> seeds) {
    std::vector<long> seedDistances;
    for (auto const& seed: seeds) {
        long tmp = seed;
        for (auto const& m: maps)
            tmp = getDest(tmp, m);
        seedDistances.push_back(tmp);
    }

    return *std::max_element(seedDistances.begin(), seedDistances.end(), [](auto a, auto b){ return b < a; });
}

using RangeVec = std::vector<std::pair<long, long>>;
RangeVec flattenRanges(RangeVec ranges, std::vector<std::map<long, long>> maps, int level) {
    RangeVec ret;
    for (auto const& r: ranges) {
        long cur = r.first;
        for (auto const& [key, val]: maps[level]) {
            if (key > r.first && key < r.second) {
                ret.push_back(std::pair<long, long>(getDest(cur, maps[level]), getDest(key, maps[level])));
                cur = key;
            }
        }
        ret.push_back(std::pair<long, long>(getDest(cur, maps[level]), getDest(r.second, maps[level])));
    }

    return ++level < maps.size() ? flattenRanges(ret, maps, level) : ret;
}

int main() {
    auto input = readInput("input.txt");
    std::vector<long> seeds;
    std::regex const sre("([0-9]+)");

    std::sregex_token_iterator tok(input[0].begin(), input[0].end(), sre, 0);
    for(; tok != std::sregex_token_iterator(); ++tok)
        seeds.push_back(std::stol(*tok));
    auto maps = getMaps(input);

    std::cout << findLowest(maps, seeds) << std::endl;

    RangeVec seedRanges;
    for (int i = 0; i < seeds.size(); i += 2)
        seedRanges.push_back({seeds[i], seeds[i]+seeds[i+1]});

    seedRanges = flattenRanges(seedRanges, maps, 0);
    seeds = {};
    for (auto const& [first, second]: seedRanges) {
        seeds.push_back(first);
        seeds.push_back(second);
    }

    std::cout << *std::max_element(seeds.begin(), seeds.end(), [](auto a, auto b){ return b < a; }) << std::endl;

    return 0;
}

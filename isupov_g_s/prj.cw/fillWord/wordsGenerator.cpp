#include "fillWord/wordsGenerator.hpp"

#include <utility>
#include <sstream>

WordsGenerator::WordsGenerator(std::string words) {
    FillWordsMap(std::move(words));
}

std::vector<std::string> WordsGenerator::SeparateString(std::string&& str) {
    constexpr char separator = ',';
    std::vector<std::string> resVector;
    std::stringstream streamData(str);
    std::string tempValue;

    while (std::getline(streamData, tempValue, separator)) {
        resVector.push_back(tempValue);
    }

    return resVector;
}

void WordsGenerator::FillWordsMap(std::string&& str) {
    const std::vector<std::string> words = SeparateString(std::move(str));
    for (const std::string& word: words) {
        int size = word.length();
        if (!wordsMap.count(size)) {
            wordsMap[size] = std::vector<std::string>{};
        }
        wordsMap[size].emplace_back(word);
    }
}

std::string WordsGenerator::GetRandomWordByLength(const int length) {
    if (!wordsMap.count(length)) {
        std::string word;
        for (int i = 0; i < length; i++) {
            word += ALPHABET[rand() % ALPHABET.size()];
        }
        return "*" + word;
    }
    return wordsMap[length][rand() % wordsMap[length].size()];
}

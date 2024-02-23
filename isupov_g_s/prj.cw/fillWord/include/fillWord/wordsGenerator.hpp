#ifndef TESTQT_WORDSGENERATOR_HPP
#define TESTQT_WORDSGENERATOR_HPP

#include <string>
#include <map>
#include <vector>

/**
 * \brief Класс для генерации слов из словаря.
 */
class WordsGenerator {
public:

    WordsGenerator() = default;

    explicit WordsGenerator(std::string words);

    WordsGenerator(const WordsGenerator& wordsGenerator) = default;

    WordsGenerator& operator=(const WordsGenerator& wordsGenerator) = default;

    ~WordsGenerator() = default;

	/**
	 * \brief Выбор из словаря случаного слова определенной длины.
	 * \param length - длина слова
	 * \return Слово
	 */
	std::string GetRandomWordByLength(int length);

private:
    std::string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

    std::map<int, std::vector<std::string>> wordsMap;

    static std::vector<std::string> SeparateString(std::string&& str);

	/**
	 * \brief Заполняет словарь словами.
	 * \param str - строка со всеми словами, разделенными запятой
	 */
	void FillWordsMap(std::string&& str);
};

#endif //TESTQT_WORDSGENERATOR_HPP

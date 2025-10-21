#include "OutputProcessor.h"
#include <iostream>
#include <iomanip>
#include <cctype>

OutputProcessor::OutputProcessor()
: _out(), _wordsModified(), _uniqueWords(), _wordCounts(),
  _totalWords(0), _totalLetters(0)
{
    for (int i = 0; i < 26; ++i) {
        _letterCounts[i] = 0;
    }
}

bool OutputProcessor::openStream() {
    std::string fname;
    std::cout << "What file would you like to output to? ";
    std::cin >> fname;

    _out.open(fname);
    if (!_out.is_open()) {
        std::cerr << "Could not open file for writing: " << fname << std::endl;
        return false;
    }
    return true;
}

void OutputProcessor::analyzeWords(const std::vector<std::string>& allWords,
                                   const std::string& punctuation)
{
    _wordsModified.clear();
    _uniqueWords.clear();
    _wordCounts.clear();
    for (int i = 0; i < 26; ++i) _letterCounts[i] = 0;
    _totalWords = 0;
    _totalLetters = 0;

    for (std::string w : allWords) {
        std::string cleaned = cleanWord(w, punctuation);
        if (cleaned.empty()) continue;

        _wordsModified.push_back(cleaned);
        _totalWords++;

        for (char ch : cleaned) {
            if (std::isupper(static_cast<unsigned char>(ch))) {
                _letterCounts[ch - 'A']++;
                _totalLetters++;
            }
        }
        int idx = indexOf(_uniqueWords, cleaned);
        if (idx == -1) {
            _uniqueWords.push_back(cleaned);
            _wordCounts.push_back(1);
        } else {
            _wordCounts[idx]++;
        }
    }
}

void OutputProcessor::write() {
    if (!_out.is_open()) {
        std::cerr << "Output file not open!" << std::endl;
        return;
    }

    _out << "Read in " << _totalWords << " words\n";
    _out << "Encountered " << _uniqueWords.size() << " unique words\n";

    size_t longestWord = 0;
    int maxCount = 0;
    for (size_t i = 0; i < _uniqueWords.size(); ++i) {
        if (_uniqueWords[i].size() > longestWord)
            longestWord = _uniqueWords[i].size();
        if (_wordCounts[i] > maxCount)
            maxCount = _wordCounts[i];
    }

    int countWidth = std::to_string(maxCount).length();

    std::vector<std::string> sortedWords = _uniqueWords;
    std::vector<int> sortedCounts = _wordCounts;

    for (size_t i = 0; i < sortedWords.size(); ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < sortedWords.size(); ++j) {
            if (sortedWords[j] < sortedWords[minIndex]) {
                minIndex = j;
            }
        }
        std::string tempWord = sortedWords[i];
        sortedWords[i] = sortedWords[minIndex];
        sortedWords[minIndex] = tempWord;

        int tempCount = sortedCounts[i];
        sortedCounts[i] = sortedCounts[minIndex];
        sortedCounts[minIndex] = tempCount;
    }

    for (size_t i = 0; i < sortedWords.size(); ++i) {
        _out << std::left << std::setw(longestWord) << sortedWords[i]
              << " : "
              << std::right << std::setw(countWidth) << sortedCounts[i] << "\n";
    }

    int maxIdx = 0, minIdx = 0;
    for (size_t i = 1; i < _wordCounts.size(); ++i) {
        if (_wordCounts[i] > _wordCounts[maxIdx]) maxIdx = i;
        if (_wordCounts[i] < _wordCounts[minIdx]) minIdx = i;
    }

    double maxPct = (_totalWords > 0)
        ? (100.0 * _wordCounts[maxIdx] / _totalWords) : 0.0;
    double minPct = (_totalWords > 0)
        ? (100.0 * _wordCounts[minIdx] / _totalWords) : 0.0;

    _out << " Most Frequent Word: " << std::left
          << std::setw(longestWord) << _uniqueWords[maxIdx]
          << " " << std::right << std::setw(countWidth) << _wordCounts[maxIdx]
          << " (" << std::setw(7) << std::fixed << std::setprecision(3)
          << maxPct << "%)\n";

    _out << "Least Frequent Word: " << std::left
          << std::setw(longestWord) << _uniqueWords[minIdx]
          << " " << std::right << std::setw(countWidth) << _wordCounts[minIdx]
          << " (" << std::setw(7) << std::fixed << std::setprecision(3)
          << minPct << "%)\n";

    for (int i = 0; i < 26; ++i) {
        char letter = 'A' + i;
        _out << letter << std::setfill('.')
              << std::setw((int)longestWord + 3) << std::setfill('.')
              << std::right << _letterCounts[i] << "\n";
        _out << std::setfill(' ');
    }

    int maxL = 0, minL = 0;
    for (int i = 1; i < 26; ++i) {
        if (_letterCounts[i] > _letterCounts[maxL]) maxL = i;
        if (_letterCounts[i] < _letterCounts[minL]) minL = i;
    }

    double maxLPct = (_totalLetters > 0)
        ? (100.0 * _letterCounts[maxL] / _totalLetters) : 0.0;
    double minLPct = (_totalLetters > 0)
        ? (100.0 * _letterCounts[minL] / _totalLetters) : 0.0;

    _out << " Most Frequent Letter: " << (char)('A' + maxL)
          << " " << _letterCounts[maxL]
          << " (" << std::setw(7) << std::fixed << std::setprecision(3)
          << maxLPct << "%)\n";

    _out << "Least Frequent Letter: " << (char)('A' + minL)
          << " " << _letterCounts[minL]
          << " (" << std::setw(7) << std::fixed << std::setprecision(3)
          << minLPct << "%)\n";
}

void OutputProcessor::closeStream() {
    if (_out.is_open()) {
        _out.close();
    }
}

int OutputProcessor::indexOf(const std::vector<std::string>& v,
                             const std::string& key) const {
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] == key) return (int)i;
    }
    return -1;
}

bool OutputProcessor::isPunct(char c, const std::string& punctuation) const {
    for (char p : punctuation)
        if (c == p)
            return true;
    return false;
}

std::string OutputProcessor::cleanWord(const std::string& word,
                                       const std::string& punctuation) const {
    std::string result;
    for (char ch : word) {
        if (!isPunct(ch, punctuation)) {
            result += static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
        }
    }
    return result;
}

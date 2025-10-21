#ifndef OUTPUTPROCESSOR_H
#define OUTPUTPROCESSOR_H

#include <fstream>
#include <string>
#include <vector>

class OutputProcessor{
public:
    OutputProcessor();
    bool openStream();
    void analyzeWords(const std::vector<std::string>& allWords,
                      const std::string& punctuation);
    void write();
    void closeStream();
private:
    std::ofstream _out;
    std::vector<std::string> _wordsModified;
    std::vector<std::string> _uniqueWords;
    std::vector<int> _wordCounts;
    int _letterCounts[26];
    int _totalWords;
    int _totalLetters;
    int indexOf(const std::vector<std::string>& v, const std::string& key) const;
    bool isPunct(char c, const std::string& punctuation) const;
    std::string cleanWord(const std::string& word, const std::string& punctuation) const;
};

#endif
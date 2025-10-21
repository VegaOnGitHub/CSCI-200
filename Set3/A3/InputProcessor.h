#ifndef INPUTPROCESSOR_H
#define INPUTPROCESSOR_H

#include <fstream>
#include <string>
#include <vector>

class InputProcessor{
public:
    InputProcessor();
    bool openStream();
    void read();
    void closeStream();
    std::vector<std::string> getAllWords() const;
private:
    std::ifstream _in;
    std::vector<std::string> _allWords;
};

#endif
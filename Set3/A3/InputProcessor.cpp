#include "InputProcessor.h"
#include <iostream>

InputProcessor::InputProcessor()
:_in(), _allWords() {}
bool InputProcessor::openStream(){     
    std::string fname;
    std::cout << "What file would you like to input? ";
    std::cin >> fname;

    _in.open(fname);
    if(!_in.is_open()){
        std::cerr << "could not open file" << std::endl;
        return false;
    }
    return true;
}

void InputProcessor::read(){
    _allWords.clear();
    std::string word;
    while (_in >> word){
        _allWords.push_back(word);
    }
}

void InputProcessor::closeStream(){
    if(_in.is_open()){
        _in.close();
    }
}

std::vector<std::string> InputProcessor::getAllWords() const{
    return _allWords;
}
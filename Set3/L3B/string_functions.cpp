#include "string_functions.h"

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

size_t string_length(const string STR)  {
    size_t result = 0;
    result = STR.length();  // set result to the length of the string
    return result;
}

char string_char_at(const string STR, const size_t IDX) {
    char result = STR.at(IDX);
    // TODO 01: set result to the character of a string at a given index
    std::cout << "TODO: implement string_char_at(\"" << STR << "\", " << IDX << ")" << std::endl;
    return result;
}

string string_append(const string LEFT, const string RIGHT)  {
    string result = LEFT + RIGHT;
    // TODO 02: set result to the concatenation of strings LEFT and RIGHT
    std::cout << "TODO: implement string_append(\"" << LEFT << "\", \"" << RIGHT << "\")" << std::endl;
    return result;
}

string string_insert(const string STR, const string TO_INSERT, const size_t IDX) {
    string result = STR;
    result.insert(IDX, TO_INSERT);
    // TODO 03: set result to the result of inserting a string into another
    std::cout << "TODO: implement string_insert(\"" << STR << "\", \"" << TO_INSERT << "\", " << IDX << ")" << std::endl;
    return result;
}

size_t string_find(const string STR, const char C)  {
    size_t result = STR.find(C);
    // TODO 04: set result to the index of the first occurrence of the character
    std::cout << "TODO: implement string_find(\"" << STR << "\", '" << C << "')" << std::endl;
    return result;
}

string string_substring(const string STR, const size_t IDX, const size_t LEN) {
    string result = STR.substr(IDX, LEN);
    // TODO 05: set result to be a substring starting at index of given length
    std::cout << "TODO: implement string_substring(\"" << STR << "\", " << IDX << ", " << LEN << ")" << std::endl;
    return result;
}

string string_replace(const string STR, const string TEXT_TO_REPLACE, const string REPLACE_WITH) {
    string result = STR;
    size_t pos = result.find(TEXT_TO_REPLACE);
    if (pos != string::npos){
        result.replace(pos, TEXT_TO_REPLACE.length(), REPLACE_WITH);
    }
    // TODO 06: set result to be the string with the given text replaced
    std::cout << "TODO: implement string_replace(\"" << STR << "\", \"" << TEXT_TO_REPLACE << "\", \"" << REPLACE_WITH << ")\"" << std::endl;
    return result;
}

string string_first_word(const string STR)  {
    string result = STR;
    size_t space = STR.find(' ');
    if (space != string::npos){
        result = STR.substr(0, space);
    }
    // TODO 07: set result to the first word from the string
    std::cout << "TODO: implement string_first_word(\"" << STR << "\")" << std::endl;
    return result;
}

string string_remove_first_word(const string STR)  {
    string result = STR;
    size_t space = STR.find(' ');
    if (space != string::npos){
        result = STR.substr(space + 1);
    } else {
        result = "";
    }
    // TODO 08: set result to be the string with the first word removed
    std::cout << "TODO: implement string_remove_first_word(\"" << STR << ")\"" << std::endl;
    return result;
}

string string_second_word(const string STR)  {
    string result = STR;
    size_t first = STR.find(' ');
    if (first != string::npos) {
        size_t second = STR.find (' ', first + 1);
        if (second != string::npos){
            result = STR.substr(first + 1, second - first - 1);
        } else {
            result = STR.substr(first + 1);
        }
    } else {
        result = "";
    }
    // TODO 09: set result to be the second word from the string
    std::cout << "TODO: implement string_second_word(\"" << STR << "\")" << std::endl;
    return result;
}

string string_third_word(const string STR)  {
    string result = STR;
    size_t first = STR.find(' ');
    if (first != string::npos) {
        size_t second = STR.find(' ', first + 1);
        if (second != string::npos) {
            size_t third = STR.find(' ', second + 1);
            if (third != string::npos)
                result = STR.substr(second + 1, third - second - 1);
            else
                result = STR.substr(second + 1);
        } else {
            result = "";
        }
    } else {
        result = "";
    }
    // TODO 10: set result to be the third word from the string
    std::cout << "TODO: implement string_third_word(\"" << STR << "\")" << std::endl;
    return result;
}

string string_nth_word(const string STR, const int N) {
    string result = STR;
    if (N <= 0){
        return "";
    }
    size_t start = 0, end = 0;
    int count = 0;
    while (start != string::npos){
        end = STR.find(' ', start);
        count++;
        if (count == N) {
            if (end == string::npos){
                return STR.substr(start);
            }
            else{
                return STR.substr(start, end - start);
            }
            if (end == string::npos){
                break;
            }
        start = end + 1;
        }
        return "";
    }
    // TODO 11: set result to be the nth word from the string
    std::cout << "TODO: implement string_nth_word(\"" << STR << "\", " << N << ")" << std::endl;
    return result;
}

vector<string> string_tokenize(const string STR, const char DELIMINATOR) {
    vector<string> result;
    size_t start = 0;
    size_t end = STR.find(DELIMINATOR);
    while (end != string::npos) {
        result.push_back(STR.substr(start, end - start));
        start = end + 1;
        end = STR.find(DELIMINATOR, start);
    }
    result.push_back(STR.substr(start));
    // TODO 12: split the string by the given deliminator
    std::cout << "TODO: implement string_tokenize(\"" << STR << "\", '" << DELIMINATOR << "')" << std::endl;
    return result;
}

string string_substitute(const string STR, const char TARGET, const char REPLACEMENT)  {
    string result = STR;
    for (size_t i = 0; i < result.size(); i++){
        if (result[i] == TARGET){
            result[i] = REPLACEMENT;
        }
    }
    // TODO 13: set result to be the string with all instances of TARGET replaced
    std::cout << "TODO: implement string_substitute(\"" << STR << "\", '" << TARGET << "', '" << REPLACEMENT << "')" << std::endl;
    return result;
}

string string_to_lower(const string STR) {
    string result = STR;
    for (size_t i = 0; i < result.size(); i++){
        result[i] = tolower(result[i]);
    }
    // TODO 14: convert all characters to lower case
    std::cout << "TODO: implement string_to_lower(\"" << STR << "\")" << std::endl;
    return result;
}

string string_to_upper(const string STR) {
    string result = STR;
    for (size_t i = 0; i < result.size(); i++){
        result[i] = toupper(result[i]);
    }

    // TODO 15: convert all characters to upper case
    std::cout << "TODO: implement string_to_upper(\"" << STR << "\")" << std::endl;
    return result;
}

int string_compare(const string LHS, const string RHS) {
    int result = 0;
    if (LHS < RHS){
        result = -1;
    } else if( LHS > RHS){
        result = 1;
    } else {
        result = 0;
    }

    // TODO 16: compare LHS and RHS
    std::cout << "TODO: implement string_compare(\"" << LHS << "\", \"" << RHS << "\")" << std::endl;
    return result;
}
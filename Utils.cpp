//
// Created by David on 2017-01-07.
//

#include <sstream>

using namespace std;

int strToInt(string s) {
    stringstream ss;
    ss << s;
    int i;
    ss >> i;
    return i;
}

string intToStr(int i) {
    stringstream ss;
    string s;
    ss << i;
    ss >> s;
    return s;
}
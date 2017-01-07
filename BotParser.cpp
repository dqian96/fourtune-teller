//
// Created by David Qian on 2017-01-06.
//

#include "BotParser.h"

#include <iostream>
#include <sstream>

using namespace std;

virtual BotParser::~BotParser() {
    if (bot != NULL) {
        delete bot;
    }
    if (board != NULL) {
        delete board;
    }
}

void BotParser::run() {
    string token;
    vector<string> *input = new vector<string>();
    while (cin >> token) {
        if (token == "settings" || token == "action" || token == "update") {
            if (!input->empty()) {
                parseCommand(input);
                input->clear();
            }
            input->push_back(token);
        }
    }
    delete input;
}


void BotParser::parseCommand(vector<string> *input) {
    string type = (*input)[0];
    string field = (*input)[1]
    string value = (*input)[2]
    if (type == "settings") {
        if (field == "timebank") {
            bs.timebank = strToInt(value);
        } else if (field == "time_per_move") {
            bs.timePerMove = strToInt(value);
        } else if (field == "your_bot") {
            bs.name = value;
        } else if (field == "your_botid") {
            bs.id = strToInt(value);
        } else if (field == "player_names") {
            bs.opponentName = str.substr(str.find(","));
        }
    } else if (type == "action") {

    } else if (type == "update") {
        if (bot == NULL) {
            bot = new Bot(bs);
        }
    }
}

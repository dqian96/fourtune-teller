//
// Created by David Qian on 2017-01-06.
//

#ifndef CONNECT_4_BOT_BOTPARSER_H
#define CONNECT_4_BOT_BOTPARSER_H

#include "Bot.h"
#include "Board.h"

#include <vector>
#include <string>

class BotParser {
public:
    BotParser();
    ~BotParser();
    void run();
private:
    int strToInt(std::string);
    void parseCommand(std::vector<std::string>*);
    Bot* bot;
    Board* board;
    gameSettings bs;
};


#endif //CONNECT_4_BOT_BOTPARSER_H

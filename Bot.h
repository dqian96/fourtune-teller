//
// Created by David Qian on 2017-01-06.
//

#ifndef CONNECT_4_BOT_BOT_H
#define CONNECT_4_BOT_BOT_H


#include "Board.h"

#include <string>

struct gameSettings {
    int timebank;
    int timePerMove;
    int id;
    std::string name;
    std::string opponentName;
};

class Bot {
public:
    Bot(gameSettings, Board*);
    int makeMove() const;
    void setTimebank(int);
private:
    gameSettings gs;
    Board* board;
};


#endif //CONNECT_4_BOT_BOT_H

//
// Created by David Qian on 2017-01-06.
//

#include "Bot.h"

using namespace std;

Bot::Bot(gameSettings gs, Board* board) : gs(gs), board(board) {}

int Bot::makeMove() const {
    return 0;
}

void Bot::setTimebank(int t) {
    gs.timebank = t;
}
//
// Created by David Qian on 2017-01-06.
//

#include "Bot.h"

using namespace std;

Bot::Bot(gameSettings gs, Board* board) : gs(gs), board(board) {}

int Bot::makeMove() const {
    if (board->getRound() == 1 && gs.id == 1) {
        // if the bot is the first player to move, always play the center column
        return board->getNumColumns()/2;
    }
    return 0;
}

void Bot::setTimebank(int t) {
    gs.timebank = t;
}
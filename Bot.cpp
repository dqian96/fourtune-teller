//
// Created by David Qian on 2017-01-06.
//

#include "Bot.h"

using namespace std;

Bot::Bot(gameSettings gs, Board* board) : gs(gs), board(board) {}

int Bot::makeMove() {
    if (board->getRound() <= 2 && gs.id == 1) {
        // for the bot's first/second move, play the centre column
        return board->getNumColumns()/2;
    }

    if (board->getRound() < 10) {
        // large branching factor at the start means more time/lookaheads are necessary for a meaningful result
        return mm.chooseBestMove(board, gs.id, 1);
    }

    if (gs.timebank <= 3000) {
        // not much time left, less piles to avoid TLE
        return mm.chooseBestMove(board, gs.id, 3);
    }

    return mm.chooseBestMove(board, gs.id, 4);
}

void Bot::setTimebank(int t) {
    gs.timebank = t;
}
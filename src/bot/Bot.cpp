//
// Created by David Qian on 2017-01-06.
//

#include "Bot.h"

using namespace std;

Bot::Bot(gameSettings gs, Board* board) : gs(gs), board(board) {}

int Bot::makeMove() {
    if (board->getRound() <= 2) {
        // for the bot's first/second move, play the centre column
        return board->getNumColumns()/2;
    }

    if (gs.timebank >= 5000 && board->getRound() >= 31) {
        // good amount of time left; increase number of piles as average branching
        // factor decreases
        return mm.chooseBestMove(board, gs.id, gs.adversaryId, 7);
    }

    if (gs.timebank <= 1000) {
        // not much time left, decrease piles
        return mm.chooseBestMove(board, gs.id, gs.adversaryId, 3);
    }

    if (board->getRound() <= 8) {
        // large branching factor and not much on board (less potential for threats)
        // means we don't have to search so many piles
        return mm.chooseBestMove(board, gs.id, gs.adversaryId, 4);
    }

    // normal search depth
    return mm.chooseBestMove(board, gs.id, gs.adversaryId, 6);
}

void Bot::setTimebank(int t) {
    gs.timebank = t;
}

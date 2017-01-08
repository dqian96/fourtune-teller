//
// Created by David on 2017-01-07.
//

#include "Minimax.h"

using namespace std;

Minimax::Minimax() {}

Minimax::~Minimax() {}
/*
int Minimax::chooseBestMove(int playerId, Board* board, int numPiles) {
    MinimaxNode* root;
    selectMove(playerId, board, root, numPiles);
}

MinimaxNode* Minimax::selectMove(int playerId, Board* board, MinimaxNode* root, int pilesLeft) {
    root = new MinimaxNode(Maximizer, board->toString());
    if (pilesLeft == 0) {

    }
    for (int move = 0; move < board->getNumColumns(); move++) {
        if (board->isValidMove(move)) {
            MinimaxNode* child;
            root->addChild(child);
            selectMove(playerId, board->placeDisc(move, playerId), child, pilesLeft - 1);
        }
    }
}
 */
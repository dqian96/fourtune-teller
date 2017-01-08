//
// Created by David on 2017-01-07.
//

#include "Minimax.h"

using namespace std;

Minimax::Minimax() {}

Minimax::~Minimax() {}


// each node pushes its alpha/beta to its children
// once each node is done searching, its pushes its alpha/beta to its parent

int Minimax::chooseBestMove(Board* board, int playerId, int numPiles) {
    string currBoard = board->toString();
    int stateEvaluation = alphaBeta(board, playerId, numPiles);
    // return board to original state
    board->updateFromString(currBoard);
}

int Minimax::alphaBeta(Board* board, int playerId, int piles, MinimaxGoal goal, int alpha, int beta) {
    if (piles == 0) {
        // evaluate leaf node
        return evaluateBoard(board->toString());
    }

    // save board at current state
    string currBoard = board->toString();

    // search all possible moves/futures
    for (int move = 0; move < board->getNumColumns(); move++) {
        if (board->isValidMove(move)) {
            board->placeDisc(playerId, move);

            // update alpha/beta from evaluation of child state
            MinimaxGoal childGoal = goal == Maximize ? Minimize : Maximize;
            int candidate = alphaBeta(board, playerId, piles - 1, childGoal, alpha, beta);
            if (goal == Maximize) {
                alpha = candidate > alpha ? candidate : alpha;
            } else {
                beta = candidate < beta ? candidate : beta;
            }

            // prune the remaining subtrees if root is invalid/impossible
            if (alpha >= beta) {
                break;
            }

            // refresh board back to current state
            board->updateFromString(currBoard);
        }
    }
    return goal == Maximize ? alpha : beta;
}

int Minimax::evaluateBoard(string board) {
    return 0;
}
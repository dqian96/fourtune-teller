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
    pair<int, int> stateEvaluation = alphaBeta(board, playerId, numPiles);
    // return board to original state
    board->updateFromString(currBoard);
    return stateEvaluation.second;
}

// (stateScore, optimalMove)
pair<int, int> Minimax::alphaBeta(Board* board, int playerId, int piles, MinimaxGoal goal, int alpha, int beta) {
    if (piles == 0) {
        // evaluate leaf node
        return pair<int, int> (evaluateBoard(board->toString()), -1);
    }

    // save board at current state
    string currBoard = board->toString();

    // search all possible moves/futures
    int bestMove = -1;
    for (int move = 0; move < board->getNumColumns(); move++) {
        if (board->isValidMove(move)) {
            board->placeDisc(playerId, move);

            // update alpha/beta from evaluation of child state
            MinimaxGoal childGoal = goal == Maximize ? Minimize : Maximize;
            pair<int, int> candidate = alphaBeta(board, playerId, piles - 1, childGoal, alpha, beta);
            if (goal == Maximize) {
                int oldAlpha = alpha;
                alpha = candidate.first > alpha ? candidate.first : alpha;
                bestMove = oldAlpha != alpha ? move : bestMove;
            } else {
                int oldBeta = beta;
                beta = candidate.first < beta ? candidate.first : beta;
                bestMove = oldBeta != alpha ? move : bestMove;
            }

            // prune the remaining subtrees if root is invalid/impossible
            if (alpha >= beta) {
                break;
            }

            // refresh board back to current state
            board->updateFromString(currBoard);
        }
    }
    return pair<int, int> (goal == Maximize ? alpha : beta, bestMove);
}

int Minimax::evaluateBoard(string board) {
    return 0;
}
//
// Created by David on 2017-01-07.
//

#include <iostream>
#include "Minimax.h"
#include "BoardIterator.h"

using namespace std;

Minimax::Minimax() {}

Minimax::~Minimax() {}


// each node pushes its alpha/beta to its children
// once each node is done searching, its pushes its alpha/beta to its parent

int counter = 0;

int Minimax::chooseBestMove(Board* board, int playerId, int adversaryId, int numPiles) {
    string currBoard = board->toString();
    pair<int, int> stateEvaluation = alphaBeta(board, playerId, adversaryId, numPiles);
    // return board to original state
    board->updateFromString(currBoard);
    cout << counter << endl; // TODO: debug counter
    return stateEvaluation.second;
}

// (stateScore, optimalMove)
pair<int, int> Minimax::alphaBeta(Board* board, int maxmizerId, int minimizerId, int piles,
                                  MinimaxGoal goal, int alpha, int beta) {
    counter += 1;
    if (piles == 0) {
        // evaluate leaf node
        return pair<int, int> (evaluateBoard(board), -1);
    }

    // save board at current state
    string originalBoard = board->toString();
    // search all possible moves/futures
    int bestMove = -1;
    for (int move = 0; move < board->getNumColumns(); move++) {
        if (board->isValidMove(move)) {
            board->placeDisc(goal == Maximize ? maxmizerId : minimizerId, move);

            // update alpha/beta from evaluation of child state
            MinimaxGoal childGoal = goal == Maximize ? Minimize : Maximize;
            pair<int, int> candidate = alphaBeta(board, maxmizerId, minimizerId, piles - 1, childGoal, alpha, beta);
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
            board->updateFromString(originalBoard);
        }
    }
    return pair<int, int> (goal == Maximize ? alpha : beta, bestMove);
}

/**
 *
 * This is a heuristic evaluation function that I came up with through basic experimentation
 *
 * Terminology:
 *
 * threat -> an empty space
 * strong threat -> an empty cell, that if played, will make a 4 in a row
 * weak threat -> an empty cell, that if played, will produce a strong threat (i.e. 2 in a row -> play -> 3 in a row
 *                that can still make a 4 in a row (not blocked off))
 * odd threat -> a threat in an odd row (zugzwang related)
 * even threat -> a threat in an even row (zugzwang related)
 * reachable threat -> a threat that can be immediately played
 * unreachable threat -> a threat can't be immediately played
 * O -> maximizing player piece
 * X -> cannot play
 * _ -> reachable empty cell
 * ^ -> unreachable empty cell
 * / -> or
 * (...) -> cell in question
 *
 * Scoring (values positive for current player, negative for adversary):
 * 4-in-a-row: inf
 * strong threat -> 5
 * weak threat -> 1
 * odd threat -> x2
 * even threat -> x1
 * reachable threat -> x3
 * unreachable threat -> x1
 *
 * Categorization of threat (_/^) cell (S/W for strong/weak threat, R/U for reachable/unreachable threat) :
 * Note: "" implies that it does not matter what piece the correspondent cell contain (i.e. (_) means the
 * pieces left and right of the empty cell do not matter)
 *
 * ^/_OO(_)X/_/^ (W, R)
 * ^/_OO(^)X/_/^ (W, U)
 * symmetry for reflection i.e.(_)OO^
 *
 * ^/_O(_)OX/_/^ (W, R)
 * ^/_O(^)OX/_/^ (W, U)
 * symmetry for reflection
 *
 * OOO(_)X/_/^ (W, R)
 * OOO(^)X/_/^ (S, U)
 *
 * OO(_)O (S, R)
 * OO(^)O (S, U)
 *
 * Note: the reason why the left and right cells (of the pattern) do not matter is that
 * OOOO will be caught as a four-in-a-row
 *
 */
int Minimax::evaluateBoard(Board* const board) {
    BoardIterator* iter = new BoardIterator(board);

    return 0;
}
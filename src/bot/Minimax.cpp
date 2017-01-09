//
// Created by David on 2017-01-07.
//

#include <iostream>
#include "Minimax.h"
#include "../board/BoardIterator.h"

using namespace std;

const unordered_map<std::string, int> Minimax::patternScore = {
        {"1111", numeric_limits<int>::max()}
};

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
        return pair<int, int> (evaluateBoard(board, maxmizerId, minimizerId), -1);
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
 * [x/y] -> x or y
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
 * [^/_]OO(_)[X/_/^] (W, R)
 * [^/_]OO(^)[X/_/^] (W, U)
 * symmetry for reflection i.e.[X/_/^](_)OO[^/_]
 *
 * [^/_]O(_)O[X/_/^] (W, R)
 * [^/_]O(^)O[X/_/^] (W, U)
 * symmetry for reflection
 *
 * OOO(_) (S, R)
 * OOO(^) (S, U)
 * symmetric for reflection
 *
 * OO(_)O (S, R)
 * OO(^)O (S, U)
 * symmetry for reflection
 *
 * Note: the reason why the left and right cells (of the pattern) do not matter is that
 * OOOO will be caught as a four-in-a-row
 *
 */
int Minimax::evaluateBoard(Board* const board, int maxmizerId, int minimizerId) const {
    BoardIterator* iter = new BoardIterator(board);
    int score = 0;

    // two strings, maximizer and minizer?
    // from perspective of maximizer
        // if spot is maximizerId -> put O
        // if spot is minimizerId -> put X
        // score + positive lookup
    // if maximizer perspective doesnt yield then from persepective of minimizer:
        // reverse X and Os
        // score - negative lookup
    while (!iter->isEnd() && score != numeric_limits<int>::max() && score != -numeric_limits<int>::max()) {
        string pattern = "";

        if (!board->isEmptyCell(iter->getDiscPosition())) {
            // look for 4 in a row

            if (board->isValidPosition(iter->getRightDiscPosition(3))) {
                // look to the right
                for (int i = 0; i < 4; i++) {
                    pattern += board->getDisc(iter->getRightDiscPosition(i));
                }
                if (patternScore.count(pattern) != 0) {
                    score += patternScore.at(pattern);
                }
                pattern = "";
            }

            if (board->isValidPosition(iter->getLowerDiscPosition(3))) {
                // look to the bottom
                for (int i = 0; i < 4; i++) {
                    pattern += board->getDisc(iter->getLowerDiscPosition(i));
                }
                if (patternScore.count(pattern) != 0) {
                    return patternScore.at(pattern);
                }
                pattern = "";
            }

            if (board->isValidPosition(iter->getUpperRightDiagonalDiscPosition(3))) {
                // look to the top right
                for (int i = 0; i < 4; i++) {
                    pattern += board->getDisc(iter->getUpperRightDiagonalDiscPosition(i));
                }
                if (patternScore.count(pattern) != 0) {
                    return patternScore.at(pattern);
                }
                pattern = "";
            }

            if (board->isValidPosition(iter->getLowerRightDiagonalDiscPosition(3))) {
                // look to the bottom left
                for (int i = 0; i < 4; i++) {
                    pattern += board->getDisc(iter->getLowerRightDiagonalDiscPosition(i));
                }
                if (patternScore.count(pattern) != 0) {
                    return patternScore.at(pattern);
                }
            }
        } else {

        }
        iter->next();
    }
    return score;
}


//
// Created by David on 2017-01-07.
//

#include <iostream>
#include "Minimax.h"
#include "../board/BoardIterator.h"

using namespace std;

/**
 * This is a heuristic evaluation function that I came up with through basic experimentation
 *
 * Terminology:
 *
 * threat -> an empty space
 * realized threat -> 4-in-a-row
 * strong threat -> an empty cell, that if played, will make a 4-in-a-row
 * weak threat -> an empty cell, that if played, will produce a strong threat (i.e. 2 in a row -> play -> 3-in-a-row
 *                that can still make a 4-in-a-row (i.e. not blocked off))
 * odd threat -> a threat in an odd row (zugzwang)
 * even threat -> a threat in an even row (zugzwang)
 * reachable threat -> a threat that can be immediately played
 * unreachable threat -> a threat can't be immediately played
 * O -> maximizing player disc
 * X -> minimizing player disc
 * _ -> reachable empty cell
 * ^ -> unreachable empty cell
 * [x/y] -> state is either x or y
 * (_) -> reachable threat
 * (^) -> unreachable threat
 *
 * Scoring (from the perspective of O):
 * realized threat: inf
 * strong threat -> 5
 * weak threat -> 1
 * odd threat -> x2
 * even threat -> x1
 * reachable threat -> x3
 * unreachable threat -> x1
 *
 * Possible threat patterns, categorized (S/W for strong/weak threat, R/U for reachable/unreachable) :
 *
 * (O)OOO (REALIZED)

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
 */
const unordered_map<std::string, int> Minimax::patternScore = {
        // (REALIZED)
        {"(O)OOO", numeric_limits<int>::max()},

        // [^/_]OO(_)[X/_/^] (W, R)
        {"^OO(_)X", 3},
        {"^OO(_)_", 3},
        {"^OO(_)^", 3},
        {"_OO(_)X", 3},
        {"_OO(_)_", 3},
        {"_OO(_)^", 3},

        {"X(_)OO^", 3},
        {"_(_)OO^", 3},
        {"^(_)OO^", 3},
        {"X(_)OO_", 3},
        {"_(_)OO_", 3},
        {"^(_)OO_", 3},

        // [^/_]O(_)O[X/_/^] (W, R)
        {"^O(_)OX", 3},
        {"^O(_)O_", 3},
        {"^O(_)O^", 3},
        {"_O(_)OX", 3},
        {"_O(_)O_", 3},
        {"_O(_)O^", 3},

        {"XO(_)O^", 3},
        {"_O(_)O^", 3},
        {"^O(_)O^", 3},
        {"XO(_)O_", 3},
        {"_O(_)O_", 3},
        {"^O(_)O_", 3},

        // [^/_]OO(^)[X/_/^] (W, U)
        {"^OO(^)X", 1},
        {"^OO(^)_", 1},
        {"^OO(^)^", 1},
        {"_OO(^)X", 1},
        {"_OO(^)_", 1},
        {"_OO(^)^", 1},

        {"X(^)OO^", 1},
        {"_(^)OO^", 1},
        {"^(^)OO^", 1},
        {"X(^)OO_", 1},
        {"_(^)OO_", 1},
        {"^(^)OO_", 1},

        // [^/_]O(^)O[X/_/^] (W, U)
        {"^O(^)OX", 1},
        {"^O(^)O_", 1},
        {"^O(^)O^", 1},
        {"_O(^)OX", 1},
        {"_O(^)O_", 1},
        {"_O(^)O^", 1},

        {"XO(^)O^", 1},
        {"_O(^)O^", 1},
        {"^O(^)O^", 1},
        {"XO(^)O_", 1},
        {"_O(^)O_", 1},
        {"^O(^)O_", 1},

        // OOO(_) (S, R)
        {"OOO(_)", 15},
        {"(_)OOO", 15},


        // OOO(^) (S, U)
        {"OOO(^)", 5},
        {"(^)OOO", 5},


        // OO(_)O (S, R)
        {"OO(_)O", 15},
        {"O(_)OO", 15},

        // OO(^)O  (S, U)
        {"OO(^)O ", 5},
        {"O(^)OO", 5},
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

string Minimax::generateCellSymbolFromMaximizerPerspective(
        Board* const board, pair<int, int> cell,
        int maximizerId, int minimizerId) const {
    int cellValue = board->getDisc(cell);
    if (cellValue == maximizerId) {
        return "O";
    } else if (cellValue == minimizerId) {
        return "X";
    } else if (board->isReachableCell(cell)) {      // empty reachable
        return "_";
    } else {                                        // empty unreachable
        return "^";
    }
}

string Minimax::flipPatternPerspective(string maximimzerPattern) const {
    replace(maximimzerPattern.begin(), maximimzerPattern.end(), 'O', '~');
    replace(maximimzerPattern.begin(), maximimzerPattern.end(), 'X', 'O');
    replace(maximimzerPattern.begin(), maximimzerPattern.end(), '~', 'X');
    return maximimzerPattern;
}


string Minimax::getPatternFromMaximizerPerspective(
        Board* const board, int maximizerId, int minimizerId,
        pair<int, int> currentCell, int lowerBound, int upperBound,
        BoardIterator* iter,
        pair<int, int> (BoardIterator::*decrementer)(int), pair<int, int>(BoardIterator::*incrementer)(int)) const {

    if (!board->isValidPosition((iter->*decrementer)(lowerBound)) ||
            !board->isValidPosition((iter->*decrementer)(upperBound))) {
        // one of the lower/upper bounds/limits/positions are invalid (i.e. outside the board)
        return "";
    }

    string pattern = "";

    // maximizer perspective
    for (int i = lowerBound; i >= 1; i--) {
        // generate pattern for [lower bound, currentCell)
        pair<int, int> cell = (iter->*decrementer)(i);
        pattern += generateCellSymbolFromMaximizerPerspective(board, cell, maximizerId, minimizerId);
    }

    // generate pattern/symbol for currentCell ("(" and ")" means that there is no ambiguity about which cell is threat)
    pattern += "(" + generateCellSymbolFromMaximizerPerspective(board, currentCell, maximizerId, minimizerId) + ")";

    for (int i = 1; i <= upperBound; i++) {
        // generate pattern for (currentCell, upper bound]
        pair<int, int> cell = (iter->*incrementer)(i);
        pattern += generateCellSymbolFromMaximizerPerspective(board, cell, maximizerId, minimizerId);
    }

    return pattern;
}


int Minimax::evaluateBoard(Board* const board, int maximizerId, int minimizerId) const {
    BoardIterator* iter = new BoardIterator(board);
    int score = 0;

    // generate pattern from maximizer perspective first
    // (pattern generated by giving lower/upper bounds and decrement/incrementer fncts for traversing to bounds)
    // i.e. if cellValue == maximizerId -> cell symbol is "O"
    // i.e. if cellValue == maximizerId -> cell symbol is "X"
    // if found in pattern table, score += patternValue
    // else, flip pattern for minimizer perspective
    // if found in pattern table score -= patternValue

    while (!iter->isEnd() && score != numeric_limits<int>::max() && score != -numeric_limits<int>::max()) {
        string pattern  = "";
        pair<int, int> currentCell = iter->getDiscPosition();
        if (!board->isEmptyCell(currentCell)) {
            // current cell not empty; look for 4 in a row

            vector< pair<int, int> (BoardIterator::*)(int) > patternDirections; // (0, 1), (2, 3),...,(decrementer, incrementer)
            patternDirections = {
                    &BoardIterator::getLeftDiscPosition,      // (O)OOO horizontal-right
                    &BoardIterator::getRightDiscPosition,
                    &BoardIterator::getLowerDiscPosition,     // (O)OOO vertical-up
                    &BoardIterator::getUpperDiscPosition,
                    &BoardIterator::getLowerLeftDiagonalDiscPosition,     // (O)OOO diagonal-lowerLeft-upperRight
                    &BoardIterator::getUpperRightDiagonalDiscPosition,
                    &BoardIterator::getLowerRightDiagonalDiscPosition,    // (O)OOO diagonal-lowerRight-upperLeft
                    &BoardIterator::getUpperLeftDiagonalDiscPosition
            };

            for (int i = 1; i < patternDirections.size(); i += 2) {
                pattern = getPatternFromMaximizerPerspective(board, maximizerId, minimizerId,
                                                             currentCell, 0, 3,
                                                             iter,
                                                             patternDirections[i], patternDirections[i - 1]);

                if (patternScore.count(pattern) != 0 && patternScore.at(pattern) == numeric_limits<int>::max()) {
                    // maximizer realized threat
                    return numeric_limits<int>::max();
                }
                // maximizer perspective not found, try minimizer perspective
                pattern = flipPatternPerspective(pattern);
                if (patternScore.count(pattern) != 0 && patternScore.at(pattern) == numeric_limits<int>::max()) {
                    // minimizer realized threat
                    return -numeric_limits<int>::max();
                }
            }
        } else {
            // current cell is empty; look for threat pattern

        }
        iter->next();
    }
    return score;
}


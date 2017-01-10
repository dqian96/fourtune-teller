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
 * (O)OOO (REALIZED) (and for all obvious positions)
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
 */
const unordered_map<std::string, int> Minimax::patternScore = {
        // (REALIZED)
        {"(O)OOO", numeric_limits<int>::max()},
        {"O(O)OO", numeric_limits<int>::max()},
        {"OO(O)O", numeric_limits<int>::max()},
        {"OOO(O)", numeric_limits<int>::max()},

        // schema: [^/_]OO(_)[X/_/^]
        // bounds to check: (3L, 1U), (1L, 3U)
        // category: (W, R), 3
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

        // schema: [^/_]O(_)O[X/_/^]
        // bounds to check: (2L, 2U), (2L, 2U)
        // category: (W, R), 3
        {"^O(_)OX", 3},
        {"^O(_)O_", 3},
        {"^O(_)O^", 3},
        {"_O(_)OX", 3},
        {"_O(_)O_", 3},
        {"_O(_)O^", 3},

        {"XO(_)O^", 3},
        {"_O(_)O^", 3},
        //{"^O(_)O^", 3},
        {"XO(_)O_", 3},
        //{"_O(_)O_", 3},
        {"^O(_)O_", 3},

        // schema: [^/_]OO(^)[X/_/^]
        // bounds to check: (3L, 1U), (1L, 3U)
        // category: (W, U), 1
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

        // schema: [^/_]O(^)O[X/_/^]
        // bounds to check: (2L, 2U), (2L, 2U)
        // category: (W, U), 1
        {"^O(^)OX", 1},
        {"^O(^)O_", 1},
        {"^O(^)O^", 1},
        {"_O(^)OX", 1},
        {"_O(^)O_", 1},
        {"_O(^)O^", 1},

        {"XO(^)O^", 1},
        {"_O(^)O^", 1},
        //{"^O(^)O^", 1},
        {"XO(^)O_", 1},
        //{"_O(^)O_", 1},
        {"^O(^)O_", 1},

        // schema: OOO(_)
        // bounds to check: (3L, 0U), (0L, 3U)
        // category: (S, R), 15
        {"OOO(_)", 15},
        {"(_)OOO", 15},

        // schema: OOO(^)
        // bounds to check: (3L, 0U), (0L, 3U)
        // category: (S, U), 5
        {"OOO(^)", 5},
        {"(^)OOO", 5},

        // schema: OO(_)O
        // bounds to check: (2L, 1U), (1L, 2U)
        // category: (S, R), 15
        {"OO(_)O", 15},
        {"O(_)OO", 15},

        // schema: OO(^)O
        // bounds to check: (2L, 1U), (1L, 2U)
        // category: (S, U), 5
        {"OO(^)O ", 5},
        {"O(^)OO", 5},
};

// (0, 1), (2, 3),...,(decrementer, incrementer) pairing for each "direction"
const vector<pair<pair<int, int> (BoardIterator::*)(int), pair<int, int> (BoardIterator::*)(int)>>
        Minimax::patternPossibleDirections = {
        // horizontal
        pair<pair<int, int> (BoardIterator::*)(int), pair<int, int> (BoardIterator::*)(int)>
                (&BoardIterator::getLeftDiscPosition, &BoardIterator::getRightDiscPosition),
        // vertical
        pair<pair<int, int> (BoardIterator::*)(int), pair<int, int> (BoardIterator::*)(int)>
                (&BoardIterator::getLowerDiscPosition, &BoardIterator::getUpperDiscPosition),
        // left down to right up diagonal
        pair<pair<int, int> (BoardIterator::*)(int), pair<int, int> (BoardIterator::*)(int)>
                (&BoardIterator::getLowerLeftDiagonalDiscPosition,
                        &BoardIterator::getUpperRightDiagonalDiscPosition),
        // right down to left up diagonal
        pair<pair<int, int> (BoardIterator::*)(int), pair<int, int> (BoardIterator::*)(int)>
                (&BoardIterator::getLowerRightDiagonalDiscPosition,
                        &BoardIterator::getUpperLeftDiagonalDiscPosition)
};

// all possible boundaries to search for 3-1, 1-3, 2-2, 3-0, 0-3, 2-1, 1-2
const vector< pair<int, int> > Minimax::threatPatternPossibleBounds = {
     pair<int, int> (3, 1),
     pair<int, int> (1, 3),
     pair<int, int> (2, 2),
     pair<int, int> (3, 0),
     pair<int, int> (0, 3),
     pair<int, int> (2, 1),
     pair<int, int> (1, 2)
};


Minimax::Minimax() {}

Minimax::~Minimax() {}


// each node pushes its alpha/beta to its children
// once each node is done searching, its pushes its alpha/beta to its parent

int Minimax::chooseBestMove(Board* board, int playerId, int adversaryId, int numPiles) {
    string currBoard = board->toString();
    pair<int, int> stateEvaluation = alphaBeta(board, playerId, adversaryId, numPiles, numPiles);
    // return board to original state
    board->updateFromString(currBoard);
    return stateEvaluation.second;
}

// (stateScore, optimalMove)
pair<int, int> Minimax::alphaBeta(Board* board, int maximizerId, int minimizerId, int piles, int originalPiles,
                                  MinimaxGoal goal, int alpha, int beta, int winningPlayer) {
    if (winningPlayer == maximizerId) {
        return pair<int, int> (numeric_limits<int>::max() - (originalPiles - piles), -1);   // favour shorter paths
    }
    if (winningPlayer == minimizerId) {
        return pair<int, int> (-numeric_limits<int>::max() + (originalPiles - piles), -1);  // favour shorter paths
    }
    if (piles == 0) {
        // evaluate leaf node
        return pair<int, int> (evaluateBoard(board, maximizerId, minimizerId), -1);
    }

    BoardIterator* iter = new BoardIterator(board);

    // save board at current state
    string originalBoard = board->toString();
    // search all possible moves/futures
    int bestMove = -1;
    for (int move = 0; move < board->getNumColumns(); move++) {
        if (board->isValidMove(move)) {
            pair<int, int> candidate;
            MinimaxGoal childGoal = goal == Maximize ? Minimize : Maximize;

            bool isWinningMove = false;
            pair<int, int> playedCell = board->placeDisc(goal == Maximize ? maximizerId : minimizerId, move);
            iter->set(playedCell);

            string pattern;
            // current cell is empty; look for threat pattern
            for (int i = 0; i < patternPossibleDirections.size(); i++) {
                for (int j = 0; j < 4; j++) {
                    pattern = getPatternFromMaximizerPerspective(board, maximizerId, minimizerId,
                                                                 playedCell,
                                                                 j,
                                                                 3 - j,
                                                                 iter,
                                                                 patternPossibleDirections[i].first,
                                                                 patternPossibleDirections[i].second);
                    if (patternScore.count(pattern) != 0) {
                        // maximizer win
                        candidate = alphaBeta(board, maximizerId, minimizerId, piles - 1, originalPiles, childGoal,
                                              alpha, beta, maximizerId);
                        isWinningMove = true;
                        break;
                    } else {
                        pattern = flipPatternPerspective(pattern);
                        if (patternScore.count(pattern) != 0) {
                            // minimizer win
                            candidate = alphaBeta(board, maximizerId, minimizerId, piles - 1, originalPiles, childGoal,
                                                  alpha, beta, minimizerId);
                            isWinningMove = true;
                            break;
                        }
                    }

                }
            }

            // recursively do alpha-beta on child, except with one less pile
            if (!isWinningMove) {
                candidate = alphaBeta(board, maximizerId, minimizerId, piles - 1, originalPiles, childGoal, alpha, beta);
            }

            // update alpha/beta from evaluation of child state
            if (goal == Maximize) {
                int oldAlpha = alpha;
                alpha = candidate.first > alpha ? candidate.first : alpha;
                bestMove = oldAlpha != alpha ? move : bestMove;
            } else {
                int oldBeta = beta;
                beta = candidate.first < beta ? candidate.first : beta;
                bestMove = oldBeta != beta ? move : bestMove;
            }

            // prune the remaining subtrees if root is invalid/impossible
            if (alpha >= beta) {
                break;
            }

            // refresh board back to current state
            board->updateFromString(originalBoard);
        }
    }
    delete iter;
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
    for (int i = 0; i < maximimzerPattern.size(); i++) {
        if (maximimzerPattern[i] == 'O') {
            maximimzerPattern[i] = 'X';
        } else if (maximimzerPattern[i] == 'X') {
            maximimzerPattern[i] = 'O';
        }
    }
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

    while (!iter->isEnd()) {
        string pattern  = "";
        pair<int, int> currentCell = iter->getDiscPosition();
        if (board->isEmptyCell(currentCell)) {
            int multiplier = board->isOddRowCell(currentCell) ? 1.5 : 1;    // TODO: 2 before
            // current cell is empty; look for threat pattern (4-in-a-row already caught by alphaBeta)
            for (int i = 0; i < patternPossibleDirections.size(); i++) {
                for (int j = 0; j < threatPatternPossibleBounds.size(); j++) {
                    pattern = getPatternFromMaximizerPerspective(board, maximizerId, minimizerId,
                                                                 currentCell,
                                                                 threatPatternPossibleBounds[j].first,
                                                                 threatPatternPossibleBounds[j].second,
                                                                 iter,
                                                                 patternPossibleDirections[i].first,
                                                                 patternPossibleDirections[i].second);

                    if (patternScore.count(pattern) != 0) {
                        // pattern is a threat pattern for maximizer
                        score += patternScore.at(pattern) * multiplier;
                    } else {
                        pattern = flipPatternPerspective(pattern);
                        if (patternScore.count(pattern) != 0) {
                            // pattern is a threat pattern for minimizer
                            score -= patternScore.at(pattern) * multiplier;
                        }
                    }

                }
            }
        }
        iter->next();
    }
    delete iter;
    return score;
}


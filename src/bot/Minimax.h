//
// Created by David on 2017-01-07.
//

#ifndef CONNECT_4_BOT_MINIMAX_H
#define CONNECT_4_BOT_MINIMAX_H

#include <limits>
#include <unordered_map>

#include "../board/Board.h"
#include "../board/BoardIterator.h"

enum MinimaxGoal {Maximize, Minimize};

class Minimax {
public:
    Minimax();
    virtual ~Minimax();
    int chooseBestMove(Board*, int, int, int);      // TODO: const?
private:
    std::string flipPatternPerspective(std::string maximimzerPattern) const;

    std::string generateCellSymbolFromMaximizerPerspective(Board* const, std::pair<int, int>,
                                                             int, int) const;

    std::string getPatternFromMaximizerPerspective(
            Board* const, int, int,
            std::pair<int, int>, int, int,
            BoardIterator*,
            std::pair<int, int> (BoardIterator::*)(int), std::pair<int, int>(BoardIterator::*)(int)) const;


    int evaluateBoard(Board* const, int, int) const;


    std::pair<int, int>  alphaBeta(Board*, int, int, int, int,
                                   MinimaxGoal = Maximize,
                                   int = -std::numeric_limits<int>::max(),
                                   int = std::numeric_limits<int>::max(),
                                   int = -1);

    static const std::unordered_map<std::string, int> patternScore;
    static const std::vector<std::pair<
            std::pair<int, int> (BoardIterator::*)(int), std::pair<int, int> (BoardIterator::*)(int)>>
            patternPossibleDirections;

    static const std::vector< std::pair<int, int> > threatPatternPossibleBounds;

};


#endif //CONNECT_4_BOT_MINIMAX_H

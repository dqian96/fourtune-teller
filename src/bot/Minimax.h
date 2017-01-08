//
// Created by David on 2017-01-07.
//

#ifndef CONNECT_4_BOT_MINIMAX_H
#define CONNECT_4_BOT_MINIMAX_H

#include <limits>
#include <unordered_map>

#include "../board/Board.h"

enum MinimaxGoal {Maximize, Minimize};

class Minimax {
public:
    Minimax();
    virtual ~Minimax();
    int chooseBestMove(Board*, int, int, int);      // TODO: const?
private:
    int evaluateBoard(Board* const, int, int) const;
    std::pair<int, int>  alphaBeta(Board*, int, int, int,
                  MinimaxGoal = Maximize,
                  int = -std::numeric_limits<int>::max(),
                  int = std::numeric_limits<int>::max());

    static const std::unordered_map<std::string, int> patternScore;


};


#endif //CONNECT_4_BOT_MINIMAX_H

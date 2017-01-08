//
// Created by David on 2017-01-07.
//

#ifndef CONNECT_4_BOT_MINIMAX_H
#define CONNECT_4_BOT_MINIMAX_H


#include "MinimaxNode.h"
#include "Board.h"

class Minimax {
public:
    Minimax();
    virtual ~Minimax();
    int chooseBestMove(int, Board*, int);
private:

};


#endif //CONNECT_4_BOT_MINIMAX_H

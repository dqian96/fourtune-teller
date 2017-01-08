//
// Created by David on 2017-01-08.
//

#ifndef CONNECT_4_BOT_BOARDITERATOR_H
#define CONNECT_4_BOT_BOARDITERATOR_H


#include "Board.h"

class BoardIterator {
public:
    BoardIterator(Board* const);
    virtual ~BoardIterator();
    void next();
    void toBegin();
    void toEnd();
    bool isBegin();
    bool isEnd();
    int getDisc();
    int getUpperDisc();
    int getLowerDisc();
    int getLeftDisc();
    int getRightDisc();
    int getUpperRightDiagonalDisc();
    int getUpperLeftDiagonalDisc();
    int getLowerLeftDiagonalDisc();
    int getLowerRightDiagonalDisc();
private:
    Board* const board;
    int row;
    int column;
};


#endif //CONNECT_4_BOT_BOARDITERATOR_H

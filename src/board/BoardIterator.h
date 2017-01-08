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
    int getUpperDisc(int = 1);
    int getLowerDisc(int = 1);
    int getLeftDisc(int = 1);
    int getRightDisc(int = 1);
    int getUpperRightDiagonalDisc(int = 1);
    int getUpperLeftDiagonalDisc(int = 1);
    int getLowerLeftDiagonalDisc(int = 1);
    int getLowerRightDiagonalDisc(int = 1);
private:
    Board* const board;
    int row;
    int column;
};


#endif //CONNECT_4_BOT_BOARDITERATOR_H

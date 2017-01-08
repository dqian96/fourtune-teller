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
    std::pair<int, int> getDiscPosition();
    std::pair<int, int> getUpperDiscPosition(int = 1);
    std::pair<int, int> getLowerDiscPosition(int = 1);
    std::pair<int, int> getLeftDiscPosition(int = 1);
    std::pair<int, int> getRightDiscPosition(int = 1);
    std::pair<int, int> getUpperRightDiagonalDiscPosition(int = 1);
    std::pair<int, int> getUpperLeftDiagonalDiscPosition(int = 1);
    std::pair<int, int> getLowerLeftDiagonalDiscPosition(int = 1);
    std::pair<int, int> getLowerRightDiagonalDiscPosition(int = 1);
private:
    Board* const board;
    int row;
    int column;
};


#endif //CONNECT_4_BOT_BOARDITERATOR_H

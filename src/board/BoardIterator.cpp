//
// Created by David on 2017-01-08.
//

#include "BoardIterator.h"

using namespace std;

BoardIterator::BoardIterator(Board* const board): board(board) {
    toBegin();
}

BoardIterator::~BoardIterator() {}

void BoardIterator::toBegin() {
    row = 0;
    column = 0;
}

void BoardIterator::toEnd() {
    row = board->getNumRows() - 1;
    column = board->getNumColumns() - 1;
}

bool BoardIterator::isBegin() {
    return row == 0 && column == 0;
}

bool BoardIterator::isEnd() {
    return row == board->getNumRows() - 1 && column == board->getNumColumns() - 1;
}

void BoardIterator::next() {
    if (isEnd()) {
        // done iterating whole board
        toBegin();
    } else {
        if (column == board->getNumColumns() - 1) {
            // done a row; go to next row and the 0th column
            row += 1;
            column = 0;
        } else {
            // next column in the row
            column += 1;
        }
    }
}


int BoardIterator::getDisc() {
    return board->getDisc(row, column);
}

int BoardIterator::getUpperDisc(int offset) {
    if (row - offset < 0) {
        // no disc above
        return -1;
    } else {
        return board->getDisc(row - offset, column);
    }
}

int BoardIterator::getLowerDisc(int offset) {
    if (row + offset > board->getNumRows() - 1) {
        // no disc below
        return -1;
    } else {
        return board->getDisc(row + offset, column);
    }
}

int BoardIterator::getLeftDisc(int offset) {
    if (column - offset < 0) {
        // no disc left
        return -1;
    } else {
        return board->getDisc(row, column - offset);
    }
}

int BoardIterator::getRightDisc(int offset) {
    if (column + offset > board->getNumColumns() - 1) {
        // no disc right
        return -1;
    } else {
        return board->getDisc(row, column + offset);
    }
}

int BoardIterator::getUpperLeftDiagonalDisc(int offset) {
    if (getUpperDisc(offset) != -1 && getLeftDisc(offset) != -1) {
        return board->getDisc(row - offset, column - offset);
    }
    return -1;
}

int BoardIterator::getUpperRightDiagonalDisc(int offset) {
    if (getUpperDisc(offset) != -1 && getRightDisc(offset) != -1) {
        return board->getDisc(row - offset, column + offset);
    }
    return -1;
}

int BoardIterator::getLowerLeftDiagonalDisc(int offset) {
    if (getLowerDisc(offset) != -1 && getLeftDisc(offset) != -1) {
        return board->getDisc(row + offset, column - offset);
    }
    return -1;
}

int BoardIterator::getLowerRightDiagonalDisc(int offset) {
    if (getLowerDisc(offset) != -1 && getRightDisc(offset) != -1) {
        return board->getDisc(row - offset, column + offset);
    }
    return -1;
}
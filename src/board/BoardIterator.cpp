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
    row = -1;
    column = -1;
}

bool BoardIterator::isBegin() {
    return row == 0 && column == 0;
}

bool BoardIterator::isEnd() {
    return row == -1 && column == -1;
}

void BoardIterator::next() {
    if (row == board->getNumRows() - 1 && column == board->getNumColumns() - 1) {
        // done iterating whole board
        row = -1;
        column = -1;
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


pair<int, int> BoardIterator::getDiscPosition() {
    return pair<int, int> (row, column);
}

std::pair<int, int> BoardIterator::getUpperDiscPosition(int offset) {
    if (row - offset < 0) {
        // no disc above
        return pair<int, int> (-1, -1);
    } else {
        return pair<int, int> (row - offset, column);
    }
}

std::pair<int, int> BoardIterator::getLowerDiscPosition(int offset) {
    if (row + offset > board->getNumRows() - 1) {
        // no disc below
        return pair<int, int> (-1, -1);
    } else {
        return pair<int, int> (row + offset, column);
    }
}

std::pair<int, int> BoardIterator::getLeftDiscPosition(int offset) {
    if (column - offset < 0) {
        // no disc left
        return pair<int, int> (-1, -1);
    } else {
        return pair<int, int> (row, column - offset);
    }
}

std::pair<int, int> BoardIterator::getRightDiscPosition(int offset) {
    if (column + offset > board->getNumColumns() - 1) {
        // no disc right
        return pair<int, int> (-1, -1);
    } else {
        return pair<int, int> (row, column + offset);
    }
}

std::pair<int, int> BoardIterator::getUpperLeftDiagonalDiscPosition(int offset) {
    if (row - offset < 0 || column - offset < 0) {
        return pair<int, int> (-1, -1);
    }
    return pair<int, int> (row - offset, column - offset);
}

std::pair<int, int> BoardIterator::getUpperRightDiagonalDiscPosition(int offset) {
    if (row - offset < 0 || column + offset > board->getNumColumns() - 1) {
        return pair<int, int> (-1, -1);
    }
    return pair<int, int> (row - offset, column - offset);
}

std::pair<int, int> BoardIterator::getLowerLeftDiagonalDiscPosition(int offset) {
    if (row + offset > board->getNumRows() - 1 || column - offset < 0) {
        return pair<int, int> (-1, -1);
    }
    return pair<int, int> (row - offset, column - offset);
}

std::pair<int, int> BoardIterator::getLowerRightDiagonalDiscPosition(int offset) {
    if (row + offset > board->getNumRows() - 1 || column + offset > board->getNumColumns() - 1) {
        return pair<int, int> (-1, -1);
    }
    return pair<int, int> (row - offset, column - offset);
}
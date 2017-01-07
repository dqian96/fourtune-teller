//
// Created by David Qian on 2017-01-06.
//

#include "Board.h"


using namespace std;

Board::Board(int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        vector<int> row;
        for (int j = 0; j < columns; j++) {
            row.push_back(0);
        }
        board.push_back(row);
    }

}
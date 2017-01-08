//
// Created by David Qian on 2017-01-06.
//

#include <sstream>
#include "Board.h"
#include "Utils.h"

using namespace std;

Board::Board(int rows, int columns): round(0) {
    for (int i = 0; i < rows; i++) {
        vector<int> row;
        for (int j = 0; j < columns; j++) {
            row.push_back(0);
        }
        board.push_back(row);
    }
}

int Board::getNumRows() const {
   return board.size();
}

int Board::getNumColumns() const {
    if (board.size() == 0) {
        return 0;
    } else {
        return board[0].size();
    }
}

void Board::clear() {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            board[i][j] = 0;
        }
    }
}

string Board::toString() const {
    string b = "";
    for (int i = 0; i < board.size(); i++) {
        string row = "";
        for (int j = 0; j < board[i].size(); j++) {
            row += intToStr(board[i][j]);
            if (j != board[i].size() - 1) {
                row += ",";
            }
        }
        if (i != board.size() - 1) {
            row += ";";
        }
        b += row;
    }
    return b;
}
int Board::getDisc(int row, int column) const {
    return board[row][column];
}

void Board::setRound(int r) {
    round = r;
}

int Board::getRound() const {
    return round;
}

bool Board::isValidMove(int column) const {
    if (board.size() == 0) {
        return false;
    }
    return board[0][column] == 0;
}

void Board::placeDisc(int player, int column) {
    for (int i = board.size() - 1; i >= 0; i--) {
        if (board[i][column] == 0) {
            board[i][column] = player;
            break;
        }
    }
}

void Board::updateFromString(std::string s) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            string cell;
            cell.push_back(s[i * board[i].size() * 2 + j * 2]);
            board[i][j] = strToInt(cell);
        }
    }
}


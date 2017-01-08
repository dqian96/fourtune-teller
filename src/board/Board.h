//
// Created by David Qian on 2017-01-06.
//

#ifndef CONNECT_4_BOT_BOARD_H
#define CONNECT_4_BOT_BOARD_H

#include <vector>
#include <string>

class Board {
public:
    Board(int, int);
    std::string getDisc(std::pair<int, int>) const;
    void placeDisc(int, int);
    bool isValidMove(int) const;
    bool isReachableCell(std::pair<int, int>) const;
    bool isValidPosition(std::pair<int, int>) const;
    bool isEmptyCell(std::pair<int, int>) const;
    void clear();
    std::string toString() const;
    void updateFromString(std::string);
    int getNumRows() const;
    int getNumColumns() const;
    void setRound(int);
    int getRound() const;
private:
    std::vector< std::vector<std::string> > board;
    int round;
};

#endif //CONNECT_4_BOT_BOARD_H

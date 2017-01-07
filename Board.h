//
// Created by David Qian on 2017-01-06.
//

#ifndef CONNECT_4_BOT_BOARD_H
#define CONNECT_4_BOT_BOARD_H

#include <vector>

class Board {
public:
    Board(int, int);
    void getDisc(int, int);
    void placeDisc(int);
    void isValidMove(int, int);
    void clear();
private:
    std::vector< std::vector<int> > board;
};

#endif //CONNECT_4_BOT_BOARD_H

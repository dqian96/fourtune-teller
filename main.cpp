#include <iostream>
#include <sstream>
#include <vector>
#include "Board.h"
#include "Bot.h"

using namespace std;

int strToInt(string s) {
    stringstream ss;
    ss << s;
    int i;
    ss >> i;
    return i;
}


int main() {
    Bot* bot;
    gameSettings gs;
    Board* board;
    int boardColumns;
    int boardRows;

    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<string> tokens;
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));

        if (tokens[0] == "settings") {
            if (tokens[1] == "timebank") {
                gs.timebank = strToInt(tokens[2]);
            } else if (tokens[1] == "time_per_move") {
                gs.timePerMove = strToInt(tokens[2]);
            } else if (tokens[1] == "your_bot") {
                gs.name = tokens[2];
            } else if (tokens[1] == "your_botid") {
                gs.id = strToInt(tokens[2]);
            } else if (tokens[1] == "player_names") {
                gs.opponentName = tokens[2].substr(tokens[2].find(","));
            } else if (tokens[1] == "field_rows") {
                boardRows = strToInt(tokens[2]);
            } else if (tokens[1] == "field_columns") {
                boardColumns = strToInt(tokens[2]);
            }
        } else if (tokens[0] == "update") {
            if (board == NULL) {
                board = new Board(boardRows, boardColumns);
            }
            if (bot == NULL) {
                bot = new Bot(gs, board);
            }
            if (tokens[1] == "field") {
                board->update(tokens[2]);
            } else if (tokens[1] == "round") {
                board->nextRound();
            }
        } else if (tokens[0] == "action") {
            if (tokens[1] == "move") {
                int move = bot->makeMove();
                cout << move << endl;
            }
        }
    }

    delete board;
    delete bot;
}
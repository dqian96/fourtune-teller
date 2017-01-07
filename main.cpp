#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

#include "Board.h"
#include "Bot.h"
#include "Utils.h"

using namespace std;

int main() {
    Bot* bot = NULL;
    gameSettings gs;

    Board* board = NULL;
    int boardColumns;
    int boardRows;

    string line;
    while (getline(cin, line)) {

        // tokenizing each line
        istringstream iss(line);
        vector<string> tokens;
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));

        // selecting proper behavior for each command
        if (tokens[0] == "settings") {
            // parsing settings command type
            if (tokens[1] == "timebank") {
                gs.timebank = strToInt(tokens[2]);
            } else if (tokens[1] == "time_per_move") {
                gs.timePerMove = strToInt(tokens[2]);
            } else if (tokens[1] == "your_bot") {
                gs.name = tokens[2];
            } else if (tokens[1] == "your_botid") {
                gs.id = strToInt(tokens[2]);
            } else if (tokens[1] == "player_names") {
                string player1 = tokens[2].substr(tokens[2].find(',') + 1);
                string player2 = tokens[2].substr(0, tokens[2].find(','));
                gs.opponentName = player1 != gs.name ? player1 : player2;
            } else if (tokens[1] == "field_rows") {
                boardRows = strToInt(tokens[2]);
            } else if (tokens[1] == "field_columns") {
                boardColumns = strToInt(tokens[2]);
            }
        } else if (tokens[0] == "update") {
            // parsing game update command type
            if (board == NULL) {
                // create a new board if not done so already
                board = new Board(boardRows, boardColumns);
            }
            if (bot == NULL) {
                // create a new bot if not done so already
                bot = new Bot(gs, board);
            }

            if (tokens[1] == "game") {
                if (tokens[2] == "field") {
                    board->updateFromString(tokens[3]);
                    cout << "Board: " << board->toString() << endl;
                } else if (tokens[2] == "round") {
                    board->setRound(strToInt(tokens[3]));
                }
            }
        } else if (tokens[0] == "action") {
            // parsing action command type
            if (tokens[1] == "move") {
                bot->setTimebank(strToInt(tokens[2]));
                int move = bot->makeMove();
                cout << "place_disc " << move << endl;
            }
        }
    }

    // memory cleanup
    if (board != NULL) {
        delete board;
    }
    if (bot != NULL) {
        delete bot;
    }
}
# Connect 4 Bot

A bot that plays competitive Connect 4 on http://theaigames.com/ .

Sample match ("dqian96_Four" is this bot): http://theaigames.com/competitions/four-in-a-row/games/5873a3594ee9c65266e51347

## AI Algorithm

The bot implements the Minimax algorithm with Alpha-Beta pruning.
Alpha-Beta pruning has been shown to greatly increase the performance of the bot, making a search with p piles
run in around the same time as a search with 2p/3 piles (determined experimentally).


## Heuristics

The heuristic evaluation function used was determined by myself through experimentation and basic
reading of Connect 4 theory. An empty cell is considered a strong threat if playing it would result in a 4-in-a-row (win).
An empty cell is considered a weak threat if playing it would create a strong threat (i.e. a 2-in-a-row that can still
be part of a 4-in-a-row in the future). Each threat is worth a fixed number of points. However, a multiplier
can be applied depending on the following characteristics of the threat; reachability (ability to be immediately played)
and row position (threats on odd rows are valued more). The function evaluates a winning board as +inf or -inf but penializes
the score based on the depth of the search such that wins that require fewer moves are favoured.

The heuristic evaluation function may be calculated in O(n) time, where n is the number of cells on the board.

## Configurations

Typically, the bot looks 5 moves/piles ahead. The number of moves to look ahead may be different depending on the
progress of the game (i.e. search through more piles during end games as average branching factor decreases) and the
time remaining in the time bank.

However, looking ahead 5 moves is actually extremely conservative, since it only takes approx 600 ms on the game server to search the tree
(determined through experimentation).

Since the game server allows for 10000ms and +500ms for each turn, the number of piles could be increased for
more optimal performance.

## TODOs
Heuristic evaluation functon sometimes search empty rows/vertices for threats

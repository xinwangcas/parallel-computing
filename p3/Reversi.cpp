/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
   */

// Original Author      : Keunhong Park
// Original Source      : https://github.com/void42/Reversi

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <time.h>
#include <iomanip>
#include <sys/time.h>
#include "GameBoard.hpp"
#include "AIPlayer.hpp"

#include "GameBoardN.hpp"
#include "AIPlayerNJoin.hpp"
#include "AIPlayerNFor.hpp"
#include "AIPlayerN.hpp"
#include "timing.hpp"

//using namespace std;

/**
 *  Function prototypes
 */
void play(int size, int mode, bool quiet);

/**
 *  Print basic usage
 */
void usage()
{
	printf("Options: -m [1-3] -s[int] -h\n");
	printf("  -s:  size of the board\n");
	printf("  -m:  game mode\n");
	printf("       1 - two human players\n");
	printf("       2 - one human player\n");
	printf("       3 - zero human players\n");
	printf("  -q:  quiet mode\n");
	printf("  -h:  this message\n\n");
	printf("Note: you'll probably want to run with -m 3 -q, and vary -s\n");
}

/**
 * command-line args are "-s" for board size, and "-m" for mode
 */
int main(int argc, char * argv[])
{
	int boardsize = -1;
	int mode = -1;
	bool quiet = false;
	int lookahead = 1;
	int choice = 0;
	// parse the command-line options
	int opt;
	while ((opt = getopt(argc, argv, "s:m:hql:c:")) != -1) {
		switch (opt) {
			case 's': boardsize = atoi(optarg); break;
			case 'm': mode      = atoi(optarg); break;
			case 'q': quiet     = true;         break;
			case 'l': lookahead = atoi(optarg); break;
			case 'c': choice    = atoi(optarg); break;
			case 'h': usage();                  return 0;
		}
	}

	uint64_t start;

	// validate board size
	if (boardsize > 0)
		printf("Board size is: %d x %d\n", boardsize, boardsize);
	else {
		usage();
		return 0;
	}

	// validate mode
	if (mode < 1 || mode < 3) {
		usage();
		return 0;
	}

	// validate quiet
	if (mode == 1)
		quiet = false;

	// create game object
	GameBoard game(boardsize);

	// create any AI agents
	AIPlayer* ai1 = NULL;
	AIPlayer* ai2 = NULL;
	start = getElapsedTime();

	if (mode == 2) {
		ai2 = new AIPlayer(&game,2);
	}
	if (mode == 3) {
		if(choice == 0){
		ai1 = new AIPlayer(&game,1);
		ai2 = new AIPlayer(&game,2);
		}
		if(choice == 1){
		ai1 = new AIPlayerN(&game,1, lookahead);
		ai2 = new AIPlayerN(&game,2, lookahead);
		}
		if(choice == 2){
		ai1 = new AIPlayerNFor(&game,1, lookahead);
		ai2 = new AIPlayerNFor(&game,2, lookahead);
		}
		if(choice == 3){
		ai1 = new AIPlayerNJoin(&game,1, lookahead);
		ai2 = new AIPlayerNJoin(&game,2, lookahead);
		}

	}

	// start main game loop
	if (!quiet) {
		printf("Player 1's turn:\n");
		game.print_board();
	}
	while (game.get_status() != 0) {
		// get player 1 move, display new state, check for victory
		if (ai1 != NULL)
			ai1->play();
		else
			game.get_move(1);
		if (!quiet) {
			game.print_board();
			game.print_scores();
		}
		if (game.check_win(1) == true)
			break;
		// repeat procedure for player 2
		if (ai2 != NULL)
			ai2->play();
		else
			game.get_move(2);
		if (!quiet) {
			game.print_board();
			game.print_scores();
		}
		if (game.check_win(2) == true)
			break;
	}

	// Print final stats
	if (game.get_status() == 0) {
		game.print_board();
		printf("Game over !\n");
		printf("Player 1 score: %d\n",game.get_score(1));
		printf("Player 2 score: %d\n",game.get_score(2));
		int winner = game.determine_winner();
		if (winner == 0)
			printf("Player 1 and Player 2 have TIED.\n");
		else
			printf("Player %d WINS!\n",winner);
	}

	uint64_t end = getElapsedTime();
	cout << "time: " << (end-start) << "(ns)" << endl;
	return 0;
}

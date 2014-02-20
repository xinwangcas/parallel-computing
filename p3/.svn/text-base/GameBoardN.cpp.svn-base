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
#include <cstdio>
#include <cassert>
#include <list>

#include "GameBoardN.hpp"
//using namespace std;

#define CORNER_VALUE 3

/**
 * Construct a board with four intial pieces
 */
GameBoardN::GameBoardN(GameBoard* _game)
{
	score[0] = 0;
	score[1] = 0;
	score[2] = 0;
	
	size = _game->get_size();
	// allocate memory for gameboard matrix
	//assert(size > 2);
	gameboard = new int*[size];
	for (int z = 0; z < size; z++)
		gameboard[z] = new int[size];

	// initialize board by setting all slots to 0
	for (int row = 0; row < size; row++){
		for (int col = 0; col < size; col++)
		{
			this->gameboard[row][col] =  _game->gameboard[row][col];
		}
	}
}

/**
 * Return the status of a slot
 */
int GameBoardN::get_slot_status(int x, int y) const
{
	assert(x >= 0 && y >= 0);
	assert(x <= size && y <= size);
	return gameboard[x][y];
}

/**
 * Getter for size of board
 */
int GameBoardN::get_size() const
{
	return size;
}

/**
 * indicates whether a move is valid
 */
bool GameBoardN::is_valid_move(int x, int y, int player) const
{
	assert(x >= 0 && y >= 0);
	assert(x <= size && y <= size);

	// check if slot is already taken
	if (get_slot_status(x,y) != 0)
		return false;

	// must flip more than 0 stones
	return (flip_count(x, y, player) > 0);
}

//change player to opponent
int GameBoardN::opponent(int player)
{
	if (player == 1)
		return 2;
	if (player == 2)
		return 1;
	else
		return 0;
}
/**
 * assign a slot to a player
 */
void GameBoardN::set_slot(int x, int y, int player)
{
	assert(x >= 0 && y >= 0);
	assert(x <= size && y <= size);
	gameboard[x][y] = player;
	change_score(1, player);
}

void GameBoardN::unset_slot(int x, int y, int player)
{
	assert(x >= 0 && y >= 0);
	assert(x <= size && y <= size);
	gameboard[x][y] = 0;
	change_score(-1, player);
}
/**
 * Count number of flips a move will make
 */
int GameBoardN::flip_count(int x, int y, int player) const
{
	assert(x >= 0 && y >= 0);
	assert(x <= size && y <= size);

	// dir_x and dir_y are each -1, 0, or 1 to change the direction of the search
	// this way, every possible move is considered.
	//
	// dist is for the length of the search
	// dist = 1 searches one slot away, dist = 2 searches 2 slots away
	//
	// cur_x and cur_y are temporary variables to store the temporary
	// positions being searched while looping through the possibilities
	int dir_x, dir_y, dist = 1, cur_x = x, cur_y = y, flip_count = 0;

	// these nested for loops consider -1, 0, and 1 for dir_x and dir_y
	for (dir_x = -1; dir_x < 2; dir_x++) {
		for (dir_y = -1; dir_y < 2; dir_y++) {
			// set initial dist to 1 and increment only if the slot tested before
			// is the opponent's stone
			dist = 1;
			while (true) {
				// dir_x and dir_y only set the direction (-1, 0, or 1)
				cur_x = x + (dist * dir_x);
				cur_y = y + (dist * dir_y);

				// break current loop if it goes off board
				if (cur_x < 0 || cur_y < 0 || cur_x >= size || cur_y >= size)
					break;

				// break current loop if the slot is blank
				// since no slots after will be able to be taken anyway
				if (gameboard[cur_x][cur_y] == 0)
					break;

				// if the stone is the current player's stone
				// increment flip count by the distance minus one
				// since the slots preceding the current slot would be flipped
				if (gameboard[cur_x][cur_y] == player) {
					flip_count += dist - 1;
					break;
				}

				// break if (dir_x,dir_y) = (0,0) since it'll go into an infinite loop
				if (dir_x == 0 && dir_y == 0)
					break;
				dist++;
			}
		}
	}
	return flip_count;
}

/**
 * Try to flip slots according to a move
 */
list<pair<int ,int> > GameBoardN::tryflip_slots(int x, int y, int player)
{
	assert(x >= 0 && y >= 0);
	assert(x <= size && y <= size);

	std::list<pair<int, int> > tmplist;
	// see flip_count... this is the same, except it actually flips slots
	int dir_x, dir_y, dist = 1, cur_x = x, cur_y = y;
	for (dir_x = -1; dir_x < 2; dir_x++) {
		for (dir_y = -1; dir_y < 2; dir_y++) {
			dist = 1;
			while (true) {
				cur_x = x + (dist * dir_x);
				cur_y = y + (dist * dir_y);
				if (cur_x < 0 || cur_y < 0 || cur_x >= size || cur_y >= size)
					break;

				if (gameboard[cur_x][cur_y] == 0)
					break;

				if (gameboard[cur_x][cur_y] == player) {
					// backtrace moves and flip opponent's slots
					// decrement dist and flip until dist is 0
					for (dist--; dist > 0; dist--) {
						cur_x = x + (dist * dir_x);
						cur_y = y + (dist * dir_y);
						set_slot(cur_x, cur_y, player); // flip slot
						tmplist.emplace_back(cur_x,cur_y);
						change_score(-1,(player == 1)?2:1);
					}
					break;
				}
				// break if (dir_x,dir_y) = (0,0) since it'll go into an infinite loop
				if (dir_x == 0 && dir_y == 0)
					break;
				dist++;
			}
		}
	}
	return tmplist;
}

pair<list<pair<int, int> >,bool> GameBoardN::try_move(int x, int y, int player)
{
	assert(x >= 0 && y >= 0);
	assert(x <= size && y <= size);

	if (is_valid_move(x,y,player) == true) {
		set_slot(x,y,player);
		return pair<list<pair<int, int> >, bool>(tryflip_slots(x,y,player), true);
	}
	return pair<list<pair<int, int> >, bool >(list<pair<int, int>>(), false);
}

bool GameBoardN::undo_move(int x, int y, int player, list<pair<int, int> > &a)
{
	assert(x >= 0 && y >= 0);
	assert(x <= size && y <= size);

	unset_slot(x,y,player);
	for (auto &i: a){
		if(gameboard[i.first][i.second] != 0)
			gameboard[i.first][i.second] = opponent(gameboard[i.first][i.second]);
		change_score(-1,player);
		change_score(1,opponent(player));
	}
	return true;
}

/**
 * Determine if any moves remain
 */
bool GameBoardN::moves_exist(int player) const
{
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			if (get_slot_status(x,y) != 0){
				continue;
				
			}
			if (flip_count(x,y,player) > 0){
				return true;
			}
		}
	}
	return false;
}

int GameBoardN::moves_num(int player)
{
	int n = 0;
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			if (get_slot_status(x,y) != 0)
				continue;
			if (flip_count(x,y,player) > 0)
				n ++ ;
		}
	}
	return n;
}

/**
 * Query user to get next move
 */
bool GameBoardN::get_move(int player)
{
	int x, y;
	while (true) {
		printf("Player %d's turn: \n",player);
		printf("Input x: ");

		// get x coordinate
		std::cin >> x;
		// sanitate input
		if (std::cin.fail()) {
			std::cin.clear();
			std::string garbage;
			std::getline(std::cin, garbage);
			printf("Invalid input: x value must be an integer.\n");
		}
		else if (x > size || x < 1) {
			std::cin.clear();
			printf("Invalid input: x value but be between 1 and %d.\n",size);
		}
		else {
			// get y coordinate
			printf("Input y: ");
			std::cin >> y;
			// sanitate input
			if (std::cin.fail()) {
				std::cin.clear();
				std::string garbage;
				std::getline(std::cin, garbage);
				printf("Invalid input: y value must be an integer.\n");
			}
			else if (y > size || y < 1) {
				std::cin.clear();
				printf("Invalid input: y must be between 1 and %d.\n",size);
			}
			else {
				bool move = make_move(x-1,y-1,player);
				if (move == false) {
					printf("Invalid move, try again.\n");
					continue;
				}
				return true;
			}
		}
	}
}

int GameBoardN::rate_stability(int player)
{
	int n = 0;
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			if(gameboard[x][y] == player)
			{
				if ((x == 0) || (x == (size - 1)))
					n += CORNER_VALUE;
				if ((y == 0) || (y == (size - 1)))
					n += CORNER_VALUE;

				// discourage giving corner to opponent
				if ((x == 1) || (x == (size - 2)))
					n -= CORNER_VALUE;
				if ((y == 1) || (y == (size - 2)))
					n -= CORNER_VALUE;
			}
		}
	}
	return n;

}

/**
 * Getter for a player's score
 */
int GameBoardN::get_score(int player) const
{
	return score[player];
}

/**
 * getter for number of free slots (0s) on the board
 */
int GameBoardN::count_free_slots() const
{
	int count = 0;
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
			count += ((get_slot_status(x, y) == 0) ? 1 : 0);
	return count;
}

/**
 * getter for number of slots owned by a player
 */
int GameBoardN::count_player_slots(int player) const
{
	int count = 0;
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
			count += ((get_slot_status(x, y) == player) ? 1 : 0);
	return count;
}

/**
 * Change a player's score
 */
void GameBoardN::change_score(int change, int player)
{
	score[player] += change;
}

void GameBoardN::print_board() const
{
    printf("Current boardN:\n");
    printf("\n\t");
    for (int z = 0; z < size; z++) {
        printf("%d ",z+1);
    }
    printf("\n\n");
    for (int y = 0; y < size; y++) {
        printf("   %d\t",y+1);
        for (int x = 0; x < size; x++) {
            printf("%d ",get_slot_status(x,y));
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Free memory on destruction
 */
GameBoardN::~GameBoardN()
{
	delete []gameboard;
}

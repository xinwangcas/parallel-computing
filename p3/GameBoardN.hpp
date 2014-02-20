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

#ifndef GAMEBOARDN_HPP__
#define GAMEBOARDN_HPP__
#include "GameBoard.hpp"
#include <list>
using namespace std;

class GameBoardN: public GameBoard
{
	public:
		// the matrix representing the board
		int** gameboard;

		// the size of the board
		int size;

		// for tracking score
		int score[3];
		bool status;

		void set_slot(int x, int y, int player);
		void unset_slot(int x, int y, int player);
		void change_score(int change, int player);
		bool moves_exist(int player) const;
		int count_free_slots() const;
		int count_player_slots(int player) const;
		int opponent(int player);

	public:
		GameBoardN(GameBoard* game = NULL);
		virtual ~GameBoardN();
		int get_size() const;
		int get_slot_status(int x, int y) const;
		bool is_valid_move(int x, int y, int player) const;
		int rate_stability(int player);
		int moves_num(int player);
		int flip_count(int x, int y, int player) const;
		int tryflip_cout(int x, int y, int player);
		int get_score(int player) const;
		pair<list<pair<int, int> >,bool> try_move(int x, int y, int player);

		bool undo_move(int x, int y, int player, list<pair<int, int> > &a);
		list<pair<int ,int> > tryflip_slots(int x, int y, int player);
		bool undo_move(int x, int y, int player);
		void print_board() const;
		bool get_move(int player);
};

#endif // GAMEBOARDN_HPP__

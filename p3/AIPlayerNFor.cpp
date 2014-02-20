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
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <vector>

#include "GameBoardN.hpp"
#include "GameBoard.hpp"
#include "AIPlayerNFor.hpp"

#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
using namespace tbb;
/**
 *  When scoring moves, this is the benefit of taking a corner
 */
#define CORNER_VALUE 3
struct tri{
	int m;
	int n;
	int k;
};

struct Parallel{
	AIPlayerNFor* ap;
	vector<tri>* vect;
	void operator()(const blocked_range<int>& range)const{
		for (int i = range.begin() ; i != range.end() ; i++){
			int a = -10000;
			int b = 10000;
			GameBoardN* board = new GameBoardN(ap->game);
			pair<list<pair<int, int> >, bool > mm = board->try_move((*vect)[i].m, (*vect)[i].n, ap->player);
			if(mm.second){
				(*vect)[i].k = ap->alpha_beta_pruning(a, b, ap->la, board,ap->opponent(ap->player));
			//	cout << "vect[i].k: " << (*vect)[i].k << endl;
			}
			delete board;
		}
	}
	Parallel(AIPlayerNFor* aip, vector<tri> *vec):ap(aip),vect(vec){}
};
/**
 *  Constructor for AIPlayer
 */

AIPlayerNFor::AIPlayerNFor(GameBoard* _game, int _player, int l):AIPlayer(_game, _player)
{la = l; }
int AIPlayerNFor::evaluation(int player, GameBoardN* board)
{
	int mobility = (board->moves_num(player)-(board->moves_num(board->opponent(player))));
	int scores = board->get_score(player)-board->get_score(board->opponent(player));
	int stability = board->rate_stability(player)-board->rate_stability(board->opponent(player));
//	cout << "mobility: " << mobility << " stability: " << stability << " scores: " << scores << endl;
	return mobility+stability+scores;	
}

/**
 *  Determine the quality of a move, by giving it a score
 *
 *  This is a pretty weak AI function... we could do a lot better with
 *  lookahead...
 */

int AIPlayerNFor::opponent(int player){
	if (player == 1)
		return 2;
	else
		return 1;
}

int AIPlayerNFor::alpha_beta_pruning(int a, int b, int depth, GameBoardN* board, int player) 
{
	//	cout << " a = " << a << " b = " << b << " depth = " << depth << " player = " << player << endl;
	//	board->print_board();
	int best_value = -10000;
	//when the search depth has reached to 0, return the evaluation
	if(depth <= 0){
		return evaluation(player,board);
	}

	//if the current move is legal
	for (int x = 0 ; x < board->get_size() ; x ++ ){
		for(int y = 0 ; y < board->get_size() ; y ++ ){
			pair<list<pair<int ,int > >, bool> m = board->try_move(x,y,player);
			if(m.second){
				int value = -alpha_beta_pruning(-b, -a, depth-1, board, opponent(player));
				(board)->undo_move(x, y, player, m.first);
				if(value >= b)
					return value;
				if (value >= best_value){
					best_value = value;
					if(value > a)
						a = value;
				}
			}
		}
	}

	if (best_value == -10000)
	{
		best_value = evaluation(player,board);
		/*
		   if(!board->moves_exist(player)&&!board->moves_exist(opponent(player)))
		   {
		   return evaluation(player,board);
		   }
		   best_value = -alpha_beta_pruning(-b, -a, depth-1,board, opponent(player));
		   return best_value;
		   */
	}

	return best_value;
}


/**
 *  Use brute force to evaluate every possible move, and find the best one.
 *  Once the best move is found, play it.
 */
void AIPlayerNFor::play()
{
	int x = 0,
	    y = 0,
	    cur_max = -10000,
	    best_x = 0,
	    best_y = 0;

	vector<tri> vec;
	for (x = 0; x < game->get_size(); x++) {
		for (y = 0; y < game->get_size(); y++) {
			if(game->is_valid_move(x,y,player))
			{
				tri t;
				t.m = x;
				t.n = y;
				t.k = cur_max;
				vec.push_back(t);
			}
		}
	}
	Parallel pa(this, &vec);
	parallel_for(blocked_range<int>(0, vec.size(), 1),pa);

	for(unsigned int i = 0 ; i < vec.size(); i ++ ){
		int temp = vec[i].k;
	//	cout << "i: "<< i <<" vec[i].m: " << vec[i].m << " vec[i].n: " << vec[i].n << " k: " << vec[i].k << endl;
		// if this move is better, choose it
		if (temp > cur_max) {
			cur_max = temp;
			best_x = vec[i].m;
			best_y = vec[i].n;
		}
	}
//	cout << "best_x: " << best_x << " best_y: "<< best_y << " player: " << player << endl;
	game->make_move(best_x,best_y,player);
}

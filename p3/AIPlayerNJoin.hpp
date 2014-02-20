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

#ifndef AIPLAYERNJOIN_HPP__
#define AIPLAYERNJOIN_HPP__
#include "AIPlayer.hpp"

class AIPlayerNJoin: public AIPlayer
{
    /**
     *  Internal method to score a move
     */
//    virtual int rate_move(int x, int y) const;

  public:
    /**
     *  Constructor just stores a reference to the game, and stores the player
     *  ID
     */
    int la;
    AIPlayerNJoin(GameBoard* game, int player, int la);
    int evaluation(int player, GameBoardN* board);
    int alpha_beta_pruning(int a, int b, int depth, GameBoardN* board, int player);
    int opponent(int player);
    /**
     *  Tell the player to find the best move and make it
     */
    virtual void play();
};

#endif // AIPLAYER_HPP__

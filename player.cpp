#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side1) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    board = new Board();
    dupboard = new Board();
    side = side1;
    score = 2;
    tempscore = 2;
    if (side == WHITE)
    {
		opponentSide = BLACK;
	}
	else
	{
	    opponentSide = WHITE;	
	}
	tempmove = NULL;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {     
    if (opponentsMove != nullptr) {
        dupboard->doMove(opponentsMove, opponentSide);
        board->doMove(opponentsMove, opponentSide);
	}
    for (int i = 0; i < 8; i++) {
	    for (int j = 0; j < 8; j++) { 
		    tempmove = new Move(i,j); 

			if (board->checkMove(tempmove, side)) {
				dupboard->doMove(tempmove,side);
                
				if (side == WHITE) {
				    tempscore = dupboard->countWhite() - dupboard->countBlack();
				}
				else {
				    tempscore = dupboard->countBlack() - dupboard->countBlack();
				}
                newmove = tempmove;
                score = tempscore;
                break;
            }			 
        }
    }
	if (newmove != nullptr) {
	    board->doMove(newmove, side);
		dupboard->doMove(newmove, side);
		return newmove;
    }
    fprintf(stderr, "GOT HERE\n");
    return nullptr;
}

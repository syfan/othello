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

std::vector<Move*> Player::getPossibleMoves(Board *board) {
    std::vector<Move*> moves;
    for (int i = 0; i < 8; i++) {
	    for (int j = 0; j < 8; j++) { 
		    tempmove = new Move(i,j); 

			if (board->checkMove(tempmove, side)) {
				dupboard->doMove(tempmove, side);
                moves.push_back(tempmove);
            }			 
        }
    }
    return moves;
}

int Player::getHeur(Board *board, Move *move) {
	int temp = 0;
	if (side == WHITE) {
		temp = board->countWhite() - board->countBlack();
	}
	else {
		temp = board->countBlack() - board->countWhite();
	}
	if ((move->getX() == 0 &&  move->getY() == 0) ||
		(move->getX() == 7 && move->getY() == 0) ||
		(move->getX() == 7 && move->getY() == 7) ||
		(move->getX() == 0 && move->getY() == 7)) {
			temp = temp * 3;
	}
	else if ((move->getX() == 0 &&  move->getY() == 1) ||
		(move->getX() == 1 && move->getY() == 0) ||
		(move->getX() == 0 && move->getY() == 6) ||
		(move->getX() == 1 && move->getY() == 7) ||
		(move->getX() == 6 && move->getY() == 0) ||
		(move->getX() == 7 && move->getY() == 1) ||
		(move->getX() == 6 && move->getY() == 7) ||
		(move->getX() == 7 && move->getY() == 6)) {
			temp = temp * -3;
	}
	return temp;
}
 
Move *Player::doMove(Move *opponentsMove, int msLeft) {     
    if (opponentsMove != nullptr) {
        dupboard->doMove(opponentsMove, opponentSide);
        board->doMove(opponentsMove, opponentSide);
	}
    std::vector<Move*> possibleMoves = getPossibleMoves(board);
    
    int best = 0;
    int best_ind = 0;
	if (possibleMoves.size() != 0) {
        for (unsigned int i = 0; i < possibleMoves.size(); i++) {
			int temp_heur = getHeur(dupboard, possibleMoves[i]);
			if (temp_heur > best) { 
				// finding move with best heuristic score
				best = temp_heur;
				best_ind = i;
			}
		}
        
        newmove = possibleMoves[best_ind];
        
	    board->doMove(newmove, side);
		dupboard->doMove(newmove, side);
		return newmove;
    }
    return nullptr;
}

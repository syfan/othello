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
 * Finds all of the legal moves that can be made, given a board and a side.
 */

std::vector<Move*> Player::getPossibleMoves(Board *board1, Side side1) {
    std::vector<Move*> moves;
    for (int i = 0; i < 8; i++) {
	    for (int j = 0; j < 8; j++) { 
		    tempmove = new Move(i,j); 

			if (board1->checkMove(tempmove, side1)) {
                moves.push_back(tempmove);
            }			 
        }
    }
    return moves;
}

/*
 * Returns the heuristic score when given a board and the move that's 
 * currently being considered.  It accounts for the strategic advantages
 * in taking corners and edges and disadvantages in giving access to
 * corners.
 */
int Player::getHeur(Board *board1, Move *move) {
	int yours, theirs;
	if (side == WHITE) {
		yours = board1->countWhite();
		theirs = board1->countBlack();
	}
	else {
		yours = board1->countBlack();
		theirs = board1->countWhite();
	}
	if ((move->getX() == 0 &&  move->getY() == 0) ||
		(move->getX() == 7 && move->getY() == 0) ||
		(move->getX() == 7 && move->getY() == 7) ||
		(move->getX() == 0 && move->getY() == 7)) {
			yours = yours * 4;
	}
	else if ((move->getX() == 0 &&  move->getY() == 1) ||
		(move->getX() == 1 && move->getY() == 0) ||
		(move->getX() == 0 && move->getY() == 6) ||
		(move->getX() == 1 && move->getY() == 7) ||
		(move->getX() == 6 && move->getY() == 0) ||
		(move->getX() == 7 && move->getY() == 1) ||
		(move->getX() == 6 && move->getY() == 7) ||
		(move->getX() == 7 && move->getY() == 6)) {
			yours = yours * -2;
	}
	else if ((move->getX() == 1 &&  move->getY() == 1) ||
		(move->getX() == 6 && move->getY() == 1) ||
		(move->getX() == 1 && move->getY() == 6) ||
		(move->getX() == 6 && move->getY() == 6)) {
			yours = yours * -4;			
	}
	else if (move->getX() == 0 || move->getX() == 7 ||
		move->getY() == 0 || move->getY() == 7) {
			yours = yours * 2;
	}
	return yours - theirs;
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
	// the current AI beats simple player about 85% of the time  
    if (opponentsMove != nullptr) {
        dupboard->doMove(opponentsMove, opponentSide);
        board->doMove(opponentsMove, opponentSide);
	}
    std::vector<Move*> possibleMoves = getPossibleMoves(board, side);
    
    int best = -100000;
	if (possibleMoves.size() != 0) {
        for (unsigned int i = 0; i < possibleMoves.size(); i++) {
			int temp_heur = getHeur(dupboard, possibleMoves[i]);
			if (temp_heur > best) { 
				// finding move with best heuristic score
				best = temp_heur;
				newmove = possibleMoves[i];
			}
		}
        
	    board->doMove(newmove, side);
		dupboard->doMove(newmove, side);
		return newmove;
    }
    return nullptr;
}

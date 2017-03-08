#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    std::vector<Move*> getPossibleMoves(Board *board);
    Side side; // to keep track of side
    Side opponentSide;
    
    int score;
    int tempscore;
    Board *board;
    Board *dupboard;
    
    Move *tempmove;
    Move *newmove;
    
    int getHeur(Board *board, Move *move);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif

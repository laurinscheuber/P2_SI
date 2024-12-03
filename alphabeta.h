#ifndef _ALPHABETA_H
#define _ALPHABETA_H

#include "otello.h"
float Alphabeta(Player pl, Board b, unsigned depth, bool maximizingPlayer, float alpha, float beta, Move &best_move);
#endif

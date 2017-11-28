#include "game.h"
#include "board.h"
#include <string.h>

#define NEG_INFINITY -1000
#define POS_INFINITY 1000

int maxAB(int board[], int cutoff, int depth, int alpha, int beta, int user_score, int ai_score);
int minAB(int board[], int cutoff, int depth, int alpha, int beta, int user_score, int ai_score);
int cutoff = 2;

void ABSearch(int board[], int cutoff, int user_score, int ai_score){
  maxAB(board, cutoff, 0, NEG_INFINITY, POS_INFINITY, user_score, ai_score);
}

int maxAB(int board[], int cutoff, int depth, int alpha, int beta, int user_score, int ai_score){
  // ai, player 0
  int copy_board[12], tmp_board[12];
  if (depth == cutoff)
    return ai_score - user_score;
  int i, tmp;
  int optinum_val = NEG_INFINITY;
  int list_step[20];
  int v;
  int depth_next =depth +  1;
  int len_list_step = get_list_step_true(copy_board, 0, list_step);
  for(i=0; i < len_list_step; i++){
    memcpy(copy_board, board, sizeof(int) * 12);
    tmp = move_iter(copy_board, list_step[i], 0);
    ai_score = tmp + ai_score;
    v = minAB(copy_board, cutoff, depth_next, alpha, beta, user_score, ai_score);
    if (optinum_val == NEG_INFINITY || v > optinum_val){
      memcpy(tmp_board,copy_board, sizeof(int) * 12);
      optinum_val = v;
      
   }
    if (beta != POS_INFINITY && v >= beta){
      memcpy(board, tmp_board, sizeof(int) * 12); 
      return v;
    }
    
    if (alpha == NEG_INFINITY || v > alpha)
      alpha = v;
  }
  memcpy(board, tmp_board, sizeof(int) * 12); 
  return optinum_val;
  
}


int minAB(int board[], int cutoff, int depth, int alpha, int beta, int user_score, int ai_score){
  // user, player 1
  int copy_board[12], tmp_board[12];
  if (depth == cutoff)
    return user_score - ai_score;
  int i, tmp;
  int optinum_val = POS_INFINITY;
  int list_step[20];
  int v;
  int depth_next =depth +  1;
  int len_list_step = get_list_step_true(copy_board, 1, list_step);
  for(i=0; i < len_list_step; i++){
    memcpy(copy_board, board, sizeof(int) * 12);
    tmp = move_iter(copy_board, list_step[i], 0);
    user_score = tmp + user_score;
    v = maxAB(copy_board, cutoff, depth_next, alpha, beta, user_score, ai_score);
    if (optinum_val == POS_INFINITY || v < optinum_val){
      memcpy(tmp_board,copy_board, sizeof(int) * 12);
      optinum_val = v;
      
   }
    if (alpha != NEG_INFINITY && v <= alpha){
      memcpy(board, tmp_board, sizeof(int) * 12);
      return v;
    }
    
    if (beta == POS_INFINITY || v < beta)
      beta = v;
  }
  memcpy(board, tmp_board, sizeof(int) * 12); 
  return optinum_val;
}


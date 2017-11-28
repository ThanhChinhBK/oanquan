#include "game.h"
#include "board.h"
#include <string.h>

int greedy(int board[]){
  int optinum = -1, total_step, optinum_score=-1;
  int list_step[20];
  int i, tmp_score;
  int copy_board[12];
  total_step =  get_list_step_true(board, 0, list_step);
  for(i=0; i < total_step; i++){
    memcpy(copy_board, board, sizeof(int)*12);
    tmp_score = move_iter(copy_board, list_step[i], 0);
    if(optinum == -1 || optinum_score < tmp_score){
      optinum = list_step[i];
      optinum_score = tmp_score;
    }

    
  }
  return optinum;
}

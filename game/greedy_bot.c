#include "game.h"
#include "board.h"

int greedy(int board[]){
  int optinum = -1, total_step, optinum_score=-1;
  int list_step[20];
  int i, tmp_score;
  total_step =  get_list_step_true(board, 0, list_step);
  for(i=0; i < total_step; i++){
    tmp_score = move_iter(board, list_step[i], 0);
    if(optinum == -1 || optinum_score < tmp_score)
      optinum = list_step[i];
  }
  return optinum;
}

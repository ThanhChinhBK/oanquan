#include "game.h"

void print_board(int s[]){
  printf("+---------------------------+\n");
  printf("|   |%3d|%3d|%3d|%3d|%3d|   |\n",s[1],s[2],s[3],s[4],s[5]);
  printf("|%3d|-------------------|%3d|\n",s[0],s[6]);
  printf("|   |%3d|%3d|%3d|%3d|%3d|   |\n",s[11],s[10],s[9],s[8],s[7]);
  printf("+---------------------------+\n");
}

int get_direct(int step){ // 1 if right, -1 if left
  return step / abs(step);
}

int step_transform(int postion, int direct){
  return postion * direct;
}

int check_step_true(int board[], int step, int side){
  int list_step[20];
  int len_list_step = get_list_step_true(board, side, list_step);
  int i;
  //int check = 0
  for(i=0; i < len_list_step; i++){
    if(step == list_step[i])
                 return 1;
  }
  return 0;
}

int get_list_step_true(int board[], int side, int *list_step){
  // if user side = 1, if ai size = 0
  int i, count=0;
  if(side==1){ //user
    for(i=0; i<5;i++)
      if(board[user_move[i]] != 0){
        list_step[count] = user_move[i];
        list_step[count+1] = -user_move[i];
        count += 2;
      }
  }
  if(side==0){ //ai
    for(i=0; i<5;i++)
      if(board[ai_move[i]] != 0){
        list_step[count] = ai_move[i];
        list_step[count+1] = -ai_move[i];
        count += 2;
      }
  }
  return count-1;
}

int get_sum_units(int board[], int side){
  // if user side = 1, if ai size = 0
  int i,sum_units=0;
  for(i=0;i<5;i++){
    if(side==1)
      sum_units += board[user_move[i]];
    else
      sum_units += board[ai_move[i]];
  }
  return sum_units;
}

int check_board_status(int board[]){
  // won return 1, not yet return 0
  if(board[quan[0]] == 0 && board[quan[1]] == 0)
    return 1;
  else if(get_sum_units(board, 0) == 0 || get_sum_units(board,1) == 0)
    return 1;
  else
    return 0;
}

int get_final_score(int board[], int side, int score){
  int i = 0;
  for(i=0;i<5;i++){
    if(side==1)
      score += board[user_move[i]];
    else
      score += board[ai_move[i]];
  }
  return score;
} 

int is_quan(int postion){
  if(postion == 0 || postion == 1)
    return 1;
  return 0;
}

int move_iter(int board[], int step, int print){ 
  // print = 1 if print board, print = 0 if not
  int direct = get_direct(step);
  int postion = abs(step);
  int score = 0;
  int next_postion = 0, next_next_postion = 0;
  int num_units = board[step];
  int matluot = 0;
  board[postion] = 0;
  while(! matluot){
    if(num_units > 0){
      postion += direct;
      postion %= 12;
      num_units--;
      board[postion]++;
    }
    if(num_units == 0){
      next_postion = (postion + direct) % 12;
      next_next_postion = (next_postion + direct) % 12;
      if (is_quan(next_postion) ||
          (board[next_postion] == 0 && board[next_next_postion] == 0)){
        matluot = 1;
        if(print)
          printf("***MAT LUOT (Gap O QUAN hoac 2 O TRONG)");
        break;
      }
      
      if (board[next_postion] == 0 && board[next_next_postion] > 0){
        score += board[next_next_postion];
        if(print)
          printf("an %d:%d, mat luot", next_postion, board[next_next_postion]);
        board[next_next_postion] = 0;
        matluot = 1;
        break;
      }

      if (board[next_postion] > 0){
        num_units = board[next_postion];
        board[next_postion] = 0;
        postion = next_postion;        
        if(print){
          print_board(board);
          printf("***BOC TIEP %d:%d-%d", num_units, postion,direct);     \
          printf("-----------------------------------\n");
        }
      }
          
    }
  }
  if(print){
    print_board(board);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  }
  return score;
} 

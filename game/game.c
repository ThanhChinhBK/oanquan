#include <game.h>

void print_board(int s[]){
  printf("+---------------------------+\n");
  printf("|   |%3d|%3d|%3d|%3d|%3d|   |\n",s[1],s[2],s[3],s[4],s[5]);
  printf("|%3d|-------------------|%3d|\n",s[0],s[6]);
  printf("|   |%3d|%3d|%3d|%3d|%3d|   |\n",s[11],s[10],s[9],s[8],s[7]);
  printf("+---------------------------+\n");
}

int check_direct(int step){ // 1 if right, -1 if left
  return step / abs(step);
}

int step_transform(int postion, int direct){
  return postion * direct;
}

int check_step_true(int step, int list_step[], int len_list_step){
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

int check_board_status(int board[]){
  // won return 1, not yet return 0
}

  

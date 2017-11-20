#include "board.h"


int game_board[] = {10,5,5,5,5,5,10,5,5,5,5,5};
char luat_choi[] = "Nguoi dung di cac o duoi,\nMay di cac o tren,\nmat luot khi an quan, gap o trong hoac gap o quan\n";


int get_user_step(void){
  int step, postion, direct;
  while(1){
    while(1){
      __fpurge(stdin);
      printf("Nhap vao vi tri muon di chuyen(1-5):");
      scanf("%d", &postion);
      if(postion >=1 && postion <= 5)
        break;
    }
    while(1){
      __fpurge(stdin);
      printf("Nhap vao huowng muon di chuyen(-1:trai,1:phai):");
      scanf("%d", &direct);
      if(direct ==1 || direct == -1)
        break;
    }
    step = postion * direct;    
    if (check_step_true(game_board, step, 1))
      break;
    else
      printf("step khong nam trong so step thoa man\n");
  }
  return step;
}

int get_ai_random_step(void){
  int list_step[20];
  int len_list_step = get_list_step_true(game_board, 0, list_step);
  int r = rand() % len_list_step;
  return list_step[r];
}

void stand_alone_game(void){
  int user_turn = 1;
  int step, user_score = 0, ai_score=0;
  int tmp_score;
  print_board(game_board);
  while(!check_board_status(game_board)){
    if(user_turn > 0){
      step = get_user_step();
      tmp_score = move_iter(game_board, step, 1);
      user_score += tmp_score;
    }
    else {
      step = get_ai_random_step();
      tmp_score = move_iter(game_board, step, 1);
      ai_score += tmp_score;
    }
    user_turn *= -1;
  }
  user_score = get_final_score(game_board, 1, user_score);
  ai_score = get_final_score(game_board, 0, ai_score);
  printf("final result: %d-%d\n", user_score, ai_score);
}

void start(void){
  stand_alone_game();
}

int main(int argc, char* argv[]){
  start();
  return 1;
}

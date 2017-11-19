#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int user_move[] = {1,2,3,4,5};
const int ai_move[] = {7,8,9,10,11};
const int quan[] = {0,6};

void print_board(int s[]);
int get_direct(int step);
int step_transform(int postion, int direct);
int check_step_true(int board[], int step, int side);
int get_list_step_true(int board[], int side, int *list_step);
int get_sum_units(int board[], int side);
int check_board_status(int board[]);
int get_final_score(int board[], int side, int score);
int is_quan(int postion);
int move_iter(int board[], int step, int print);

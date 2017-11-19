#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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

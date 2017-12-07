#include "game.h"

const int user_move[] = {1, 2, 3, 4, 5};
const int ai_move[] = {7, 8, 9, 10, 11};
const int quan[] = {0, 6};

int game_board[] = {10,5,5,5,5,5,10,5,5,5,5,5};
char luat_choi[] = "Nguoi dung di cac o duoi,\nMay di cac o tren,\nmat luot khi an quan, gap o trong hoac gap o quan\n";
char buffer[BUFFER_LENGTH];
char *str;

void print_board(int sock, int s[])
{
    asprintf(&str, 
        "+---------------------------+\n"
        "|   |%3d|%3d|%3d|%3d|%3d|   |\n"
        "|%3d|-------------------|%3d|\n"
        "|   |%3d|%3d|%3d|%3d|%3d|   |\n"
        "+---------------------------+\n",
        s[1], s[2], s[3], s[4], s[5],
        s[0], s[6],
        s[11], s[10], s[9], s[8], s[7]);

    toClient(sock, str);
}

int get_direct(int sock, int step)
{ // 1 if right, -1 if left
    return step > 0 ? 1 : -1;
}

int step_transform(int sock, int postion, int direct)
{
    return postion * direct;
}

int check_step_true(int sock, int board[], int step, int side)
{
    // if user side = 1, if ai size = 0
    int list_step[20];
    int len_list_step = get_list_step_true(sock, board, side, list_step);
    int i;
    //int check = 0
    for (i = 0; i < len_list_step; i++) {
        if (step == list_step[i])
            return 1;
    }
    return 0;
}

int get_list_step_true(int sock, int board[], int side, int *list_step) {
    // if user side = 1, if ai size = 0
    int i, count = 0;
    if (side == 1) { //user
        for (i = 0; i < 5; i++) {
            if (board[user_move[i]] != 0) {
                list_step[count] = user_move[i];
                list_step[count + 1] = -user_move[i];
                count += 2;
            }
        }
    }
    if (side == 0) { //ai
        for (i = 0; i < 5; i++) {
            if (board[ai_move[i]] != 0) {
                list_step[count] = ai_move[i];
                list_step[count + 1] = -ai_move[i];
                count += 2;
            }
        }
    }
    return count - 1;
}

int get_sum_units(int sock, int board[], int side) {
    // if user side = 1, if ai size = 0
    int i, sum_units = 0;
    for (i = 0; i < 5; i++) {
        if (side == 1)
            sum_units += board[user_move[i]];
        else
            sum_units += board[ai_move[i]];
    }
    return sum_units;
}

int check_board_status(int sock, int board[]) {
    // won return 1, not yet return 0
    if (board[quan[0]] == 0 && board[quan[1]] == 0)
        return 1;
    else if (get_sum_units(sock, board, 0) == 0 || get_sum_units(sock, board, 1) == 0)
        return 1;
    else
        return 0;
}

int get_final_score(int sock, int board[], int side, int score) {
    int i = 0;
    for (i = 0; i < 5; i++) {
        if (side == 1)
            score += board[user_move[i]];
        else
            score += board[ai_move[i]];
    }
    return score;
}

int is_quan(int sock, int postion) {
    if (postion == 0 || postion == 1)
        return 1;
    return 0;
}

int move_iter(int sock, int board[], int step, int print) {
    // print = 1 if print board, print = 0 if not
    int direct = get_direct(sock, step);
    int postion = step > 0 ? step : -step;
    if (print) {
        asprintf(&str, "postion:%d direct:%d:\n", postion, direct);
        toClient(sock, str);
    }
    int score = 0;
    int next_postion = 0, next_next_postion = 0;
    int num_units = board[postion];
    int matluot = 0;
    board[postion] = 0;
    while (!matluot) {
        if (num_units > 0) {
            postion += direct;
            postion = (postion + 12) % 12;
            num_units--;
            board[postion] += 1;
        }
        if (num_units == 0) {
            next_postion = (12 + postion + direct) % 12;
            next_next_postion = (12 + next_postion + direct) % 12;
            if (is_quan(sock, next_postion) ||
                (board[next_postion] == 0 && board[next_next_postion] == 0)) {
                matluot = 1;
            if (print)
                asprintf(&str, "***MAT LUOT (Gap O QUAN hoac 2 O TRONG)\n");
            toClient(sock, str);
            break;
        }

        if (board[next_postion] == 0 && board[next_next_postion] > 0) {
            score += board[next_next_postion];
            if (print)
                asprintf(&str, "an %d:%d, mat luot\n", next_postion, board[next_next_postion]);
            toClient(sock, str);
            board[next_next_postion] = 0;
            matluot = 1;
            break;
        }

        if (board[next_postion] > 0) {
            num_units = board[next_postion];
            board[next_postion] = 0;
            postion = next_postion;
            if (print) {
                print_board(sock, board);
                asprintf(&str, "***BOC TIEP %d: postion=%d,direct=%d\n", num_units, postion, direct);
                toClient(sock, str);
                asprintf(&str, "-----------------------------------\n");
                toClient(sock, str);
            }
        }
    }
}
if (print) {
    print_board(sock, board);
    asprintf(&str, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    toClient(sock, str);
}
return score;
}

///////////

int get_user_step(int sock){
    int step, postion, direct;
    while(1){
        while(1){
            __fpurge(stdin);
            toClient(sock, "Nhap vao vi tri muon di chuyen(1-5):");
            postion = waitIntFromClient(sock);
            if(postion >=1 && postion <= 5)
                break;
        }
        while(1){
            __fpurge(stdin);
            toClient(sock, "Nhap vao huong muon di chuyen(-1:trai,1:phai):");
            direct = waitIntFromClient(sock);
            if(direct ==1 || direct == -1)
                break;
        }
        step = postion * direct;    
        if (check_step_true(sock, game_board, step, 1))
            break;
        else
            toClient(sock, "step khong nam trong so step thoa man\n");
    }
    return step;
}

int get_ai_random_step(int sock){
    int list_step[20];
    int len_list_step = get_list_step_true(sock, game_board, 0, list_step);
    int r = rand() % len_list_step;
    return list_step[r];
}

void stand_alone_game(int sock){
    // toClient(sock, "!-------------Start game-------------!\n");
    int user_turn = 1;
    int step, user_score = 0, ai_score=0;
    int tmp_score;
    print_board(sock, game_board);
    while(!check_board_status(sock, game_board)){
        if(user_turn > 0){
            step = get_user_step(sock);
            tmp_score = move_iter(sock, game_board, step, 1);
            user_score += tmp_score;
        }
        else {
            step = get_ai_random_step(sock);
            tmp_score = move_iter(sock, game_board, step, 1);
            ai_score += tmp_score;
        }
        user_turn *= -1;
    }
// toClient(sock, "final result: %d-%d\n", user_score, ai_score);
}

void start(int sock){
    stand_alone_game(sock);
}

// int main(int argc, char* argv[]){
//     start();
//     return 1;
// }

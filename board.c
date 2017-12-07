#include "board.h"

extern int game_board[] = {10,5,5,5,5,5,10,5,5,5,5,5};
extern char luat_choi[] = "Nguoi dung di cac o duoi,\nMay di cac o tren,\nmat luot khi an quan, gap o trong hoac gap o quan\n";
char buffer[BUFFER_LENGTH];

int get_user_step(int sock){
    int step, postion, direct;
    while(1){
        while(1){
            __fpurge(stdin);
            toClient(sock, "Nhap vao vi tri muon di chuyen(1-5):");
            // scanf("%d", &postion);
            bzero(buffer, BUFFER_LENGTH);
            strcpy(buffer, fromClient(sock));
            // postion = (int)buffer;
            printf("\n%s\n",buffer);
            if(postion >=1 && postion <= 5)
                break;
        }
        while(1){
            __fpurge(stdin);
            toClient(sock, "Nhap vao huowng muon di chuyen(-1:trai,1:phai):");
            scanf("%d", &direct);
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

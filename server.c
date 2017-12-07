#include "transfer.h"

void convertToUpperCase(char *sPtr);
int playGame(int sock);


// void print_board(int sock, int s[]);
// int get_direct(int sock, int step);
// int step_transform(int sock, int postion, int direct);
// int check_step_true(int sock, int board[], int step, int side);
// int get_list_step_true(int sock, int board[], int side, int *list_step);
// int get_sum_units(int sock, int board[], int side);
// int check_board_status(int sock, int board[]);
// int get_final_score(int sock, int board[], int side, int score);
// int is_quan(int sock, int postion);
// int move_iter(int sock, int board[], int step, int print);

// int get_user_step(int sock, void);
// int get_ai_random_step(int sock, void);
// void stand_alone_game(int sock, void);
// void start(int sock, void);


////////
int main(int argc, char const *argv[]) {

    int sockfd, newSockfd, childcount = 0;
    pid_t pid;
    socklen_t cLen;
    char buffer[BUFFER_LENGTH];
    
    struct sockaddr_in sAddr, cAddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR OPENING SOCKET");
        exit(1);
    }

    bzero((char*) &sAddr, sizeof(sAddr));

    sAddr.sin_family = AF_INET; 
    sAddr.sin_addr.s_addr = INADDR_ANY;
    sAddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *) &sAddr, sizeof(sAddr)) < 0) {
        perror("ERROR ON BINDING");
        exit(1);
    }

    if (listen(sockfd, 1000) < 0){
        perror("ERROR LISTEN PORT");
        exit(1);
    };

    printf("Linsten on port: %d\n", PORT);
    fflush(stdout);

    while(1) {
        cLen = sizeof(cAddr);
        newSockfd = accept(sockfd, (struct sockaddr *) &cAddr, &cLen);

        if (newSockfd < 0)  {
            perror("ERROR ON ACCEPT");
            exit(1);
        }

        pid = fork();

        if (pid < 0) {
            perror("ERROR ON FORK");
            exit(1);
        } else if (pid == 0) {
            // bzero(buffer, BUFFER_LENGTH);
            close(sockfd);
            
            while(1) {
                toClient(newSockfd, "!-------------Start game-------------!\n");
                if ( playGame(newSockfd) < 0) {
                    close(newSockfd);
                    exit(0);
                };
            }

            close(newSockfd);
            exit(0);
        }

        printf("\n-------PROCESS ID: %d\n", pid);
        childcount++;
        while(childcount){
            pid = waitpid( (pid_t) - 1, NULL, WNOHANG );
            if (pid < 0) perror("ERROR WAIT PROCESS");
            else if (pid == 0) break;
            else childcount--;
        }
    }
    
    close(sockfd);
    return 0;
}
/////////


void convertToUpperCase(char *sPtr) {   
    while(*sPtr != '\0')  {
        if (islower(*sPtr))
            *sPtr = toupper((unsigned char)*sPtr);
        *sPtr++;
    }
}

int playGame(int sock) {
    // toClient(sock, "!--------------------!\n");
    stand_alone_game(sock);
}

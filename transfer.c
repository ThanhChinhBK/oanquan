#include "transfer.h"

// Common
char fullBuffer[BUFFER_LENGTH];
////
// Use in Client

void fromServer(int sock)
{
    char buffer[BUFFER_LENGTH];
    bzero(buffer, BUFFER_LENGTH);
    char bufferTemp[BUFFER_LENGTH];
    bzero(bufferTemp, BUFFER_LENGTH);

    int state = recv(sock, buffer, BUFFER_LENGTH - 1, 0);

    if (state < 0)
    {
        perror("ERROR RECEIVE RESPONSE");
        exit(1);
    }

    if (buffer[0] == '(') {   // Write file log
        char logFileName[25];
        FILE *logFile;

        time_t now = time(NULL);
        strftime(logFileName, 25, "%Y-%m-%d-%H-%M-%S", localtime(&now));
        logFile = fopen(logFileName, "w+");

        fprintf(logFile, buffer);
        fclose(logFile);
        printf("Log file: %s\nEnd Game!\n", logFileName);
        close(sock);
    } else {
        printf("%s", buffer);
        if (strcmp(buffer, "Good Bye!") == 0) { // End game
            close(sock);
        }
        else { // Gaming
            toServer(sock);
        }
    }

}

void toServer(int sock)
{
    char buffer[BUFFER_LENGTH];
    bzero(buffer, BUFFER_LENGTH);

    if (fgets(buffer, BUFFER_LENGTH - 1, stdin) == NULL)
    {
        perror("ERROR CREATE TO BUFFER");
        exit(1);
    }

    if (send(sock, buffer, strlen(buffer), 0) < 0)
    {
        close(sock);
        printf("DISCONECT\n");
        perror("ERROR SEND REQUEST");
        exit(1);
    }
    fromServer(sock);
}

////
// Use in Server
void fromClient(int sock, char *str)
{
    int strLeng;
    char buffer[BUFFER_LENGTH];
    bzero(buffer, BUFFER_LENGTH);

    strLeng = read(sock, (char *)&buffer, BUFFER_LENGTH - 1);

    if (strLeng < 0)
    {
        perror("ERROR READING FROM SOCKET");
        exit(1);
    }

    buffer[strLeng - 1] = '\0';

    if (strcmp(buffer, "END") == 0)
    {
        printf("\n\tFrom client: END\n");
        printf("\tTo client:   DISCONECT\n");
        strLeng = write(sock, "DISCONECT", strlen("DISCONECT"));

        if (strLeng < 0)
        {
            perror("ERROR WRITING TO SOCKET");
            exit(1);
        }
        close(sock);
        return;
    }
    else
    {
        printf("\n\tFr client: %s\n", buffer);
        strcpy(str, buffer);
        return;
    }
}

void toClient(int sock, char *buffer, char* sending)
{
    int state;
    char sendText[BUFFER_LENGTH];
    bzero(sendText, BUFFER_LENGTH);

    strcat(fullBuffer, buffer);

    if (strcmp(sending, "endgame") == 0) {
        printf("\tTo client: End Game!\n");
        state = write(sock, fullBuffer, strlen(fullBuffer));
        bzero(fullBuffer, BUFFER_LENGTH);
        close(sock);
        if (state < 0)
        {
            perror("ERROR WRITING TO SOCKET");
            exit(1);
        }
    } else if (strcmp(sending, "end") == 0) {
        printf("\tTo client: Gaming...%s\n", buffer);
        state = write(sock, fullBuffer, strlen(fullBuffer));
        bzero(fullBuffer, BUFFER_LENGTH);
        if (state < 0)
        {
            perror("ERROR WRITING TO SOCKET");
            exit(1);
        }
    }
    return;
}

int waitIntFromClient(int sock)
{
    char buffer[BUFFER_LENGTH];
    bzero(buffer, BUFFER_LENGTH);
    fromClient(sock, buffer);
    return atoi(buffer);
}

void waitEndFromClient(int sock, char * log_string) {
    // send file and close socket
    char buffer[BUFFER_LENGTH];
    bzero(buffer, BUFFER_LENGTH);
    fromClient(sock, buffer);
    if (strcmp(buffer, "yes") == 0)
    {
        toClient(sock, log_string, "endgame");
    } else {
        toClient(sock, "Good Bye!", "endgame");
    }
}
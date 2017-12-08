#include "transfer.h"

// Common
char ahihi[BUFFER_LENGTH];
////
// Use in Client

void fromServer(int sock)
{
    char buffer[BUFFER_LENGTH];
    bzero(buffer, BUFFER_LENGTH);
    char bufferTemp[BUFFER_LENGTH];
    bzero(bufferTemp, BUFFER_LENGTH);
    char sending[11];

    memset(sending, '\0', sizeof(sending));

    int state = recv(sock, buffer, BUFFER_LENGTH - 1, 0);

    if (state < 0)
    {
        perror("ERROR RECEIVE RESPONSE");
        exit(1);
    }

    printf("%s", buffer);

    toServer(sock);
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

    strcat(ahihi, buffer);

    if (strcmp(sending, "end") == 0) {
        printf("\tTo client: Gaming...\n");
        state = write(sock, ahihi, strlen(ahihi));
        bzero(ahihi, BUFFER_LENGTH);
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

void waitEndFromClient(int sock) {
    // send file and close socket
}
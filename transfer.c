#include "transfer.h"

// Common

////
// Use in Client

void fromServer(int sock)
{
    char buffer[BUFFER_LENGTH];
    bzero(buffer, BUFFER_LENGTH);

    int state = recv(sock, buffer, BUFFER_LENGTH - 1, 0);

    if (state < 0)
    {
        perror("ERROR RECEIVE RESPONSE");
        exit(1);
    }
    // do {
        printf("%s", buffer);
        
    // }while(recv(sock, buffer, BUFFER_LENGTH - 1, 0) > 0) ;
    // }

    toServer(sock);
}

void toServer(int sock)
{
    char buffer[BUFFER_LENGTH];
    bzero(buffer, BUFFER_LENGTH);
    // printf("toServer: ");
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
        // printf("\n%s\n", str);
        return;
    }
}

void toClient(int sock, char *buffer)
{
    int state;

    printf("\tTo client: %s\n", buffer);

    state = write(sock, buffer, strlen(buffer));

    if (state < 0)
    {
        perror("ERROR WRITING TO SOCKET");
        exit(1);
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

////
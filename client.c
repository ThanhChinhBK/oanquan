#include "transfer.h"


int socketConnected = 0;

void sigpipe_handler();

int main(int argc, char *argv[])
{

    int sockfd, portno, n;
    struct sockaddr_in sAddr;
    struct hostent *server;

    char buffer[BUFFER_LENGTH];

    if (argc < 3)
    {
        fprintf(stderr, "usage: %s HOSTNAME PORT\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("ERROR OPENING SOCKET");
        exit(1);
    }

    server = gethostbyname(argv[1]);

    if (server == NULL)
    {
        fprintf(stderr, "ERROR, NO SUCH HOST: %s\n", argv[0]);
        exit(0);
    }

    bzero((char *)&sAddr, sizeof(sAddr));

    sAddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&sAddr.sin_addr.s_addr, server->h_length);
    sAddr.sin_port = htons(portno);

    signal(SIGPIPE, sigpipe_handler);

    if (connect(sockfd, (struct sockaddr *)&sAddr, sizeof(sAddr)) < 0)
    {
        perror("ERROR CONNECTING");
        exit(1);
    }

    socketConnected = 1;

    while (1)
    {
        if (!socketConnected)
            break;
        // Play game!
        fromServer(sockfd);
    }

    return 0;
}

void sigpipe_handler()
{
    printf("SIGPIPE caught\n");
    socketConnected = 0;
}


#include <sys/socket.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>

#define PORT 8888
#define BUFFER_LENGTH 10001

// Common


// Use in Client
void fromServer(int sock);
void toServer(int sock);

// Use in Server
void fromClient(int sock, char *str);
void toClient(int sock, char* buffer, char* sending);
int waitIntFromClient(int sock);
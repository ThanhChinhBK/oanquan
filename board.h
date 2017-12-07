#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int get_user_step(int sock);
int get_ai_random_step(int sock);
void stand_alone_game(int sock);
void start(int sock);

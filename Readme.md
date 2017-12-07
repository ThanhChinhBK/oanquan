Use in Folder: intro/[oanquan_online]

TERMINAL 1
```
gcc server.c transfer.c transfer.h game.c  game.h -o server
./server


TERMINAL 2
```
gcc client.c transfer.h transfer.c -o  client
./client 127.1.1.1 8888

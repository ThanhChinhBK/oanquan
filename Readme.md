Use in Folder: intro/[oanquan_online]

TERMINAL 1
```
gcc server.c transfer.c game.c -o server
./server
```

TERMINAL 2
```
gcc client.c transfer.c -o  client
./client 127.1.1.1 8888
```
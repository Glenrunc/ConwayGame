# Conway's Game

You will find an implementation of the Conway's Game in C.
## Raylib

To be able to compile and run the game you have to download **[Raylib](https://www.raylib.com/)**. Once you have dowload just follow instruction on **[The Official github repo](https://github.com/raysan5/raylib)**.

## Compile time
```shell
gcc -L/user/local/lib -o main main.c conway.c -lraylib
```
<font color="red">*Warning: Don't forget to put raylib.so in /user/local/lib directory*</font>

## Main idea for the algorithm

```mermaid
    A-->Null;
    A-->B;
    B-->A;
    B-->C;
    C-->B;
    C-->Null;
```
#ifndef TETRIS_H
#define TETRIS_H

extern const char L[5][5]; 
extern const char rL[5][5];
extern const char T[5][5];
extern const char O[4][4];
extern const char S[5][5];
extern const char rS[5][5];
extern const char I[4][4];
extern int falling_block_5;
extern char falling_block[5][5];
extern int *ptr;
extern char *ptr2;

void Draw(char board[20][10]);

/// @brief Fuction that Spawns a block in the board
/// @param board The board array (used to place the block there)
/// @param cords The cordinate array (used to fill it with the block cordinates and size)
/// @param fb The falling block array (the actuall falling block thats get copied to the board array)
/// @param x The x spawn cordinate in board cordinates
/// @param y The y spawn cordinate in board cordinates
/// @param block The block templete (the shape of the block)
void Spawn(char board[20][10],int cords[3], char fb[cords[2]][cords[2]], int x, int y, int block);
void Rotate(int cords[3], char fb[cords[2]][cords[2]], char board[20][10]);
void Move(char board[20][10], int cords[3], char mask[cords[2]][cords[2]], char direction);
int Check(int cords[3], char fb[cords[2]][cords[2]],char board[20][10], char dir);
void CheckFullRows(char board[20][10], int full_lines[20]);
void ClearRows(char board[20][10]);
#endif
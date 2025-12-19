#ifndef NIG_H
#define NIG_H

void copyArray(char array1[], char array2[], int size);
void copy2DArray(int size, char array1[size][size], char array2[size][size]);
void copy2DArrayConst(int size, const char array1[size][size], char array2[size][size]);
void rotateArray(int size, char array[size][size]);
void placeArray(int size, char array[size][size], char board[20][10], int x, int y, int ovr);
void replaceArray(char a,char b,int size, char array[size][size]);
void shiftArrayDown(char board[20][10], int shift_by, int start_y);
void init2DArray(int size_x, int size_y, char array[size_y][size_x]);
void initArray(int size, char array[size]);
int checkOverlap(int size, char tmp[size][size], int ox, int oy, int board_w, int board_h, char board[20][10]);
#endif
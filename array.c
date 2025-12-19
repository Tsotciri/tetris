#include "arrays.h"
#include <stdio.h>

void copy2DArrayConst(int size, const char array1[size][size], char array2[size][size]) {
    for (int y = 0; y < size; y++) {    
        for (int x = 0; x < size; x++) {
            array2[y][x] = array1[y][x];
        }
    }
}

void copy2DArray(int size, char array1[size][size], char array2[size][size]) {
    for (int y = 0; y < size; y++) {    
        for (int x = 0; x < size; x++) {
            array2[y][x] = array1[y][x];
        }
    }
}

void rotateArray(int size, char array[size][size]) {

    // Transpose
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            char t = array[i][j];
            array[i][j] = array[j][i];
            array[j][i] = t;
        }
    }
    // Reverse rows
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size / 2; j++) {
            char t = array[i][j];
            array[i][j] = array[i][size - 1 - j];
            array[i][size - 1 - j] = t;
        }
    }
}

void placeArray(int size, char array[size][size], char board[20][10], int x, int y, int ovr) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (ovr == 0) {
                if (board[i+y][j+x] == ' ') {
                    board[i+y][j+x] = array[i][j];
                } else {
                    continue;
                }
            } else {
                board[i+y][j+x] = array[i][j];
            }
        }
    }
}

void replaceArray(char a, char b, int size, char array[size][size]) {
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (array[y][x] == a)
                array[y][x] = b;
        }
    }
}

void init2DArray(int size_x, int size_y, char array[size_y][size_x]) {
    for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
            array[y][x] = ' ';
        }
    }
}

void copyArray(char array1[], char array2[], int size) {
    for (int i = 0; i < size; i++) {
        array2[i] = array1[i];
    }
}

void initArray(int size, char array[size]) {
    for (int i = 0; i < size; i++) {
        array[i] = ' ';
    }
}

int checkOverlap(int size, char tmp[size][size], int ox, int oy, int board_w, int board_h, char board[20][10]) {

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {

            if (tmp[y][x] == ' ') continue;  // skip empty tiles

            int bx = ox + x;
            int by = oy + y;

            // Check out of bounds
            if (bx < 0 || bx >= board_w || by < 0 || by >= board_h) {
                return 1; // blocked
            }

            // Check out of bounds
            if (board[by][bx] != ' ') {
                return 1;
            }
        }
    }
    return 0; // free to rotate or move
}

void shiftArrayDown(char board[20][10], int shift_by, int start_y) {

        // Repeating however many times to shift down by
        for (int i = 0; i < shift_by; i++) {

            // Itirating over the board starting from bottom rigt copying to top line to the bottom one starting from the given y
            for (int y = start_y; y >= 0; y--) {
                for (int x = 9; x >= 0; x--) {
                    board[y][x] = board[y-1][x];
                }
            }
            
            // Clearing the top line
            for (int x = 0; x < 10; x++)
            {
                board[0][x] = ' ';
            }
            
        }
}
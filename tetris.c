#include <stdio.h>
#include "tetris.h"
#include "arrays.h"
#include <stdlib.h>
#include <windows.h>

#define SYMBOL 219
#define SIZE_X 10
#define SIZE_Y 20

// Bebug stuff, i think
int cx;
char sussy;
int* ptr = &cx;
char* ptr2 = &sussy; 

void debug_print(char board[20][10], char fb[5][5], int cords[3], int check_y, int check_x, int x, int y);

// Block templates
const char L[5][5] = {
    {' ',' ',' ',' ',' '},
    {' ',' ','x',' ',' '},
    {' ',' ','x',' ',' '},
    {' ',' ','x','x',' '},
    {' ',' ',' ',' ',' '} 
};

const char rL[5][5] = {
    {' ',' ',' ',' ',' '},
    {' ',' ','x',' ',' '},
    {' ',' ','x',' ',' '},
    {' ','x','x',' ',' '},
    {' ',' ',' ',' ',' '}
};

const char T[5][5] = {
    {' ',' ',' ',' ',' '},
    {' ',' ','x',' ',' '},
    {' ','x','x','x',' '},
    {' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' '}
};

const char O[4][4] = {
    {' ',' ',' ',' '},
    {' ','x','x',' '},
    {' ','x','x',' '},
    {' ',' ',' ',' '}
};

const char S[5][5] = {
    {' ',' ',' ',' ',' '},
    {' ','x','x',' ',' '},
    {' ',' ','x','x',' '},
    {' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' '}
};

const char rS[5][5] = {
    {' ',' ',' ',' ',' '},
    {' ',' ','x','x',' '},
    {' ','x','x',' ',' '},
    {' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' '}
};

const char I[4][4] = {
    {' ',' ','x',' '},
    {' ',' ','x',' '},
    {' ',' ','x',' '},
    {' ',' ','x',' '}
};

void Spawn(char board[20][10], int cords[3], char fb[cords[2]][cords[2]], int x, int y, int block) {

    int rng_color = rand() % 7;
    int rng_block;

    if (block == 0) {
        rng_block = rand() % 7;

    } else {
        rng_block = block;
    }

    char color_l;
    int ar_size = 5;

    // Copying a template block from the template arrays into the falling_block array based on the random number 
    switch (rng_block)
    {
    case 0:
        copy2DArrayConst(5, L, fb);
        color_l = 'o';
        break;
    case 1:
        copy2DArrayConst(5, rL, fb);
        color_l = 'b';
        break;
    case 2:
        copy2DArrayConst(5, T, fb);
        color_l = 'p';
        break;
    case 3:
        copy2DArrayConst(4, O, fb);
        color_l = 'y';
        ar_size = 4;
        break;
    case 4:
        copy2DArrayConst(5, S, fb);
        color_l = 'g';

        break;
    case 5:
        copy2DArrayConst(5, rS, fb);
        color_l = 'r';
        break;
    case 6:
        copy2DArrayConst(4, I, fb);
        color_l = 'c';
        ar_size = 4;
        break;
    default:
        copy2DArrayConst(5, L, fb);
        color_l = 'o';
        break;
    }
    
    // Replacing x's from template to the randomly chosen color
    replaceArray('x', color_l, ar_size, fb);
    
    // Setting spawn cords and array size
    cords[0] = x;
    cords[1] = y;
    cords[2] = ar_size;


    // Placing the new falling block in the board
    placeArray(ar_size, fb, board, x, y, 0);
}

void Rotate(int cords[3], char fb[cords[2]][cords[2]], char board[20][10]) {

    // 1. Create rotated version
    char tmp[cords[2]][cords[2]];
    copy2DArray(cords[2], fb, tmp);
    rotateArray(cords[2], tmp);

    // 2. Remove old block
    for (int y = 0; y < cords[2]; y++) 
        for (int x = 0; x < cords[2]; x++)
            if (fb[y][x] != ' ')
                board[cords[1]+y][cords[0]+x] = ' ';

    // 3. Check if new rotation fits
    if (checkOverlap(cords[2], tmp, cords[0], cords[1], 10, 20, board) == 0) {

        // 4. Copy rotated back into fb
        copy2DArray(cords[2], tmp, fb);
    }

    // 5. Place rotated block
    placeArray(cords[2], fb, board, cords[0], cords[1], 0);
}

void Draw(char board[20][10]) {  

    // Move pointer back and clear (Not clearing because then it flickers (\033[J))  
    printf("\033[H");

    printf("\n");

    // Printing top design
    printf(" +");
    for (int x = 0; x <= 2*SIZE_X-1; x++) {
            printf("-", x);
    }
    printf("+\n");
    
    for (int y = 0; y < SIZE_Y; y++ ) {

        // Printing left wall
        printf(" |");

        // Printing the board characters based on the board array, SYMBOL is the ascii characters blocks are going to be printed with
        for (int x = 0; x < SIZE_X; x++) {

            switch (board[y][x])
            {
            case 'p':
                /* purple */
                printf("\033[35m%c", SYMBOL);
                printf("%c\033[0m",SYMBOL);
                break;
            case 'b':
                /* blue */
                printf("\033[34m%c", SYMBOL);
                printf("%c\033[0m",SYMBOL);
                break;
            case 'r':
                /* red */
                printf("\033[31m%c", SYMBOL);
                printf("%c\033[0m",SYMBOL);
                break;
            case 'y':
                /* yelllow */
                printf("\033[38;5;226m%c", SYMBOL);
                printf("%c\033[0m",SYMBOL);
                break;
            case 'g':
                /* green */
                printf("\033[32m%c", SYMBOL);
                printf("%c\033[0m",SYMBOL);
                break;
            case 'o':
                /* orange */
                printf("\033[38:5:202m%c", SYMBOL);
                printf("%c\033[0m",SYMBOL);
                break;
            case 'c':
                /* cyan */
                printf("\033[38:5:51m%c", SYMBOL);
                printf("%c\033[0m",SYMBOL);
                break;
            case 'x':
                /* x */
                printf("%d");
                break;
            case ' ':
                printf("  ");
                break;
            default:
                printf("x");
                break;
            }

        }

        // Printing right wall
        printf("|\n");
    }

    // Printing bottom design
    printf(" +");
    for (int x = 0; x <= 2*SIZE_X-1; x++) {
            printf("-");
    }
    printf("+\n");

}

void Move(char board[20][10], int cords[3], char mask[cords[2]][cords[2]], char direction) {

    // Itirating over the board array only where the falling block is to see what blocks are part of it and deleting them
        for (int y = cords[2] - 1 + cords[1]; y >= cords[1]; y--) {
            for (int x = cords[2] - 1 + cords[0]; x >= cords[0]; x--) {

                // Checking if a character is part of the block
                if ((board[y][x] != ' ') && (board[y][x] == mask[y-cords[1]][x-cords[0]])) {

                    // Deleting the character
                    board[y][x] = ' '; 

                } else if (board[y][x] == ' ') {
                    continue;
                }
            }
        }
        
    // Chosing direction to place new block
    int x;
    int y;
    switch (direction)
    {
    case 'r':
        x = cords[0] + 1;
        y = cords[1];
        break;
    case 'l':
        x = cords[0] - 1;
        y = cords[1];
        break;
    
    case 'u':
        x = cords[0];
        y = cords[1] - 1;
        break;
    default:
        x = cords[0];
        y = cords[1] + 1;
        break;
    }

    // Saving new cordinates
    cords[0] = x;
    cords[1] = y;

    // Placing falling block to the new modified cordinates
    placeArray(cords[2], mask, board, x,y, 0);
}

int Check(int cords[3], char fb[cords[2]][cords[2]], char board[20][10], char dir) {

    int dir_x;
    int dir_y;
    int fb_x = cords[0];
    int fb_y = cords[1];

    // Chosing direction to check
    switch (dir) {
    case 'r':
        dir_x = +1;
        dir_y = 0;
        break;
    case 'l':
        dir_x = -1;
        dir_y = 0;
        break;
    
    case 'u':
        dir_x = 0;
        dir_y = -1;
        break;
    case 'd':
        dir_x = 0;
        dir_y = 1;
        break;
    default:
        printf("Nigglet");
        break;
    }

    // Initializing the direction wwe gonna check for x and y and bx, by
    int check_y;
    int check_x;

    /* 
    bx stands for board x (and board y) because in the for loops below the x and y represent the coordinates
    in the small 5x5 or 4x4 falling block array, so the bx (and by) are the coordinates in the board where the
    falling block is located
    */ 
    int bx = 0;
    int by = 0;

    // Itirating over the board array only where the falling block is to see what blocks are part of it and if it can be moved
    for (int y = 0; y < cords[2]; y++) {
        
        by = y + cords[1];
        
        for (int x = 0; x < cords[2]; x++) {
            bx = x + cords[0];

            // Checking if a character is part of the block
            if ((board[by][bx] != ' ') && (board[by][bx] == fb[y][x])) {
                
                check_y = by + dir_y;
                check_x = bx + dir_x;

                //Check out of bounds
                if (!(0 <= check_x && check_x <= 9 ) || check_y > 19) {
                    //printf("Bingo (%d, %d)", x, y);  
                    return 1;
                }
               
                // Check if in the chosen direction its empty space, if its not AND its not part of the mask, then we've hit diffrent block, end the fucntion and return 1
                if (board[check_y][check_x] != fb[y+dir_y][x+dir_x]) {
                    return 1;
                } else {    
                    continue;
                } 

            } else {
                continue;
            }
        }
    }
    return 0;
}

void CheckFullRows(char board[20][10], int full_rows[20]) {
    
    // Initializing full_rows array as 1, assuming all rows are filled
    for (int i = 0; i < 20; i++) {
        full_rows[i] = 1;
    }

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            if (board[y][x] != ' ') {
                continue;
            
            // If a row isnt full, make full_rows for this row into 0 to signify that that row isnt filled
            } else if (board[y][x] == ' ') {
                full_rows[y] = 0;
                break;
                
            }
        }
    }    
}

void ClearRows(char board[20][10]) {

    // Getting filled rows
    int full_rows[20];
    CheckFullRows(board, full_rows);

    // Clearing filled rows
    for (int i = 0; i < 20; i++) 
    {
        if (full_rows[i] == 1) {
            for (int x = 0; x < 10; x++) {
                board[i][x] = ' ';
            }
            
        }
    }

    //Shifting down the board array, from top to bottom
    for (int index = 0; index < 20; index++) 
    {
        if (full_rows[index] == 1) {
            // Index represent the y coordinate of the board in this case and if its 1 or 0 represent if its full or not
            shiftArrayDown(board, 1, index);
        }
    }

}

// A function that used for debuging
void debug_print(char board[20][10], char fb[5][5], int cords[3], int check_y, int check_x, int x, int y) {
    printf("[Check] Local space check cords: %d, %d\n", x-1, y);
    printf("[Check] Board space check cords: %d, %d\n", check_x, check_y);
    printf("[Check] Spawn Cords (BS) (x,y): (%d, %d)\n", cords[0], cords[1]);
    printf("[Check] Current detected block cords (x,y): (%d, %d)\n",x, y);
    printf("y-x>%c<\n", fb[y-1][x]);
    printf("1-1>%c<\n", fb[y][x]);
    printf("0-2>%c<\n", fb[y][x+1]);
    printf("--------\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (fb[i][j] != ' ') {printf("%c ", fb[i][j]);} else {printf(". ");}
        }
        printf("\n");
    }
    
    char condA = fb[y][x-1];
    char condB = board[check_y][check_x];
    printf("[Check] condA, condB: %c %c\n", condA, condB);
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "tetris.h"
#include "arrays.h"

void hidecursor();

int main() {

    // Initializing rng
    srand(time(NULL));
    
    // Initalizing board
    char b[20][10];
    init2DArray(10,20,b);
    
    // Hide cursor (windows only)
    hidecursor();

    // Initialazing falling block
    char falling_block[5][5];
    int falling_block_cords[3];
    init2DArray(5,5, falling_block);

    // Spawn falling block 1 at cords (1,1)
    Spawn(b, falling_block_cords, falling_block, 4, 0, 0);

    // Clear terminal
    printf("\033[H\033[J");

    // Temporary for debug
    
    /** 
    for (int x = 0; x < 10; x++) {
            b[19][x] = 'r';
    }

    b[18][2] = 'g';
    
    for (int y = 0; y < 20; y++) {
            b[y][9] = 'r';
    } 
    for (int x = 0; x < 10; x++) {
            b[19][x] = 'c';
    }  
    */

    // Inialazing the variables
    char ch;
    int key = 0;
    int cond = 1;
    
    // Counter is a variable that practicly allows thew game to listen to keypressed in between of waiting for blocs to falls
    // It also directly defies how fast blocks fall
    int counter = 0;

    Draw(b);

    while (cond) {
        key = 0;
        
        // Reading whether there is a keypress waiting in the buffer
        key = _kbhit();

        if (key != 0) {
            
            // Getting the pressed key from the buffer and clearing it
            ch = _getch();

            // Reading keypress
            switch (ch) {
            case 'd':
                if (!Check(falling_block_cords, falling_block, b, 'r')) {
                    Move(b, falling_block_cords, falling_block, 'r');
                }
                break;
            case 'a':
                if (!Check(falling_block_cords, falling_block, b, 'l')) {
                    Move(b, falling_block_cords, falling_block, 'l');
                }
                break;
            case 's':
                if (!Check(falling_block_cords, falling_block, b, 'd')) {
                    Move(b, falling_block_cords, falling_block, 'd');
                }
                    break;
            case 'w':
                Rotate(falling_block_cords, falling_block, b);
                break;
            case 'p':
                printf("\033[H\033[J");
                printf("Game paused");
                getchar();
                printf("\033[H\033[J");
                break;
            default:
                break;
            }
        }


        // Checking falling block can be moved down
        if (!Check(falling_block_cords, falling_block, b, 'd') && counter == 6) {
            counter = 0;
            
            Move(b, falling_block_cords, falling_block, 'd');
        
        // If you cant move block down, block has hit something
        } else if (Check(falling_block_cords, falling_block, b, 'd') && counter == 6) {
            counter = 0;
            
            // Cleaing filled rows
            ClearRows(b);
            
            // Checking if you can spawn other block
            falling_block_cords[0] = 3;
            falling_block_cords[1] = 0;
            if (checkOverlap(falling_block_cords[2], falling_block, falling_block_cords[0], falling_block_cords[1], 10, 20, b)) {
                // If not, end the game
                cond = 0;
                break;
            }

            // Else spawn new block
            Spawn(b, falling_block_cords, falling_block, 3, 0, 0);
            
        }
        
        // Draw the board after all the other stuff has been completed
        Draw(b);
        counter += 1;
        Sleep(10);

    }

    printf("\nYou lost :(\n");
    return 0;
}

// A funtion to hide the sensor on windows
void hidecursor() {
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
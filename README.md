#MARGARITA MALIGAYA
#Summary of Game of Life program
#CS300 BART MASSEY
#OCT-NOV 2020

The goal of this program is to recreate Conway's Game of Life. This game consists of rules that determine whether a cell lives or dies. The program is to utilize ncurses. The program (in C++) is to allow the user to enter X's where they please by using the arrows on their keypad and pressing X. If the cell already has an "X" (which means the cell is alive) and the user presses X again, the cell will revert back to dead, shown as whitespace. The user can create any pattern within the terminal. If the user presses "n," the screen should move forward in time by one step or on generation. If the user presses "p," the program will take the pattern and continuously move in time, updating the cells and displaying a new generation every 0.5 seconds. At any time, whether creating a pattern or in play mode, the user can cleanly exit the game by pressing "q." 

To help make the code clean and efficient, I created functions that will get called multiple times throughout the program. In order to move a step forward or play the entire patterns through, I had to create a function that iterates through the current 2d array, checks each cells 8 neighbors, and updates the cell depending on the amount of neighbors (according to Conway's GoL). I was able to achieve this by creating a temporary 2d array, filling in the values for the corresponding indices, and copying the temporary array to the original grid. This was then used within an if statement for "n" and for "p." One note is that I was not able to deallocate the temporary array properly without compromising the program. I inserted a delete[] within the function, but I am not certain this prevents memory from leaking. Deallocating a temporary array allocated within a function getting called several times in a while loop directly affects the program and its outputs. Hopefully, I will be able to find the right method to deallocate this temporary array to avoid memory leaks if the current method is not sufficient.

The program was required to play through each generation every 0.5 seconds in play mode, and this was achieved by using usleep(), a function provided by unistd.h. This function takes in microseconds and will pause execution for the time given. Another requirement was to not allow any input during play mode unless it is q (to quit). Ncurses provides a function called timeout() which blocks getch() when set to 0 and waits for input when set to -1. This was used primarily when switching back and forth from play and pause mode. 

The following links are resources used to help create this program:
Game of life description: https://en.wikipedia.org/wiki/Conway's_Game_of_Life;
Usleep() function: https://www.softwaretestinghelp.com/cpp-sleep/;
Keyboard interface: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/keys.html;
Attributes (highlighting X): https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/attrib.html;
Output in ncurses: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/printw.html;
Timeout() function: https://docs.oracle.com/cd/E36784_01/html/E36880/timeout-3curses.html;


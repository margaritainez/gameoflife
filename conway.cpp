// SOURCE CODE FOR GAME OF LIFE PROGRAM
// MARGARITA MALIGAYA

#include <ncurses.h>
#include <unistd.h> // usleep() function
#include <iostream>
#include <cstring>
using namespace std;

void set_grid(char **grid, int ysize, int xsize);
void process(char **grid, int ysize, int xsize);
void draw_grid(char **grid, int ysize, int xsize);

int main(int argc, char ** argv)
{
	int key, play, p_toggle;
	int start_y, start_x;
	int term_lines, term_cols;

	initscr();
	cbreak();
	nodelay(stdscr, true);
	keypad(stdscr, true);
	noecho();

	start_y = (LINES-1) / 2;
	start_x = (COLS-1) / 2;	
	getmaxyx(stdscr, term_lines, term_cols);

	refresh();
	move(start_y, start_x);

	char ** grid = new char*[term_lines];
	for(int i = 0; i < term_lines; i++)
		grid[i] = new char[term_cols];
	set_grid(grid, term_lines, term_cols);

	bool p_flag = false; // false flag means game is paused
	while ((key = getch()) != 'q')
	{
		switch(key)
		{
			case KEY_UP:
				start_y--;
				break;
			case KEY_DOWN:
				start_y++;
				break;
			case KEY_LEFT:
				start_x--;
				break;
			case KEY_RIGHT:
				start_x++;
				break;
		}

		if (key == 'x' || key == 'X')
		{
			getyx(stdscr, start_y, start_x);
			if (grid[start_y][start_x] == 'X') {
				grid[start_y][start_x] = ' ';
				addch(' ');
				refresh();}
			else {
				grid[start_y][start_x] = 'X';
				addch('X' | A_STANDOUT);
				refresh();}
		}
		move(start_y, start_x);

		if (key == 'n') // one step in time
		{
			process(grid, term_lines, term_cols);
			draw_grid(grid, term_lines, term_cols);
		}
		
		if (key == 'p' && p_flag == false) // if in pause mode and press p, play forward
		{		
			play = 1;
			timeout(0); // ncurses nonblocking getch
			while (play == 1)
			{
				p_flag = true;
				process(grid, term_lines, term_cols);
				refresh();
				draw_grid(grid, term_lines, term_cols);
				usleep(500000); // 0.5 second intervals

				switch(p_toggle = getch()) {
					case 'p':
						play = 0;
						p_flag = false;
						break;
					case 'q':
						play = 0;
						endwin();
						return 0;
						break;
				}
			}
			timeout(-1); // wait for input
		}
	}

	if (key == 'q') {
	refresh();
	endwin();
	}
	
	for(int i = 0; i < term_lines; i++) // deallocate grid
		delete [] grid[i];
	delete [] grid;
	
	return 0;
}

void set_grid(char **grid, int ysize, int xsize) // create a grid, set to whitespace
{
	for(int y = 0; y < ysize; y++) {
		for(int x = 0; x < xsize; x++) {
			grid[y][x] = ' ';
		}
	}
}

void draw_grid(char **grid, int ysize, int xsize) // redraw the updated grid
{
	for (int y = 0; y < ysize-1; y++) {
		for (int x = 0; x < xsize-1; x++) {
			if (grid[y][x] == 'X') 
				mvaddch(y, x, 'X' | A_STANDOUT);
			if (grid[y][x] == ' ') 
				mvaddch(y, x, ' ');
	}
}
}

void process(char **grid, int ysize, int xsize) // check all 8 neighbors for every cell and update accordingly
{
	char **temp = new char*[ysize];
	for (int i = 0; i < ysize; temp[i] = new char [xsize], i++);
	int n,nw,ne,s,sw,se,w,e, neighbors;
	for(int y = 0; y < ysize-1; y++){
		for(int x = 0; x < xsize-1; x++) {
				if (grid[(y+ysize-1)%ysize][(x+xsize-1)%xsize] == 'X')
					nw = 1;
				else
					nw = 0;
				if (grid[y][(x+xsize-1)%xsize] == 'X')
					w = 1;
				else
					w = 0;
				if (grid[(y+1)%ysize][(x+xsize-1)%xsize] == 'X')
					sw = 1;
				else
					sw = 0;
				if (grid[(y+ysize-1)%ysize][x] == 'X')
					n = 1;
				else
					n = 0;
				if (grid[(y+1)%ysize][x] == 'X')
					s = 1;
				else
					s = 0;
				if (grid[(y+ysize-1)%ysize][x+1] == 'X')
					ne = 1;
				else
					ne = 0;
				if (grid[(y+1)%ysize][(x+1)%xsize] == 'X')
					se = 1;
				else
					se = 0;
				if (grid[y][(x+1)%xsize] == 'X')
					e = 1;
				else
					e = 0;

				neighbors = n + nw + ne + s + sw + se + e + w;
				
				if (neighbors < 2 && grid[y][x] == 'X')
					temp[y][x] = ' ';
				else if (neighbors > 3 && grid[y][x] == 'X')
					temp[y][x] = ' ';
				else if (neighbors == 3 && grid[y][x] == ' ')
					temp[y][x] = 'X';
				else if ((neighbors == 2 || neighbors == 3) && grid[y][x] == 'X')
					temp[y][x] = 'X';
				else temp[y][x] = grid[y][x];
		}
	}
	memcpy(grid, temp, ysize*sizeof(char*));

	/*for(int i = 0; i < ysize; i++) {
                delete [] temp[i];
		temp[i]= grid[i]; }
        delete [] temp;
	temp = grid;*/ 
}



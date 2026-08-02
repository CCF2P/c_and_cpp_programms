#ifdef _WIN32
#include <windows.h>
static void init_terminal(void)
{
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD dwMode = 0;
  GetConsoleMode(hOut, &dwMode);
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hOut, dwMode);
  system("chcp 65001 >nul");
}
#else
static void init_terminal(void) {}
#endif


#include "stdio.h"
#include "stdlib.h"
#include "escape_commands.h"
#include "terminal_graphics.h"

struct Cursor
{
  unsigned x;
  unsigned y;
};

struct Board
{
  int size;
  char *board; // 1D array
};

void draw_horizontal_lines_top(int start_x, int start_y);
void draw_horizontal_lines_middle(int start_x, int start_y);
void draw_horizontal_middle_board(int start_x, int start_y, int row);
void draw_horizontal_lines_bottom(int start_x, int start_y);

void draw_board();
void redraw_board();

void init_board(int size);
void move_cursor(unsigned x, unsigned y);

short is_valid_pos(unsigned x, unsigned y);
short is_win(short flag);
void game(int size);
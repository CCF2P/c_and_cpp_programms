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

// Board box
#define l_horizontal           "\u2500"
#define l_vertical             "\u2502"
#define l_down_right           "\u250C"
#define l_down_left            "\u2510"
#define l_up_right             "\u2514"
#define l_up_left              "\u2518"
#define l_vertical_right       "\u251C"
#define l_vertical_left        "\u2524"
#define l_horizontal_down      "\u252C"
#define l_horizontal_up        "\u2534"
#define l_verctical_horizontal "\u253C"

// ESC commands
#define home                     printf("\033[H")
#define cls                      printf("\033[2J")
#define move_cursor_(x,y)        printf("\033[%d;%dH", y, x)
#define hide_cursor              printf("\033[?251l")
#define show_cursor              printf("\033[?251h")
#define resetcolor               printf("\033[0m")
#define set_display_atrib(color) printf("\033[%dm", color)

// Background Colours
#define B_BLACK   40
#define B_RED     41
#define B_GREEN   42
#define B_YELLOW  43
#define B_BLUE    44
#define B_MAGENTA 45
#define B_CYAN    46
#define B_WHITE   47

// Text colors
#define F_RED    31
#define F_GREEN  32
#define F_YELLOW 33
#define F_BLUE   34
#define F_CYAN   36
#define F_WHITE  37


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
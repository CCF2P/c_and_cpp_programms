#include "chess.h"

struct Cursor CURSOR = {1, 1};
struct Board BOARD;

/*
Board's cells coordinates:
(1, 1) ... (1, n)
  ...  ...  ...
(n, 1) ... (n, n)
*/
void game(int size)
{
  init_terminal();
  init_board(size);

  free(BOARD.board);
}

void init_board(int size)
{
  BOARD.size = size;
  BOARD.board = (char*)malloc(sizeof(char) * (size * size));
  for (int i = 0; i < size * size; ++i) {
    BOARD.board[i] = ' ';
  }
}

void move_cursor(unsigned x, unsigned y)
{
  CURSOR.x = x;
  CURSOR.y = y;
  move_cursor_(x, y);
}

void draw_horizontal_lines_top(int start_x, int start_y)
{
  move_cursor(start_x, start_y);
  printf(l_down_right);
  CURSOR.x += 1;
  for (int i = 0; i < BOARD.size; ++i) {
    printf(l_horizontal);
    printf(l_horizontal_down);
    CURSOR.x += 2;
  }
  move_cursor(CURSOR.x - 1, CURSOR.y);
  printf(l_down_left);
  CURSOR.x += 1;
}

void draw_horizontal_lines_middle(int start_x, int start_y)
{
  move_cursor(start_x, start_y);
  printf(l_vertical_right);
  CURSOR.x += 1;
  for (int i = 0; i < BOARD.size; ++i) {
    printf(l_horizontal);
    printf(l_verctical_horizontal);
    CURSOR.x += 2;
  }
  move_cursor(CURSOR.x - 1, CURSOR.y);
  printf(l_vertical_left);
  CURSOR.x += 1;
}

void draw_horizontal_middle_board(int start_x, int start_y, int row)
{
  move_cursor(start_x, start_y);
  for (int i = 0; i < BOARD.size; ++i) {
    printf("%s%c", l_vertical, BOARD.board[row * BOARD.size + i]);
    CURSOR.x += 2;
  }
  move_cursor(CURSOR.x, CURSOR.y);
  printf(l_vertical);
  CURSOR.x += 1;
}

void draw_horizontal_lines_bottom(int start_x, int start_y)
{
  move_cursor(start_x, start_y);
  printf(l_up_right);
  CURSOR.x += 1;
  for (int i = 0; i < BOARD.size; ++i) {
    printf(l_horizontal);
    printf(l_horizontal_up);
    CURSOR.x += 2;
  }
  move_cursor(CURSOR.x - 1, CURSOR.y);
  printf(l_up_left);
  CURSOR.x += 1;
}

void draw_board()
{
  draw_horizontal_lines_top(CURSOR.x, CURSOR.y);
  for (int i = 0; i < BOARD.size; ++i) {
    draw_horizontal_middle_board(1, (CURSOR.y + 1), i);
    draw_horizontal_lines_middle(1, (CURSOR.y + 1));
  }
  draw_horizontal_lines_bottom(1, CURSOR.y);
}
#include "tic_tac_toe.h"

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

  redraw_board();

  unsigned player_x = 0;
  unsigned player_y = 0;
  short flag = 1;
  unsigned count = 0;

  move_cursor(1, BOARD.size * 2 + 2);
  short runnig = 1;
  while (runnig) {
    scanf("%d%d", &player_x, &player_y);
    if (player_x == 0 || player_y == 0) {
      runnig = 0;
    } else {
      if (is_valid_pos(player_x, player_y)) {
        ++count;
        if (flag) {
          BOARD.board[(player_y - 1) * BOARD.size + (player_x - 1)] = 'X';
          flag = 0;
        } else {
          BOARD.board[(player_y - 1) * BOARD.size + (player_x - 1)] = 'O';
          flag = 1;
        }

        if (count == BOARD.size * BOARD.size) {
          //if (is_win(flag)) {
          //  runnig = 0;
          //}
          runnig = 0;
        }

        redraw_board();
        move_cursor(1, BOARD.size * 2 + 2);
      } else {
        redraw_board();
        move_cursor(1, BOARD.size * 2 + 2);
      }
    }
  }

  free(BOARD.board);
}

short is_valid_pos(unsigned x, unsigned y)
{
  if (x < 1 || x > BOARD.size)
    return 0;
  if (y < 1 || y > BOARD.size)
    return 0;
  return 1;
}

short is_win(short flag)
{
  char s;
  if (flag = 1)
    s = 'X';
  else
    s = 'O';

  for (int i = 0; i < BOARD.size; ++i) {
    for (int j = 0; j < BOARD.size; ++j) {

    }
  }
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

void redraw_board()
{
  cls;
  move_cursor(1, 1);
  draw_board();
}
// ESC commands
#define home                     printf("\033[H")
#define cls                      printf("\033[2J")
#define move_cursor_(x,y)        printf("\033[%d;%dH", y, x)
#define hide_cursor              printf("\033[?251l")
#define show_cursor              printf("\033[?251h")
#define resetcolor               printf("\033[0m")
#define set_display_atrib(color) printf("\033[%dm", color)
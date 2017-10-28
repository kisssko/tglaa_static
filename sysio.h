
#ifdef _WIN32
#include <windows.h>
#define io_sleep(S) Sleep((DWORD)(S))
#endif

void io_init(void);
void io_cleanup(void);
void io_clrscr(void);
void io_gotoxy(int x, int y);
void io_putchar(int c);
void io_textcolor(int c);
void io_flush(void);
int  io_kbhit(void);
int  io_get_width(void);
int  io_get_height(void);
unsigned int io_get_ticks(void);

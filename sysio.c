
#include "sysio.h"
#include "tglaa.h"

extern int		appflags;
extern float	shift_x;
extern float	shift_y;
extern float	shift_z;

#ifdef _WIN32
HANDLE     sys_stdin;
HANDLE     sys_stdout;
HANDLE     sys_stderr;
COORD      zero_coord={0,0};
COORD      tbsz;
CHAR_INFO *txtbuf;
DWORD      tbidx=0;
DWORD      cm_old;
WORD       txa;

void mouse_handler(MOUSE_EVENT_RECORD *mev)
{
	static COORD hc;
	static DWORD bs;
	COORD mp;
	bs=mev->dwButtonState;
	switch(mev->dwEventFlags)
	{
		case 0:
			if(bs&1) SETBIT(appflags,APPFLAG_PAUSE);
			else     CLRBIT(appflags,APPFLAG_PAUSE);
			if(bs&4)
			{
				CLRBIT(appflags, APPFLAG_SHIFT);
				shift_x=0.0; shift_y=0.0; shift_z=0.0;
			}
			break;
		case MOUSE_MOVED:
			mp=mev->dwMousePosition;
			if(bs&1)
				rotate_scene((float)((mp.X-hc.X)*4),
							 (float)((mp.Y-hc.Y)*4));
			if(bs&2)
			{
				SETBIT(appflags, APPFLAG_SHIFT);
				shift_x+=(float)(mp.X-hc.X)*6;
				shift_y-=(float)(mp.Y-hc.Y)*6;
			}
			hc=mev->dwMousePosition;
			break;
		case MOUSE_WHEELED:
			SETBIT(appflags, APPFLAG_SHIFT);
			shift_z-=((float)((short)(bs>>16))/8.0);
			break;
	}
}

void update_winsize(void)
{
	CONSOLE_SCREEN_BUFFER_INFO sbi;
	GetConsoleScreenBufferInfo(sys_stdout, &sbi);
	tbsz.X=(SHORT)(sbi.srWindow.Right-sbi.srWindow.Left+1);
	tbsz.Y=(SHORT)(sbi.srWindow.Bottom-sbi.srWindow.Top+1);
}

void resize_handler(void)
{
	update_winsize();
	SETBIT(appflags,APPFLAG_UPDREQ);
}

BOOL WINAPI event_handler(DWORD ev)
{
	switch(ev)
	{
		case CTRL_C_EVENT:
		case CTRL_BREAK_EVENT:
		case CTRL_CLOSE_EVENT:
		case CTRL_LOGOFF_EVENT:
		case CTRL_SHUTDOWN_EVENT:
			SETBIT(appflags, APPFLAG_EXITREQ);
			break;
	}
	return TRUE;
}

#else
#endif

void io_init(void)
{
#ifdef _WIN32
	DWORD cm;
	sys_stdin	= GetStdHandle(STD_INPUT_HANDLE);
	sys_stdout	= GetStdHandle(STD_OUTPUT_HANDLE);
	sys_stderr	= GetStdHandle(STD_ERROR_HANDLE);
	GetConsoleMode(sys_stdin, &cm);
	cm_old=cm;
	SETBIT(cm,ENABLE_WINDOW_INPUT);
	SetConsoleMode(sys_stdin, cm);
	update_winsize();
	txtbuf=(CHAR_INFO*)malloc(tbsz.X*tbsz.Y*sizeof(CHAR_INFO));
#else
#endif
}

void io_cleanup(void)
{
#ifdef _WIN32
	free((void*)txtbuf);
	SetConsoleMode(sys_stdin, cm_old);
#else
#endif
}

void io_gotoxy(int x, int y)
{
#ifdef _WIN32
	x--;y--;
	tbidx=(DWORD)tbsz.X*y+x;
#else
#endif
}

void io_putchar(int c)
{
#ifdef _WIN32
	txtbuf[tbidx].Char.AsciiChar=(CHAR)c;
	txtbuf[tbidx].Attributes=txa;
	tbidx++;
#else
#endif
}

void io_textcolor(int c)
{
#ifdef _WIN32
	txa=(WORD)c;
#else
#endif
}

int io_kbhit(void)
{
	int ret=0;
#ifdef _WIN32
	DWORD n;
	INPUT_RECORD ev;
	PeekConsoleInputA(sys_stdin,&ev,1,&n);
	while(n)
	{
		ReadConsoleInputA(sys_stdin,&ev,1,&n);
		if((ev.EventType&KEY_EVENT)&&(ev.Event.KeyEvent.bKeyDown))
			ret=1;
		if(ev.EventType&MOUSE_EVENT)
			mouse_handler(&(ev.Event.MouseEvent));
		if(ev.EventType&WINDOW_BUFFER_SIZE_EVENT)
			resize_handler();
		PeekConsoleInputA(sys_stdin,&ev,1,&n);
	}
#else
#endif
	return ret;
}

void io_flush(void)
{
#ifdef _WIN32
	SMALL_RECT wrgn;
	wrgn.Top=0;
	wrgn.Left=0;
	wrgn.Right=tbsz.X-1;
	wrgn.Bottom=tbsz.Y-1;
	WriteConsoleOutputA(sys_stdout, txtbuf, tbsz, zero_coord, &wrgn);
#else
#endif
}

void io_clrscr(void)
{
#ifdef _WIN32
	int i,sz;
	CHAR_INFO ci;
	sz=((int)tbsz.X)*((int)tbsz.Y);
	ci.Char.AsciiChar=32;
	ci.Attributes=7;
	for(i=0;i<sz;i++) txtbuf[i]=ci;
	io_flush();
#else
#endif
}

int io_get_width(void)
{
#ifdef _WIN32
	return (int)tbsz.X;
#else
#endif
}

int io_get_height(void)
{
#ifdef _WIN32
	return (int)tbsz.Y;
#else
#endif
}

unsigned int io_get_ticks(void)
{
#ifdef _WIN32
	return (unsigned int)GetTickCount();
#else
#endif
}


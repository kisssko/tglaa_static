
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tgl.h"
#include "tglaa.h"
#include "sysio.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

typedef void (*SCENE_PROC)(void);

int scrw, scrh;
tgl_context *tgc=NULL;
u16 *tglfbs[1];
int appflags=0;
int scene_n=0;
float shift_x=0.0;
float shift_y=0.0;
float shift_z=0.0;
u32   oticks;

SCENE_PROC scenes[2]={scene1, scene2};

void app_init(void)
{
	io_init();
	scrw=io_get_width();
	scrh=io_get_height()-1;
	tglfbs[0]=(u16*)malloc(scrw*scrh*sizeof(u16));
	memset((void*)tglfbs[0], 0, scrw*scrh*sizeof(u16));
	tgc=tglContextCreate(scrw, scrh, 16, (void*)tglfbs, 1);
	tglContextMakeCurrent(tgc, 0);
	init_gl(scrw, scrh);
}

void app_cleanup(void)
{
	tglContextDelete(tgc);
	free((void*)tglfbs[0]);
	io_cleanup();
}

int main(int argc, char **argv)
{
	app_init();
	oticks=io_get_ticks();
	while(!io_kbhit())
	{
		if(appflags&APPFLAG_EXITREQ) break;
		if(appflags&APPFLAG_UPDREQ)
		{
			app_cleanup();
			app_init();
			CLRBIT(appflags,APPFLAG_UPDREQ);
			io_clrscr();
		}
		scenes[((io_get_ticks()-oticks)>>13)&1]();
		if(appflags&APPFLAG_UPDREQ) continue;
		print_fb(tglfbs[0], scrw, scrh);
		if(!(appflags&APPFLAG_PAUSE))
			rotate_scene(360.0/256.0, 1.0/M_PI);
		io_sleep(10);
	}
	app_cleanup();
    return 0;
}


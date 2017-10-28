
#include "tglaa.h"
#include "tgl.h"

#define BRIGHT 0.75
#define PSHIFT  100
#define NSHIFT -100

#define CLEAR_OPS (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)

typedef struct {float x,y,z,t;} OBJECT_COORD;
typedef struct {float r,g,b,a;} OBJECT_COLOR;

OBJECT_COORD	objcrd[8]=
{
	{0     ,0     ,0     ,0},
	{0     ,0     ,NSHIFT,0},
	{0     ,0     ,PSHIFT,0},
	{NSHIFT,0     ,0     ,0},
	{PSHIFT,0     ,0     ,0},
	{0     ,NSHIFT,0     ,0},
	{0     ,PSHIFT,0     ,0},
	{0     ,0     ,0     ,0}
};
OBJECT_COLOR	objclr[8]=
{
	{BRIGHT,BRIGHT,BRIGHT,1},
	{0     ,0     ,BRIGHT,1},
	{0     ,BRIGHT,0     ,1},
	{0     ,BRIGHT,BRIGHT,1},
	{BRIGHT,0     ,0     ,1},
	{BRIGHT,0     ,BRIGHT,1},
	{BRIGHT,BRIGHT,0     ,1},
	{0     ,0     ,0     ,1}
};

float	 roty=0.0;
float	 rotx=0.0;

extern int		appflags;
extern float	shift_x;
extern float	shift_y;
extern float	shift_z;

void rotate_scene(float axisy, float axisx)
{
	roty+=axisy;
	rotx+=axisx;
	while(roty>=360.0)  roty-=360.0;
	while(rotx>=360.0)  rotx-=360.0;
	while(roty<=-360.0) roty+=360.0;
	while(rotx<=-360.0) rotx+=360.0;
}

void scene1(void)
{
	int i;
	glClear(CLEAR_OPS);
//	glClearColor(0.75,0.0,0.0,0.0);

	glPushMatrix();
	glTranslatef(0,0,-25);
	glScalef(0.1,0.1,0.1);
	if(appflags&APPFLAG_SHIFT)
		glTranslatef(shift_x,shift_y,shift_z);
	glRotatef(roty, 0,1,0);
	glRotatef(rotx, 1,0,0);

	glColor3f(BRIGHT,BRIGHT,BRIGHT);
	//drawSquare(100);

	for(i=0;i<7;i++)
	{
		glColor3f(objclr[i].r,objclr[i].g,objclr[i].b);
		glPushMatrix();
		glTranslatef(objcrd[i].x,objcrd[i].y,objcrd[i].z);
		drawCube(50);
		glPopMatrix();
	}
	glPopMatrix();
}

void scene2(void)
{
	int i;
	glClear(CLEAR_OPS);
//	glClearColor(0.75,0.0,0.0,0.0);

	glPushMatrix();
	glTranslatef(0,0,-30);
	glScalef(0.1,0.1,0.1);
	if(appflags&APPFLAG_SHIFT)
		glTranslatef(shift_x,shift_y,shift_z);
	glRotatef(roty, 0,1,0);
	glRotatef(rotx, 1,0,0);

	glColor3f(BRIGHT,BRIGHT,BRIGHT);
	//drawSquare(100);

	for(i=0;i<7;i++)
	{
		glColor3f(objclr[i].r,objclr[i].g,objclr[i].b);
		glPushMatrix();
		glTranslatef(objcrd[i].x,objcrd[i].y,objcrd[i].z);
		glRotatef(32, 0,1,0);
		renderTeapot(30);
		glPopMatrix();
	}
	glPopMatrix();
}


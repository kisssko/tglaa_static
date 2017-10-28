#include "tglaa.h"
#include "tgl.h"

float	 pos[4] = {1,1,15,1};
float	 dir[3] = {-1,-1,-1};
float	 mat_ambient[]  = {1,1,1,1};
float	 mat_specular[] = {1,1,1,1};

void init_gl(int szx, int szy)
{
	GLdouble xmul, ymul;
	if(szx>szy) {ymul=1.0; xmul=((GLdouble)szx)/((GLdouble)szy);}
	else        {xmul=1.0; ymul=((GLdouble)szy)/((GLdouble)szx);}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

	glViewport(0,0,szx,szy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-3.0*xmul,3.0*xmul,-5.0*ymul,5.0*ymul,10.0,1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


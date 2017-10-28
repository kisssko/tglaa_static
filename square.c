
#include "tgl.h"

void drawSquare(float sz)
{
	glBegin(GL_QUADS);
		glNormal3f(0,0,1);
		glVertex3f(-(sz/2), -(sz/2), 0);
		glVertex3f(-(sz/2),  (sz/2), 0);
		glVertex3f( (sz/2),  (sz/2), 0);
		glVertex3f( (sz/2), -(sz/2), 0);
	glEnd();
}

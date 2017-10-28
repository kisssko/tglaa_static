
#include "tgl.h"

void drawCube(float sz)
{
	// front
	glBegin(GL_QUADS);
		glNormal3f(0,0,1);
		glVertex3f(-(sz/2), -(sz/2), (sz/2));
		glVertex3f(-(sz/2),  (sz/2), (sz/2));
		glVertex3f( (sz/2),  (sz/2), (sz/2));
		glVertex3f( (sz/2), -(sz/2), (sz/2));
	glEnd();
	// back
	glBegin(GL_QUADS);
		glNormal3f(0,0,-1);
		glVertex3f(-(sz/2), -(sz/2), -(sz/2));
		glVertex3f(-(sz/2),  (sz/2), -(sz/2));
		glVertex3f( (sz/2),  (sz/2), -(sz/2));
		glVertex3f( (sz/2), -(sz/2), -(sz/2));
	glEnd();
	// top
	glBegin(GL_QUADS);
		glNormal3f(0,1,0);
		glVertex3f(-(sz/2),  (sz/2),  (sz/2));
		glVertex3f(-(sz/2),  (sz/2), -(sz/2));
		glVertex3f( (sz/2),  (sz/2), -(sz/2));
		glVertex3f( (sz/2),  (sz/2),  (sz/2));
	glEnd();
	// bottom
	glBegin(GL_QUADS);
		glNormal3f(0,-1,0);
		glVertex3f(-(sz/2), -(sz/2),  (sz/2));
		glVertex3f(-(sz/2), -(sz/2), -(sz/2));
		glVertex3f( (sz/2), -(sz/2), -(sz/2));
		glVertex3f( (sz/2), -(sz/2),  (sz/2));
	glEnd();
	// left
	glBegin(GL_QUADS);
		glNormal3f(-1,0,0);
		glVertex3f(-(sz/2), -(sz/2), -(sz/2));
		glVertex3f(-(sz/2),  (sz/2), -(sz/2));
		glVertex3f(-(sz/2),  (sz/2),  (sz/2));
		glVertex3f(-(sz/2), -(sz/2),  (sz/2));
	glEnd();
	// right
	glBegin(GL_QUADS);
		glNormal3f(1,0,0);
		glVertex3f( (sz/2), -(sz/2),  (sz/2));
		glVertex3f( (sz/2),  (sz/2),  (sz/2));
		glVertex3f( (sz/2),  (sz/2), -(sz/2));
		glVertex3f( (sz/2), -(sz/2), -(sz/2));
	glEnd();

}

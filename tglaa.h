
#include "defs.h"

#define SETBIT(A,B) (A)|=(B)
#define CLRBIT(A,B) (A)&=(~(B))

#define APPFLAG_PAUSE		0x01
#define APPFLAG_UPDREQ		0x02
#define APPFLAG_SHIFT		0x04
#define APPFLAG_EXITREQ		0x08

void init_gl(int szx, int szy);
void scene1(void);
void scene2(void);
void print_fb(u16 *pfb, int w, int h);
void drawCube(float sz);
void rotate_scene(float axisy, float axisx);
void renderTeapot(float scale);

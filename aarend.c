
#include <stdio.h>
#include <math.h>
#include "tglaa.h"
#include "sysio.h"

u8 div3tab[96]=
{
	 0,  0,  0,  1,  1,  1,  2,  2,
	 2,  3,  3,  3,  4,  4,  4,  5,
	 5,  5,  6,  6,  6,  7,  7,  7,
	 8,  8,  8,  9,  9,  9, 10, 10,
    10, 11, 11, 11, 12, 12, 12, 13,
	13, 13, 14, 14, 14, 15, 15, 15,
	16, 16, 16, 17, 17, 17, 18, 18,
	18, 19, 19, 19, 20, 20, 20, 21,
	21, 21, 22, 22, 22, 23, 23, 23,
	24, 24, 24, 25, 25, 25, 26, 26,
	26, 27, 27, 27, 28, 28, 28, 29,
	29, 29, 30, 30, 30, 31, 31, 31
};

u8 tpal[]="   .-.:/+-,;%<?!*+$:/;@0<%?!*$@0";
u8 btab[]="00000100011000000101110011111111";

void print_fb(u16 *pfb, int w, int h)
{
	int otc=7;
	int x,y,c;
	u8 r,g,b,v,m;
	//io_gotoxy(1,1);
	for(y=0;y<h;y++)
	{
		io_gotoxy(1,y+1);
		for(x=0;x<w;x++)
		{
			v=0; c=0; m=0;
			r=*pfb>>11;
			g=(*pfb>>6)&0x1F;
			b=*pfb&0x1F;
			if(r>v)v=r;
			if(g>v)v=g;
			if(b>v)v=b;
			m=div3tab[r+g+b]; // m=(r+g+b)/3;
			if(r>=m)c|=4;
			if(g>=m)c|=2;
			if(b>=m)c|=1;
			//if(v&16)c|=8;
			if(btab[v]&1)c|=8;
			if(c!=otc)io_textcolor(c);
			otc=c;
			io_putchar(tpal[v]);
			pfb++;
		}
	}
	io_flush();
}

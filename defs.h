

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef struct
{
	u8 R,G,B,A;
} RGBA8888_t;

typedef struct
{
	u16 B:5;
	u16 G:6;
	u16 R:5;
} BGR565_t;

typedef union
{
	u16       I;
	BGR565_t  C;
} COLOR16_t;


#ifndef __CIRCUIT_HEADER__
#define __CIRCUIT_HEADER__


#include "stdint.h"



typedef enum{
	G_EQ	= 0,
	G_NOT	= 1,
	G_AND	= 2,
	G_NAND	= 3,
	G_OR	= 4,
	G_NOR	= 5,
	G_XOR	= 6,
	G_XNOR	= 7,
	G_SLAT	= 8,
	G_DLAT	= 9
}GateKind;

typedef struct{
	uint32_t a, b, c, m;
	union{
		uint16_t width;		// normal gates
		struct{
			uint8_t  h;		// sram
			uint8_t  w;
		};
	};
	GateKind k;
}Gate;

typedef struct{
	char name[16];
	int  bs, width;
}Buffer;

typedef struct{
	Gate*		gates;
	int			fill, size;
	
	uint64_t*	bits;
	uint64_t*	next;
	
	int			wirect, maxwires, wiresize;
	
	int			time;
	
	Buffer*		bufs;
	int			bfill, bsize;
}Circuit;


void	printCircuit	(Circuit);
void	readCircuit		(Circuit);

Circuit	makeCircuit		(int, int);
int		circMakeWires	(Circuit*, int);
int		circMakeGate	(Circuit*, GateKind, int, int, int, int);



#endif

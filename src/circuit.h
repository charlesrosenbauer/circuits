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
	G_XNOR	= 7
}GateKind;

typedef struct{
	uint32_t a, b, c;
	uint32_t width;
	GateKind k;
}Gate;

typedef struct{
	Gate*	gates;
	int		fill, size, wirect;
}Circuit;


void	printCircuit	(Circuit);

Circuit	makeCircuit		(int);
int		circMakeWires	(Circuit*, int);
int		circMakeGate	(Circuit*, GateKind, int, int, int, int);



#endif

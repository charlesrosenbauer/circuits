#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"



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
	GateKind k;
}Gate;

typedef struct{
	Gate*	gates;
	int		fill, size, wirect;
}Circuit;


int main(){
	printf("Hello world!\n");
}

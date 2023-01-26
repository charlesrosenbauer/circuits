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


void printCircuit(Circuit c){
	printf("====CIRC %6i : %6i====\n", c.fill, c.wirect);
	for(int i = 0; i < c.fill; i++){
		switch(c.gates[i].k){
			case G_EQ	: printf("EQ   %6i %6i > %6i\n", c.gates[i].a,            0, c.gates[i].c ); break;
			case G_NOT	: printf("NOT  %6i %6i > %6i\n", c.gates[i].a,            0, c.gates[i].c ); break;
			case G_AND	: printf("AND  %6i %6i > %6i\n", c.gates[i].a, c.gates[i].b, c.gates[i].c ); break;
			case G_NAND	: printf("NAND %6i %6i > %6i\n", c.gates[i].a, c.gates[i].b, c.gates[i].c ); break;
			case G_OR	: printf("OR   %6i %6i > %6i\n", c.gates[i].a, c.gates[i].b, c.gates[i].c ); break;
			case G_NOR	: printf("NOR  %6i %6i > %6i\n", c.gates[i].a, c.gates[i].b, c.gates[i].c ); break;
			case G_XOR	: printf("XOR  %6i %6i > %6i\n", c.gates[i].a, c.gates[i].b, c.gates[i].c ); break;
			case G_XNOR	: printf("XNOR %6i %6i > %6i\n", c.gates[i].a, c.gates[i].b, c.gates[i].c ); break;
		}
	}
}




int main(){
	printf("Hello world!\n");
}

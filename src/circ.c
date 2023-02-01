#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

#include "circuit.h"



void printCircuit(Circuit c){
	printf("====CIRC %6i : %6i====\n", c.fill, c.wirect);
	for(int i = 0; i < c.fill; i++){
		printf("%06x : ", i);
		switch(c.gates[i].k){
			case G_EQ	: printf("EQ   [%4i] %6i %6i > %6i\n", c.gates[i].width, c.gates[i].a,            0, c.gates[i].c ); break;
			case G_NOT	: printf("NOT  [%4i] %6i %6i > %6i\n", c.gates[i].width, c.gates[i].a,            0, c.gates[i].c ); break;
			case G_AND	: printf("AND  [%4i] %6i %6i > %6i\n", c.gates[i].width, c.gates[i].a, c.gates[i].b, c.gates[i].c ); break;
			case G_NAND	: printf("NAND [%4i] %6i %6i > %6i\n", c.gates[i].width, c.gates[i].a, c.gates[i].b, c.gates[i].c ); break;
			case G_OR	: printf("OR   [%4i] %6i %6i > %6i\n", c.gates[i].width, c.gates[i].a, c.gates[i].b, c.gates[i].c ); break;
			case G_NOR	: printf("NOR  [%4i] %6i %6i > %6i\n", c.gates[i].width, c.gates[i].a, c.gates[i].b, c.gates[i].c ); break;
			case G_XOR	: printf("XOR  [%4i] %6i %6i > %6i\n", c.gates[i].width, c.gates[i].a, c.gates[i].b, c.gates[i].c ); break;
			case G_XNOR	: printf("XNOR [%4i] %6i %6i > %6i\n", c.gates[i].width, c.gates[i].a, c.gates[i].b, c.gates[i].c ); break;
			case G_SLAT	: printf("SLAT [%4i] %6i %6i > %6i\n", c.gates[i].width, c.gates[i].a, c.gates[i].b, c.gates[i].c ); break;
			case G_DLAT	: printf("DLAT [%4i] %6i %6i > %6i\n", c.gates[i].width, c.gates[i].a, c.gates[i].b, c.gates[i].c ); break;
		}
	}
}


Circuit	makeCircuit(int size, int wirect){
	Circuit ret;
	ret.gates 		= malloc(sizeof(Gate) * size);
	ret.fill  		= 0;
	ret.size  		= size;
	ret.wirect		=   wirect;
	ret.maxwires	= ((wirect * 2) + 63) & -64;
	ret.wiresize	=  (wirect / 64) + ((wirect % 64) != 0);
	
	ret.bits		= malloc(sizeof(uint64_t) * ret.maxwires / 64);
	ret.next		= malloc(sizeof(uint64_t) * ret.maxwires / 64);
	for(int i = 0; i < ret.maxwires / 64; i++){ ret.bits[i] = 0; ret.next[i] = 0; }
	return ret;
}



int		circMakeWires(Circuit* c, int wires){
	int ret    = c->wirect;
	c->wirect += wires;
	return ret;
}


int		circMakeGate(Circuit* c, GateKind k, int a, int b, int q, int width){
	if(c->fill+5 >= c->size){
		Gate* tmp = c->gates;
		c->size  *= 2;
		c->gates  = malloc(sizeof(Gate) * c->size);
		for(int i = 0; i < c->fill; i++)  c->gates[i] = tmp[i];
		free(tmp);
	}
	c->gates[c->fill] = (Gate){.k=k, .a=a, .b=b, .c=q, .width=width};
	c->fill++;
	return c->fill-1;
}




#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

#include "circuit.h"



void printCircuit(Circuit c){
	printf("====CIRC %6i : %6i====\n", c.fill, c.wirect);
	for(int i = 0; i < c.fill; i++){
		printf("%06x : ", i);
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


Circuit	makeCircuit(int size){
	Circuit ret;
	ret.gates  = malloc(sizeof(Gate) * size);
	ret.fill   = 0;
	ret.size   = size;
	ret.wirect = 0;
	return ret;
}



int		circMakeWires(Circuit* c, int wires){
	int ret    = c->wirect;
	c->wirect += wires;
	return ret;
}


int		circMakeGate(Circuit* c, GateKind k, int a, int b, int q){
	if(c->fill+5 >= c->size){
		Gate* tmp = c->gates;
		c->size  *= 2;
		c->gates  = malloc(sizeof(Gate) * c->size);
		for(int i = 0; i < c->fill; i++)  c->gates[i] = tmp[i];
		free(tmp);
	}
	c->gates[c->fill] = (Gate){.k=k, .a=a, .b=b, .c=q};
	c->fill++;
	return c->fill-1;
}


int		circMakeGates	(Circuit* c, GateKind k, int as, int bs, int qs, int ct){
	if(c->fill+ct+5 >= c->size){
		Gate* tmp = c->gates;
		c->size  *= 2;
		c->gates  = malloc(sizeof(Gate) * c->size);
		for(int i = 0; i < c->fill; i++)  c->gates[i] = tmp[i];
		free(tmp);
	}
	for(int i = 0; i < ct; i++)
		c->gates[c->fill+i] = (Gate){.k=k, .a=as+i, .b=bs+i, .c=qs+i};
	c->fill += ct;
	return c->fill-ct;
}

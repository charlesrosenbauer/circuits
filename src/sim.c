#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

#include "circuit.h"




void simulatorStep(Circuit* c){
	int* wiredeltas = malloc(sizeof(int) * c->wiresize);
	for(int i = 0; i < c->fill; i++){
		/*
			TODO:
			* simulate gates
			* account for changing wires
		*/
		switch(c->gates[i].k){
			case G_EQ	: break;
			case G_NOT	: break;
			case G_AND	: break;
			case G_NAND	: break;
			case G_OR	: break;
			case G_NOR	: break;
			case G_XOR	: break;
			case G_XNOR	: break;
			case G_SLAT	: break;
			case G_DLAT	: break;
		}
	}
}

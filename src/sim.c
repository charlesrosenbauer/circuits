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
		Gate g = c->gates[i];
		if((g.k == G_SLAT) || (g.k == G_DLAT)){
			// MEMORY
		}else{
			int aix = g.a;
			int bix = g.b;
			int qix = g.c;
			for(int j = 0; j < g.width; j += 64){
				// TODO: handle cases for unaligned bits
				uint64_t a, b, q;
				a = c->wirebits[aix / 64];
				b = c->wirebits[bix / 64];
				
				switch(g.k){
					case G_EQ	: q =       a ; break;
					case G_NOT	: q =      ~a ; break;
					case G_AND	: q =   a & b ; break;
					case G_NAND	: q = ~(a & b); break;
					case G_OR	: q =   a | b ; break;
					case G_NOR	: q = ~(a | b); break;
					case G_XOR	: q =   a ^ b ; break;
					case G_XNOR	: q = ~(a ^ b); break;
				}
				
				c->wirebits[qix/64] = q;
			}
		}
	}
}

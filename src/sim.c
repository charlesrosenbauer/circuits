#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

#include "circuit.h"




void simulatorStep(Circuit* c){
	for(int i = 0; i < c->fill; i++){
		/*
			TODO:
			* simulate gates
			* account for changing wires
		*/
		Gate g = c->gates[i];
		switch(g.k){
			case G_EQ	: {
				for(int j = 0; j < g.width; j++){
					uint64_t am = 1l << ((g.a + j) % 64);
					uint64_t ai = (g.a + j) / 64;
					uint64_t cm = 1l << ((g.c + j) % 64);
					uint64_t ci = (g.c + j) / 64;
					c->wirebits[ci] &= ~cm;
					c->wirebits[ci] |= (c->wirebits[ai] & am)? cm : 0;
				}
			}break;
			case G_NOT	: {
				for(int j = 0; j < g.width; j++){
					uint64_t am = 1l << ((g.a + j) % 64);
					uint64_t ai = (g.a + j) / 64;
					uint64_t cm = 1l << ((g.c + j) % 64);
					uint64_t ci = (g.c + j) / 64;
					c->wirebits[ci] &= ~cm;
					c->wirebits[ci] |= (c->wirebits[ai] & am)? 0 : cm;
				}
			}break;
			case G_AND	: {
				for(int j = 0; j < g.width; j++){
					uint64_t am = 1l << ((g.a + j) % 64);
					uint64_t ai = (g.a + j) / 64;
					uint64_t bm = 1l << ((g.b + j) % 64);
					uint64_t bi = (g.b + j) / 64;
					uint64_t cm = 1l << ((g.c + j) % 64);
					uint64_t ci = (g.c + j) / 64;
					c->wirebits[ci] &= ~cm;
					c->wirebits[ci] |= ((c->wirebits[ai] & am) && (c->wirebits[bi] & bm))? cm : 0;
				}
			}break;
			case G_NAND	: {
				for(int j = 0; j < g.width; j++){
					uint64_t am = 1l << ((g.a + j) % 64);
					uint64_t ai = (g.a + j) / 64;
					uint64_t bm = 1l << ((g.b + j) % 64);
					uint64_t bi = (g.b + j) / 64;
					uint64_t cm = 1l << ((g.c + j) % 64);
					uint64_t ci = (g.c + j) / 64;
					c->wirebits[ci] &= ~cm;
					c->wirebits[ci] |= ((c->wirebits[ai] & am) && (c->wirebits[bi] & bm))? 0 : cm;
				}
			}break;
			case G_OR	: {
				for(int j = 0; j < g.width; j++){
					uint64_t am = 1l << ((g.a + j) % 64);
					uint64_t ai = (g.a + j) / 64;
					uint64_t bm = 1l << ((g.b + j) % 64);
					uint64_t bi = (g.b + j) / 64;
					uint64_t cm = 1l << ((g.c + j) % 64);
					uint64_t ci = (g.c + j) / 64;
					c->wirebits[ci] &= ~cm;
					c->wirebits[ci] |= ((c->wirebits[ai] & am) || (c->wirebits[bi] & bm))? cm : 0;
				}
			}break;
			case G_NOR	: {
				for(int j = 0; j < g.width; j++){
					uint64_t am = 1l << ((g.a + j) % 64);
					uint64_t ai = (g.a + j) / 64;
					uint64_t bm = 1l << ((g.b + j) % 64);
					uint64_t bi = (g.b + j) / 64;
					uint64_t cm = 1l << ((g.c + j) % 64);
					uint64_t ci = (g.c + j) / 64;
					c->wirebits[ci] &= ~cm;
					c->wirebits[ci] |= ((c->wirebits[ai] & am) || (c->wirebits[bi] & bm))? 0 : cm;
				}
			}break;
			
			// TODO: xor, xnor, sram
			case G_XOR	: {
				
			}break;
			case G_XNOR	: {
			
			}break;
			case G_SLAT	: {
			
			}break;
			case G_DLAT	: {
			
			}break;
		}
	}
}

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
				for(int j = 0; j < g.width; j++){
					uint64_t am = 1l << ((g.a + j) % 64);
					uint64_t ai = (g.a + j) / 64;
					uint64_t bm = 1l << ((g.b + j) % 64);
					uint64_t bi = (g.b + j) / 64;
					uint64_t cm = 1l << ((g.c + j) % 64);
					uint64_t ci = (g.c + j) / 64;
					
					int a = (c->wirebits[ai] & am) != 0;
					int b = (c->wirebits[bi] & bm) != 0;
					c->wirebits[ci] &= ~cm;
					c->wirebits[ci] |= (a != b)? cm : 0;
				}
			}break;
			case G_XNOR	: {
				for(int j = 0; j < g.width; j++){
					uint64_t am = 1l << ((g.a + j) % 64);
					uint64_t ai = (g.a + j) / 64;
					uint64_t bm = 1l << ((g.b + j) % 64);
					uint64_t bi = (g.b + j) / 64;
					uint64_t cm = 1l << ((g.c + j) % 64);
					uint64_t ci = (g.c + j) / 64;
					
					int a = (c->wirebits[ai] & am) != 0;
					int b = (c->wirebits[bi] & bm) != 0;
					c->wirebits[ci] &= ~cm;
					c->wirebits[ci] |= (a != b)? 0 : cm;
				}
			}break;
			case G_SLAT	: {
				for(int j = 0; j < g.h; j++){
					// selector bits
					uint64_t sm = 1l << ((g.a + j) % 64);
					uint64_t si = (g.a + j) / 64;
					if(c->wirebits[si] & sm){
						for(int k = 0; k < g.w; k++){
							// bitline
							uint64_t am = 1l << ((g.a + k) % 64);
							uint64_t ai = (g.a + k) / 64;
							// inverse bitline
							uint64_t bm = 1l << ((g.b + k) % 64);
							uint64_t bi = (g.b + k) / 64;
							// memory
							uint64_t mm = 1l << ((g.m + (j * g.w) + k) % 64);
							uint64_t mi = (g.m + (j * g.w) + k) / 64;
							
							int a = (c->wirebits[ai] & am) != 0;
							int b = (c->wirebits[bi] & bm) != 0;
							int m = (c->wirebits[mi] & mm) != 0;
							
							b = ~(a | m);
							m = ~ b;
							a =   m;
							
							c->wirebits[ai] |= a? am : 0;
							
							c->wirebits[bi] |= b? bm : 0;
							
							c->wirebits[mi] &= ~mm;
							c->wirebits[mi] |= m? mm : 0;
						}
					}
				}
			}break;
			case G_DLAT	: {
				for(int j = 0; j < g.width; j++){
					// set
					uint64_t am = 1l << ((g.a + j) % 64);
					uint64_t ai = (g.a + j) / 64;
					// enable
					uint64_t bm = 1l << ((g.b + j) % 64);
					uint64_t bi = (g.b + j) / 64;
					// output
					uint64_t cm = 1l << ((g.c + j) % 64);
					uint64_t ci = (g.c + j) / 64;
					
					int a = (c->wirebits[ai] & am) != 0;
					int b = (c->wirebits[bi] & bm) != 0;
					
					if(b){
						c->wirebits[ci] &= ~cm;
						c->wirebits[ci] |= a? cm : 0;
					}
				}
			}break;
		}
	}
}

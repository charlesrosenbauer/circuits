#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

#include "circuit.h"



int main(){
	Circuit c = makeCircuit(512);
	
	int as = circMakeWires(&c, 64);
	int bs = circMakeWires(&c, 64);
	int qs = circMakeWires(&c, 64);
	
	circMakeGate(&c, G_NAND, as, bs, qs, 64);
	
	printCircuit(c);
}

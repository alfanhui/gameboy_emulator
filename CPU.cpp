#include <iostream>
#include <string>
#include "CPU.h"
#include "MMU.h"
#include <uchar.h>


CPU::CPU() {
	af->joined = 0;
	bc->joined = 0;
	de->joined = 0;
	hl->joined = 0;
	sp->joined = 0;
	pc->joined = 0;
}

void CPU::runInstruction()
{

}

void CPU::destroyCpu(CPU* cpu) {
	delete cpu;
}

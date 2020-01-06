#include <iostream>
#include <string>
#include "CPU.h"
#include "MMU.h"


void CPU::runInstruction()
{

}

void CPU::destroyCpu(CPU* cpu) {
	delete cpu;
}
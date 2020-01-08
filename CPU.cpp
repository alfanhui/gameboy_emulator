#include <iostream>
#include <string>
#include "CPU.h"
#include "MMU.h"
#include <uchar.h>



void CPU::runInstruction()
{

}

void CPU::destroyCpu(CPU* cpu) {
	delete cpu;
}

char16_t CPU::registers::read16(CPU::registers* reg, char addr)
{
	return *((char16_t*)(reg->array + addr));
}

void CPU::registers::write16(CPU::registers* reg, char addr, char16_t data)
{
	char16_t* pos = ((char16_t*)(reg->array + addr));
	*pos = data;
}

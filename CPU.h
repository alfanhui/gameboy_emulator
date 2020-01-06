#pragma once
#include <cstdint>
#include <string>
#include "MMU.h"

struct registers {
	char A;
	char B;
	char D;
	char H;
	char F;
	char C;
	char E;
	char L;
	char16_t SP;
	char16_t PC;
};

class CPU
{
public: 
	void runInstruction();
	void destroyCpu(CPU* cpu);
};



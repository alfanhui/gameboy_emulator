#pragma once
#include <cstdint>
#include <string>
#include "CPURegister.h"

class CPU
{
private:
	CPURegister* af = new CPURegister();
	CPURegister* bc = new CPURegister();
	CPURegister* de = new CPURegister();
	CPURegister* hl = new CPURegister();
	CPURegister* sp = new CPURegister();
	CPURegister* pc = new CPURegister();

public:
	CPU();
	void runInstruction();
	void destroyCpu(CPU* cpu);

};



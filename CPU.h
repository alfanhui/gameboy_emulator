#pragma once
#include <cstdint>
#include <string>
#include "CPURegister.h"

class CPU
{
private:
	CPURegister* reg;
public:
	CPU();
	void runInstruction(uint8_t opcode, uint8_t n);
	void LDnn_n(uint8_t reg, uint8_t n);
	void LDr1_r2(uint8_t opcode, uint8_t n);
	void destroyCpu(CPU* cpu);

};



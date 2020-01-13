#pragma once
#include <cstdint>
#include <string>
#include "CPURegister.h"
#include "MMU.h"

class CPU
{
private:
	CPURegister* _reg;
	MMU* _mmu;
public:
	CPU(MMU* mmu, CPURegister* reg) : _mmu(mmu), _reg(reg) {}
	void runInstruction(uint16_t opcode);
	void LDnn_n(uint16_t opcode);
	void LDr1_r2(uint16_t opcode);
	void LDA_n(uint16_t opcode);
	void LDn_A(uint16_t opcode);
	void LDn_nn16(uint16_t opcode);
	void destroyCpu(CPU* cpu);
};



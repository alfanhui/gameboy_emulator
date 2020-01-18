#pragma once
#include <cstdint>
#include <string>
#include "CPURegister.h"
#include "CPUFlags.h"
#include "MMU.h"

class CPU
{
private:
	CPURegister* _reg;
	MMU* _mmu;
	CPUFlags* _flags;
public:
	CPU(MMU* mmu, CPURegister* reg, CPUFlags* flags) : _mmu(mmu), _reg(reg), _flags(flags) {}
	void runInstruction(uint16_t opcode);
	void LDnn_n(uint16_t opcode);
	void LDr1_r2(uint16_t opcode);
	void LDA_n(uint16_t opcode);
	void LDn_A(uint16_t opcode);
	void LDA_C(uint16_t opcode);
	void LDC_A(uint16_t opcode);
	void LDA_HLneg(uint16_t opcode);
	void LDDA_HLpos(uint16_t opcode);
	void LDIHL_A(uint16_t opcode);
	void LDN_A(uint16_t opcode);
	void LDA_N(uint16_t opcode);
	void LDn_nn16(uint16_t opcode);
	void LDSP_HL(uint16_t opcode);
	void LDHL_SPn(uint16_t opcode);
	void LDNN_SP(uint16_t opcode);
	void PUSHnn(uint16_t opcode);
	void POPnn(uint16_t opcode);
	void ADDA_n(uint16_t opcode);
	void ABCA_n(uint16_t opcode);
	void SUBA_n(uint16_t opcode);
	void SBCA_n(uint16_t opcode);
	void destroyCpu(CPU* cpu);
};



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
	bool _halt = false;
	bool _ime = true; //interrupt master enable
public:
	CPU(MMU* mmu, CPURegister* reg, CPUFlags* flags) : _mmu(mmu), _reg(reg), _flags(flags) {}
	void runInstruction(uint8_t opcode);
	void LDnn_n(uint8_t opcode);
	void LDr1_r2(uint8_t opcode);
	void LDA_n(uint8_t opcode);
	void LDn_A(uint8_t opcode);
	void LDA_C(uint8_t opcode);
	void LDC_A(uint8_t opcode);
	void LDA_HLneg(uint8_t opcode);
	void LDDA_HLpos(uint8_t opcode);  
	void LDIHL_A(uint8_t opcode);
	void LDN_A(uint8_t opcode);
	void LDA_N(uint8_t opcode);
	void LDn_nn16(uint8_t opcode);
	void LDSP_HL(uint8_t opcode);
	void LDHL_SPn(uint8_t opcode);
	void LDNN_SP(uint8_t opcode);
	void PUSHnn(uint8_t opcode);
	void POPnn(uint8_t opcode);
	void ADDA_n(uint8_t opcode);
	void ABCA_n(uint8_t opcode);
	void SUBA_n(uint8_t opcode);
	void SBCA_n(uint8_t opcode);
	void ANDA_n(uint8_t opcode);
	void ORA_n(uint8_t opcode);
	void XORA_n(uint8_t opcode);
	void CPA_n(uint8_t opcode);
	void INCN(uint8_t opcode);
	void DECN(uint8_t opcode);
	void ADDHL_n16(uint8_t opcode);
	void ADDSP_n16(uint8_t opcode);
	void INCnn16(uint8_t opcode);
	void DECnn16(uint8_t opcode);
	void CB(uint8_t opcode);
	void SWAPN(uint8_t cb_opcode);
	void DAA();
	void CPL();
	void CCF();
	void SCF();
	void NOP();
	void HALT();
	void TEN();
	void STOP();
	void DI();
	void EI();
	void RLCA();
	void RLA();
	void RRCA();
	void RRA();
	void RLCN(uint8_t cb_opcode);
	void RLN(uint8_t cb_opcode);
	void RRCN(uint8_t cb_opcode);
	void RRN(uint8_t cb_opcode);
	void destroyCpu(CPU* cpu);
};



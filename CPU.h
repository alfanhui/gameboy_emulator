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
	bool _ime = false; //interrupt master enable
public:
	CPU(MMU* mmu, CPURegister* reg, CPUFlags* flags) : _mmu(mmu), _reg(reg), _flags(flags) {}
	void RunInstruction(uint8_t opcode);
	void LdNnN(uint8_t opcode);
	void LdR1R2(uint8_t opcode);
	void LdAN(uint8_t opcode);
	void LdNA(uint8_t opcode);
	void LdAC(uint8_t opcode);
	void LdCA(uint8_t opcode);
	void LdAHlneg(uint8_t opcode);
	void LddAHlpos(uint8_t opcode);  
	void LdiHlA(uint8_t opcode);
	void LdhNA(uint8_t opcode);
	void LdhAN(uint8_t opcode);
	void LdNNn16(uint8_t opcode);
	void LdSpHl(uint8_t opcode);
	void LdHlSpn(uint8_t opcode);
	void LdNnSp(uint8_t opcode);
	void PushNn(uint8_t opcode);
	void PopNn(uint8_t opcode);
	void AddAN(uint8_t opcode);
	void AbcAN(uint8_t opcode);
	void SubAN(uint8_t opcode);
	void SbcAN(uint8_t opcode);
	void AndAN(uint8_t opcode);
	void OrAN(uint8_t opcode);
	void XorAN(uint8_t opcode);
	void CpaN(uint8_t opcode);
	void IncN(uint8_t opcode);
	void DecN(uint8_t opcode);
	void AddHlN16(uint8_t opcode);
	void AddSpN16(uint8_t opcode);
	void IncNn16(uint8_t opcode);
	void DecNn16(uint8_t opcode);
	void Cb(uint8_t opcode);
	void SwapN(uint8_t cb_opcode);
	void Daa();
	void Cpl();
	void Ccf();
	void Scf();
	void Nop();
	void Halt();
	void Ten();
	void Stop();
	void Di();
	void Ei();
	void Rlca();
	void Rla();
	void Rrca();
	void Rra();
	void RlcN(uint8_t cb_opcode);
	void RlN(uint8_t cb_opcode);
	void RrcN(uint8_t cb_opcode);
	void RrN(uint8_t cb_opcode);
	void SlaN(uint8_t opcode);
	void SraN(uint8_t cb_opcode);
	void destroyCpu(CPU* cpu);
};



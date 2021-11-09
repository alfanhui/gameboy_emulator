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
	uint32_t _cycleCounter = 0;
public:
	CPU(MMU* mmu, CPURegister* reg, CPUFlags* flags) : _mmu(mmu), _reg(reg), _flags(flags) {}
	uint32_t GetCycleCounter();
	void SetCycleCounter(uint32_t cycleCounter);
	void RunInstruction(uint8_t opcode);
	void LdNnn(uint8_t opcode);
	void LdR1R2(uint8_t opcode);
	void LdAN(uint8_t opcode);
	void LdNA(uint8_t opcode);
	void LdAC();
	void LdCA();
	void LdHlnegA();
	void LdAHlpos();
	void LdHlposA();
	void LdAHlneg();
	void LdhNA(uint8_t opcode);
	void LdhAN(uint8_t opcode);
	void LdNNn16(uint8_t opcode);
	void LdSpHl(uint8_t opcode);
	void LdHlSpn(uint8_t opcode);
	void LdNnSp(uint8_t opcode);
	void PushNn(uint8_t opcode);
	void PopNn(uint8_t opcode);
	void AddAN(uint8_t opcode);
	void AdcAN(uint8_t opcode);
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
	void SrlN(uint8_t cb_opcode);
	void Bit0(uint8_t opcode);
	void Bit1(uint8_t cb_opcode);
	void Bit2(uint8_t cb_opcode);
	void Bit3(uint8_t cb_opcode);
	void Bit4(uint8_t cb_opcode);
	void Bit5(uint8_t cb_opcode);
	void Bit6(uint8_t cb_opcode);
	void Bit7(uint8_t cb_opcode);
	void Set0(uint8_t cb_opcode);
	void Set1(uint8_t cb_opcode);
	void Set2(uint8_t cb_opcode);
	void Set3(uint8_t cb_opcode);
	void Set4(uint8_t cb_opcode);
	void Set5(uint8_t cb_opcode);
	void Set6(uint8_t cb_opcode);
	void Set7(uint8_t cb_opcode);
	void JpNn();
	void JpCcNn(uint8_t opcode);
	void JpHl();
	void JrN();
	void JrCcN(uint8_t opcode);
	void CallNn();
	void Res0(uint8_t cb_opcode);
	void Res1(uint8_t cb_opcode);
	void Res2(uint8_t cb_opcode);
	void Res3(uint8_t cb_opcode);
	void Res4(uint8_t cb_opcode);
	void Res5(uint8_t cb_opcode);
	void Res6(uint8_t cb_opcode);
	void Res7(uint8_t cb_opcode);
	void CallCcNn(uint8_t opcode);
	void RstN(uint8_t opcode);
	void Ret();
	void RetCc(uint8_t opcode);
	void RetI();
	void DestroyCpu(CPU* cpu);
};



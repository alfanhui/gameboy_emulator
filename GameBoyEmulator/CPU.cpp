#include <bit>
#include <bitset>
#include <cmath>
#include <iostream>
#include "CPU.h"

uint32_t CPU::GetCycleCounter() {
	return _cycleCounter;
}

void CPU::SetCycleCounter(uint32_t cycleCounter) {
	_cycleCounter = cycleCounter;
}

uint16_t CPU::ByteSwap(uint16_t number) {
	uint8_t hibyte = (number & 0xff00) >> 8;
	uint8_t lobyte = (number & 0xff);
	return lobyte << 8 | hibyte;
}

// Number of Trailing Zeros
// https://stackoverflow.com/questions/45221914/number-of-trailing-zeroes
int CPU::ntz(unsigned x) {
	int n;

	if (x == 0) return(32);
	n = 1;
	if ((x & 0x0000FFFF) == 0) { n = n + 16; x = x >> 16; }
	if ((x & 0x000000FF) == 0) { n = n + 8; x = x >> 8; }
	if ((x & 0x0000000F) == 0) { n = n + 4; x = x >> 4; }
	if ((x & 0x00000003) == 0) { n = n + 2; x = x >> 2; }
	return n - (x & 1);
}

void CPU::RunInstruction(uint8_t opcode)
{
	switch (opcode) {
		case 0x06: case 0x0E: case 0x16: case 0x1E:	case 0x26: case 0x2E:
			LdNnn(opcode); 
			break;
		case 0x36: case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: 
		case 0x45: case 0x46: case 0x48: case 0x49: case 0x4A: case 0x4B:
		case 0x4C: case 0x4D: case 0x4E: case 0x50: case 0x51: case 0x52: 
		case 0x53: case 0x54: case 0x55: case 0x56: case 0x58: case 0x59: 
		case 0x5A: case 0x5B: case 0x5C: case 0x5D: case 0x5E: case 0x60: 
		case 0x61: case 0x62: case 0x63: case 0x64: case 0x65: case 0x66:
		case 0x6A: case 0x6B: case 0x6C: case 0x6E: case 0x70: case 0x71: 
		case 0x72: case 0x73: case 0x74: case 0x75: case 0x7F: case 0x78: 
		case 0x79: case 0x7A: case 0x7B: case 0x7C: case 0x7D: case 0x7E:
			LdR1R2(opcode);
			break;
		case 0x0A: case 0x1A: case 0xFA: case 0x3E:
			LdAN(opcode);
			break;
		case 0x47: case 0x4F: case 0x57: case 0x5F: case 0x67: case 0x6F:
		case 0x02: case 0x12: case 0x77: case 0xEA:
			std::cout << "LD n, A";
			LdNA(opcode);
			break;
		case 0xF2: 
			std::cout << "LD A, (0xFF00 + C)";
			LdAC();
			break;
		case 0xE2: 
			std::cout << "LD (0xFF00 + C), A";
			LdCA();
			break;
		case 0x3A: 
			std::cout << "LD A, (HL-)";
			LdAHlneg();
			break;
		case 0x32:
			std::cout << "LD (HL-), A";
			LdHlnegA();
			break;
		case 0x2A:
			std::cout << "LD A, (HL+)";
			LdAHlpos();
			break;
		case 0x22: 
			std::cout << "LD (HL+), A";
			LdHlposA();
			break;
		case 0xE0:
			std::cout << "LD A, (0xFF00 + n)";
			LdhNA(opcode);
			break;
		case 0xF0: 
			std::cout << "LD (0xFF00 + n), A";
			LdhAN(opcode);
			break;
		case 0x01: case 0x11: case 0x21: case 0x31:
			LdNNn16(opcode);
			break;
		case 0xF9:
			std::cout << "LD16 (SP + n), HL";
			LdSpHl(opcode);
			break;
		case 0xF8: 
			std::cout << "LD16 HL, (SP + n)";
			LdHlSpn(opcode);
			break;
		case 0x08: 
			std::cout << "LD16 (nn), SP";
			LdNnSp(opcode);
			break;
		case 0xF5: case 0xC5: case 0xD5: case 0xE5:
			std::cout << "PUSH16";
			PushNn(opcode);
			break;
		case 0xF1: case 0xC1: case 0xD1: case 0xE1:
			std::cout << "POP16";
			PopNn(opcode);
			break;
		case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: 
		case 0x86: case 0x87: case 0xC6:
			std::cout << "ADD16 A, n";
			AddAN(opcode);
			break;
		case 0x88: case 0x89: case 0x8A: case 0x8B: case 0x8C: case 0x8D:
		case 0x8E: case 0x8F: case 0xCE:
			std::cout << "ADC16 A, n";
			AdcAN(opcode);
			break;
		case 0x90: case 0x91: case 0x92: case 0x93: case 0x94: case 0x95:
		case 0x96: case 0x97: case 0xD6:
			std::cout << "SUB16 A, n";
			SubAN(opcode);
			break;
		case 0x98: case 0x99: case 0x9A: case 0x9B: case 0x9C: case 0x9D:
		case 0x9E: case 0x9F: case 0xDE:
			std::cout << "SBC16 A, n";
			SbcAN(opcode);
			break;
		case 0xA0: case 0xA1: case 0xA2: case 0xA3: case 0xA4: case 0xA5:
		case 0xA6: case 0xA7: case 0xE6:
			std::cout << "AND A, n";
			AndAN(opcode);
			break;
		case 0xB0: case 0xB1: case 0xB2: case 0xB3: case 0xB4: case 0xB5:
		case 0xB6: case 0xB7: case 0xF6:
			std::cout << "OR A, n";
			OrAN(opcode);
			break;
		case 0xA8: case 0xA9: case 0xAA: case 0xAB: case 0xAC: case 0xAD:
		case 0xAE: case 0xAF: case 0xEE:
			std::cout << "X0R A, n";
			XorAN(opcode);
			break;
		case 0xB8: case 0xB9: case 0xBA: case 0xBB: case 0xBC: case 0xBD:
		case 0xBE: case 0xBF: case 0xFE:
			std::cout << "CP n";
			CpaN(opcode);
			break;
		case 0x04: case 0x0C: case 0x14: case 0x1C: case 0x24: case 0x2C:
		case 0x34: case 0x3C:
			std::cout << "INC n";
			IncN(opcode);
			break;
		case 0x05: case 0x0D: case 0x15: case 0x1D: case 0x25: case 0x2D:
		case 0x35: case 0x3D:
			std::cout << "DEC n";
			DecN(opcode);
			break;
		case 0x09: case 0x19: case 0x29: case 0x39:
			AddHlN16(opcode);
			break;
		case 0xE8:
			std::cout << "ADD SP, n";
			AddSpN16(opcode);
			break;
		case 0x03: case 0x13: case 0x23: case 0x33:
			std::cout << "INC16 nn";
			IncNn16(opcode);
			break;
		case 0x0B: case 0x1B: case 0x2B: case 0x3B:
			std::cout << "DEC16 nn";
			DecNn16(opcode);
			break;
		case 0xCB:
			Cb(opcode);
			break;
		case 0x27:
			std::cout << "DAA";
			Daa();
			break;
		case 0x2F:
			std::cout << "CPL";
			Cpl();
			break;
		case 0x3F:
			std::cout << "CCF";
			Ccf();
			break;
		case 0x37:
			std::cout << "SCF";
			Scf();
			break;
		case 0x00:
			std::cout << "NOP";
			Nop();
			break;
		case 0x76:
			std::cout << "HALT";
			Halt();
			break;
		case 0x10:
			Ten();
			break;
		case 0xF3:
			std::cout << "DI";
			Di();
			break;
		case 0xFB:
			std::cout << "EI";
			Ei();
			break;
		case 0x07:
			std::cout << "RLC n";
			Rlca();
			break;
		case 0x17:
			std::cout << "RL A";
			Rla();
			break;
		case 0x0F:
			std::cout << "RRC n";
			Rrca();
			break;
		case 0x1F: 
			std::cout << "RR n";
			Rra();
			break;
		case 0xC3:
			std::cout << "JP nn";
			JpNn();
			break;
		case 0xC2: case 0xCA: case 0xD2: case 0xDA:
			std::cout << "JP cc, nn";
			JpCcNn(opcode);
			break;
		case 0xE9:
			std::cout << "JP (HL)";
			JpHl();
			break;
		case 0x18:
			std::cout << "JR n";
			JrN();
			break;
		case 0x20: case 0x28: case 0x30: case 0x38:
			JrCcN(opcode);
			break;
		case 0xCD:
			CallNn();
			_cycleCounter += 12; //Making it 24
			break;
		case 0xC4: case 0xCC: case 0xD4: case 0xDC:
			std::cout << "CALL cc, nn";
			CallCcNn(opcode);
			break;
		case 0xC7: case 0xD7: case 0xE7: case 0xF7: case 0xCF: case 0xDF:
		case 0xEF: case 0xFF:
			std::cout << "RST N";
			RstN(opcode);
			break;
		case 0xC9:
			std::cout << "RET";
			Ret();
			break;
		case 0xC0: case 0xC8: case 0xD0: case 0xD8:
			std::cout << "RET cc";
			RetCc(opcode);
			break;
		case 0xD9:
			std::cout << "RET I";
			RetI();
			break;
		default: 
			std::cout << "Instruction not mapped: " << std::hex << (int)opcode << std::endl;
	}
}

//Desc: Put value nn into n.
// Don't listen to the docs, put immediate value into Reg
// p65
void CPU::LdNnn(uint8_t opcode) {
	std::cout << "LD " << _reg->labels[((opcode + 2) / 8) - 1] << ", nn";

	uint8_t value = _mmu->ReadMemory8(_mmu, _reg->Read8(_reg, PC));
	_reg->Write8(_reg, (opcode - 0x06) >> 3, value); // Thanks ChatGPT
	_cycleCounter += 8;
	_reg->array[PC]++; 
}

//Put value r2 into r1.
void CPU::LdR1R2(uint8_t opcode) {
	if (opcode == 0x36) { //edge case [12 cycles]
		std::cout << "LD (HL), n";
		uint8_t value = _mmu->ReadMemory8(_mmu, _reg->Read8(_reg, PC));
		_mmu->WriteMemory8(_mmu, _reg->Read16(_reg, HL), value);
		_cycleCounter += 12;
		_reg->array[PC]++; // TODO_CHATGPT
		return;
	}
	float r = (opcode / 8.0f) - 8.0f;
	uint8_t r1_orig = (uint8_t)std::floor(r);
	uint8_t r2_orig = (uint8_t)((fmod(r, 8.0f) - (float)r1_orig) / 0.125f);
	uint8_t r1 = r1_orig;
	uint8_t r2 = r2_orig;
	if (r1_orig == 6) {
		r1 = H;
	}
	else if (r1_orig == 7) {
		r1 = A;
	}
	if (r2_orig == 6) {
		r2 = H;
	}
	else if (r2_orig == 7) {
		r2 = A;
	}
	std::cout << "LD " << _reg->labels[r1] << ", " << _reg->labels[r2];
	//8 cycles
	if (r1_orig == 6)
	{   //r1 is HL
		_mmu->WriteMemory8(_mmu, _reg->Read16(_reg, HL), _reg->Read8(_reg, r2));
		_cycleCounter += 8;
		return;
	}
	//8 cycles
	if (r2_orig == 6) {
		//r2 is HL
		_reg->Write8(_reg, r1, _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL))); 
		_cycleCounter += 8;
		return;
	}
	//4 cycles
	_reg->Write8(_reg, r1, _reg->array[r2]);
	_cycleCounter += 4;
}

//Put value n into A.
void CPU::LdAN(uint8_t opcode) {
	uint16_t addr;
	switch (opcode) {
		case 0x0A:
			std::cout << "LD A, (BC)";
			// 4 cycles
			_reg->Write8(_reg, A, _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, BC)));
			_cycleCounter += 4;
			break;
		case 0x1A:
			std::cout << "LD A, (DE)";
			// 4 cycles
			_reg->Write8(_reg, A, _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, DE)));
			_cycleCounter += 4;
			break;
		case 0xFA:
			std::cout << "LD A, nn";
			// 16 cycles
			addr = _mmu->ReadMemory16(_mmu, _reg->Read16(_reg, PC));
			//Last byte first
			_reg->Write8(_reg, A, _mmu->ReadMemory8(_mmu, ByteSwap(addr)));
			_cycleCounter += 16;
			_reg->array[PC]+=2;
			break;
		case 0x3E:
			std::cout << "LD A, (PC)";
			// 8 cycles
			_reg->Write8(_reg, A, _mmu->ReadMemory8(_mmu, _reg->Read8(_reg, PC)));
			_cycleCounter += 8;
			_reg->array[PC]++;
			break;
	}
}

//Put value A into n
void CPU::LdNA(uint8_t opcode) {
	uint16_t n = (((opcode + 1) / 8) - 9);
	switch (opcode) {
	case 0x02:
		//8 cycles
		n = _reg->Read16(_reg, BC);
		_cycleCounter += 8;
		break;
	case 0x12:
		//8 cycles 
		n = _reg->Read16(_reg, DE);
		_cycleCounter += 8;
		break;
	case 0x77:
		//8 cycles
		n = _reg->Read16(_reg, HL);
		_cycleCounter += 8;
		break;
	case 0xEA:
		//LS byte first
		//16 cycles
		n = _mmu->ReadMemory16(_mmu, _reg->Read16(_reg, PC));
		n = ByteSwap(n);
		_cycleCounter += 16;
		_reg->array[PC] +=2;
		break;
	}

	//4 cycles
	_mmu->WriteMemory8(_mmu, n, _reg->a);
	_cycleCounter += 4;
}

//Put value at address $FF00 + C into A. [8 cycles]
void CPU::LdAC() {
	_reg->Write8(_reg, A, _mmu->ReadMemory8(_mmu, 0xFF00 + _reg->c));
	_cycleCounter += 8;
}

//Put value A into $FF00 + C. [8 cycles]
void CPU::LdCA() {
	_mmu->WriteMemory8(_mmu, (0xFF00 + _reg->c), _reg->a);
	_cycleCounter += 8;
}

//Put value at address HL into A, then Decrement HL. [8 cycles]
void CPU::LdAHlneg() {
	_reg->Write8(_reg, A, _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL)));
	_reg->Write16(_reg, HL, _reg->Read16(_reg, HL) - 1);
	_cycleCounter += 8;
}

//Put A into address HL, then Decrement HL. [8 cycles]
void CPU::LdHlnegA() {
	_reg->Write16(_reg, _reg->Read16(_reg, HL), _reg->Read8(_reg, A));
	_reg->Write16(_reg, HL, _reg->Read16(_reg, HL) - 1);
	_cycleCounter += 8;
}

//Put value at address HL into A, then Increment HL. [8 cycles] 
void CPU::LdAHlpos() {
	_reg->Write8(_reg, A, _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL)));
	_reg->Write16(_reg, HL, _reg->Read16(_reg, HL) + 1);
	_cycleCounter += 8;
}

//Put A into memory address HL. Increment HL[8 cycles]
void CPU::LdHlposA() {
	_mmu->WriteMemory8(_mmu, _reg->Read16(_reg, HL), _reg->Read8(_reg, A));
	_reg->Write16(_reg, HL, _reg->Read16(_reg, HL) + 1);
	_cycleCounter += 8;
}

//Put value A into $FF00 + n. [12 cycles]
void CPU::LdhNA(uint8_t opcode) {
	uint8_t value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, PC));
	_mmu->WriteMemory8(_mmu, (0xFF00 + value), _reg->a);
	_cycleCounter += 12;
	_reg->array[PC]++; 
}

//Put memory address $FF00 + n into A. [12 cycles]
void CPU::LdhAN(uint8_t opcode) {
	uint8_t value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, PC));
	_reg->Write8(_reg, A, _mmu->ReadMemory8(_mmu, 0xFF00 + value));
	_cycleCounter += 12;
	_reg->array[PC]++; 
}

//Put 16byte value nn into n. 12 cycles
void CPU::LdNNn16(uint8_t opcode) {
	uint16_t value = _mmu->ReadMemory16(_mmu, _reg->Read16(_reg, PC));
	uint8_t n = opcode == 0x31 ? SP : ((opcode - 1) / 16) * 2; //SP is offset by A
	std::cout << "LD " << _reg->labels16[n] << "," << std::hex << value;
	_mmu->WriteMemory16(_mmu, _reg->Read16(_reg, n), value);
	_cycleCounter += 12;
	_reg->array[PC]+=2;
}

//Put HL into SP [8 cycles]
void CPU::LdSpHl(uint8_t opcode) {
	_reg->Write16(_reg, SP, _reg->Read16(_reg, HL));
	_cycleCounter += 8;
}

//LDHLSPn Put SP + n effective address into HL. [12 cycles]
void CPU::LdHlSpn(uint8_t opcode) {
	uint8_t value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, PC));
	_reg->Write16(_reg, HL, _mmu->ReadMemory16(_mmu, _reg->Read16(_reg, SP) + value));

	//Set flags
	_flags->SetZeroAtMask(FLAG_Z);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetFlag(FLAG_H, (_reg->Read16(_reg, SP) & 0x000F) + (value & 0x000F) > 0x000F);
	_flags->SetFlag(FLAG_C, (_reg->Read16(_reg, SP) & 0x00FF) + (value & 0x00FF) > 0x00FF);
	_cycleCounter += 12;
	_reg->array[PC]+=2; 
}

//Put Stack Pointer (SP) at address nn [20 cycles]
void CPU::LdNnSp(uint8_t opcode) {
	_mmu->WriteMemory16(_mmu, _reg->Read16(_reg, PC), _reg->Read16(_reg, SP));
	_cycleCounter += 20;
	_reg->array[PC]+=2; 
}

//Push register pair nn onto stack. Decrement Stack Pointer (SP) twice [16 cycles]
void CPU::PushNn(uint8_t opcode) {
	int8_t nn = ((int)std::floor(opcode / 8) - 24);
	if (nn == 0x00)
		std::cout << " (BC)";
	else if (nn == 0x02)
		std::cout << " (DE)";
	else if (nn == 0x04)
		std::cout << " (HL)";
	else if (nn == 0x06)
		std::cout << " (AF)";
	else
		std::cout << "ERROR! PANIC";
	_reg->Write16(_reg, SP, _reg->Read16(_reg, SP) - 2);
	_mmu->WriteMemory16(_mmu, _reg->Read16(_reg, SP), _reg->Read16(_reg, nn));
	_cycleCounter += 16;
}

//Pop two bytes off stack into register pair nn. Increment Stack Pointer (SP) twice. [12 cycles]
void CPU::PopNn(uint8_t opcode) {
	int8_t nn = ((int)std::floor(opcode / 8) - 24);
	if (nn == 0x00)
		std::cout << " (BC)";
	else if (nn == 0x02)
		std::cout << " (DE)";
	else if (nn == 0x04)
		std::cout << " (HL)";
	else if (nn == 0x06)
		std::cout << " (AF)";
	else
		std::cout << "ERROR! PANIC";
	uint16_t value = _mmu->ReadMemory16(_mmu, _reg->Read16(_reg, SP));
	_reg->Write16(_reg, SP, _reg->Read16(_reg, SP) + 2);
	_reg->Write16(_reg, nn, value);

	if (opcode == 0xF1) { //TODO CHECK
		// Set flags from the low byte of the popped value
		_flags->SetFlag(FLAG_Z, value & 0x80);
		_flags->SetFlag(FLAG_N, value & 0x40);
		_flags->SetFlag(FLAG_H, value & 0x20);
		_flags->SetFlag(FLAG_C, value & 0x10);
	}

	_cycleCounter += 12;
}

//Add n to A.
void CPU::AddAN(uint8_t opcode) {
	uint8_t n;
	if (opcode == 0x86) { //edge case [8 cycles]
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 8;
	}
	else if (opcode == 0xC6) { //edge case [8 cycles]
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, SP));
		_cycleCounter += 8;
		_reg->array[PC]++;
	}
	else if (opcode == 0x87) { //A,A, edge case [4 cycles]
		n = _reg->Read8(_reg, (opcode - 129));
		_cycleCounter += 4;
	}
	else {
		n = _reg->Read8(_reg, (opcode - 128)); //[4 cycles]
		_cycleCounter += 4;
	}
	uint8_t original_a = _reg->a;
	uint8_t new_value = n + _reg->a;
	_reg->Write8(_reg, A, new_value);

	//Set flags
	_flags->SetFlag(FLAG_Z, (new_value == 0x00));
	_flags->SetZeroAtMask(FLAG_N); //Not a subtraction method
	_flags->SetFlag(FLAG_H, ((original_a & 0xF) + (n & 0xF)) > 0xF);
	_flags->SetFlag(FLAG_C, new_value > 0xFF);
}

//Add n + carry flag to A.
void CPU::AdcAN(uint8_t opcode) {
	uint8_t n;
	if (opcode == 0x8E) { //edge case [8 cycles]
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 8;
	}
	else if (opcode == 0xCE) { //edge case [8 cycles]
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, SP));
		_cycleCounter += 8;
		_reg->array[PC]++;
	}
	else if (opcode == 0x8F) {
		n = _reg->Read8(_reg, (opcode - 137));
		_cycleCounter += 4;
	}
	else {
		n = _reg->Read8(_reg, (opcode - 136));
		_cycleCounter += 4;
	}
	uint8_t original_a = _reg->a;
	uint8_t new_value = n + _flags->GetFlag(FLAG_C) + _reg->a;
	_reg->Write8(_reg, A, (_reg->a + new_value));

	//Set flags
	_flags->SetFlag(FLAG_Z, (new_value == 0x00));
	_flags->SetZeroAtMask(FLAG_N); //Not a subtraction method
	_flags->SetFlag(FLAG_H, ((original_a & 0xF) + (n & 0xF) + (_flags->GetFlag(FLAG_C) & 0xF)) > 0xF);
	_flags->SetFlag(FLAG_C, (new_value) > 0xFF);
}

//Subtract n from A. 
void CPU::SubAN(uint8_t opcode){
	uint8_t n;
	if (opcode == 0x96) { //edge case [8 cycles]
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 8;
	}
	else if (opcode == 0xD6) { //edge case [8 cycles]
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, SP));
		_cycleCounter += 8;
		_reg->array[PC]++;
	}
	else {
		n = _reg->Read8(_reg, (opcode - 144)); //4 cycles
		_cycleCounter += 4;
	}
	int8_t original_a = (int8_t)(_reg->a);
	int8_t new_value = (int8_t)(_reg->a - n); //we need to check if goes beyond neg for flag wavin'
	_reg->Write8(_reg, A, (uint8_t)new_value);

	//Set flags
	_flags->SetFlag(FLAG_Z, (new_value == 0x00));
	_flags->SetOneAtMask(FLAG_N);
	_flags->SetFlag(FLAG_H, (original_a & 0x0F) < (n & 0x0F));
	_flags->SetFlag(FLAG_C, (original_a < n));
}

//Subtract n + carry flag from A. 
void CPU::SbcAN(uint8_t opcode) {
	uint8_t n;
	if (opcode == 0x9E) { //edge case [8 cycles]
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 8;
	}
	else if (opcode == 0xDE) {
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, SP));
		_cycleCounter += 8;
		_reg->array[PC]++;
	}
	else if (opcode == 0x9F){
		n = _reg->Read8(_reg, (opcode - 153)); //4 cycles
		_cycleCounter += 4;
	}
	else {
		n = _reg->Read8(_reg, (opcode - 152)); //4 cycles
		_cycleCounter += 4;
	}
	int8_t original_a = (int8_t)_reg->a;
	int8_t new_value = (int8_t)(_reg->a - (n + _flags->GetFlag(FLAG_C))); //we need to check if goes beyond neg for flag wavin'
	_reg->Write8(_reg, A, (uint8_t)new_value);

	//Set flags
	_flags->SetFlag(FLAG_Z, (new_value == 0x00));
	_flags->SetOneAtMask(FLAG_N);
	_flags->SetFlag(FLAG_H, (original_a & 0xF) < ((n & 0xF) + _flags->GetFlag(FLAG_C)));
	_flags->SetFlag(FLAG_C, original_a < (n + _flags->GetFlag(FLAG_C))); // MOHANSON uses 16bit integers here
}

//Logically AND n with A, result in A.
void CPU::AndAN(uint8_t opcode) {
	uint8_t n;
	if (opcode == 0xA6) { //edge case [8 cycles]
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 8;
	} 
	else if (opcode == 0xE6) { //edge case [8 cycles]
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, SP));
		_cycleCounter += 8;
		_reg->array[PC] ++;
	} 
	else if (opcode == 0xA7) { //A,A edge case [4 cycles]
		n = _reg->Read8(_reg, (opcode - 161));
		_cycleCounter += 4;
	}
	else {
		n = _reg->Read8(_reg, (opcode - 160)); //4 cycles
		_cycleCounter += 4;
	}
	uint8_t original_a = _reg->a;
	uint8_t new_value = (_reg->a & n);
	_reg->Write8(_reg, A, new_value);

	//Set flags
	_flags->SetFlag(FLAG_Z, new_value == 0x00);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetOneAtMask(FLAG_H);
	_flags->SetZeroAtMask(FLAG_C);
}

// Logical OR n with register A, result in A.
void CPU::OrAN(uint8_t opcode) {
	uint8_t n;
	if (opcode == 0xB6) { //edge case [8 cycles]
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 8;
	}
	else if (opcode == 0xF6) { //edge case [8 cycles]
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, SP));
		_cycleCounter += 8;
		_reg->array[PC] ++;
	}
	else if (opcode == 0xB7) { //A,A edge case [4 cycles]
		n = _reg->Read8(_reg, (opcode - 177));
		_cycleCounter += 4;
	}
	else {
		n = _reg->Read8(_reg, (opcode - 176)); //4 cycles
		_cycleCounter += 4;
	}
	uint8_t value = (_reg->a | n);
	_reg->Write8(_reg, A, value);

	//Set flags
	_flags->SetFlag(FLAG_Z, (value == 0x00));
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetZeroAtMask(FLAG_C);
}

//Logical exclusive OR n with register A, result in A.
//TODO test
void CPU::XorAN(uint8_t opcode) {
	uint8_t n;
	if (opcode == 0xAE) { //edge case [8 cycles]
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 8;
	}
	else if (opcode == 0xEE) { //edge case [8 cycles]
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, SP));
		_cycleCounter += 8;
		_reg->array[PC] ++;
	}
	else if (opcode == 0xAF) { //A,A edge case [4 cycles]
		n = _reg->Read8(_reg, (opcode - 169));
		_cycleCounter += 4;
	}
	else {
		n = _reg->Read8(_reg, (opcode - 168)); //4 cycles
		_cycleCounter += 4;
	}
	uint8_t value = (_reg->a ^ n);
	_reg->Write8(_reg, A, value);

	//Set flags
	_flags->SetFlag(FLAG_Z, value == 0x00);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetZeroAtMask(FLAG_C);
}

//Compare A with n. Basically A - n, but don't store results
// p87
void CPU::CpaN(uint8_t opcode) {
	uint8_t n;
	if (opcode == 0xBE) { //edge case [8 cycles]
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 8;
	}
	else if (opcode == 0xFE) { //edge case [8 cycles]
		n = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, SP));
		_cycleCounter += 8;
		_reg->array[PC] ++; 
	}
	else if (opcode == 0xBF) { //A,A edge case [4 cycles]
		n = _reg->Read8(_reg, (opcode - 185));
		_cycleCounter += 4;
	}
	else {
		n = _reg->Read8(_reg, (opcode - 184)); //4 cycles
		_cycleCounter += 4;
	}

	//Set flags
	_flags->SetFlag(FLAG_Z, n == 0x00);
	_flags->SetOneAtMask(FLAG_N);
	_flags->SetFlag(FLAG_H, (_reg->a & 0x0F) < (n & 0xF));
	_flags->SetFlag(FLAG_C, _reg->a < n);
}

//Increment register n
void CPU::IncN(uint8_t opcode) {
	uint8_t n = (opcode - 4) / 8;
	uint8_t value;

	if (opcode == 0x34) { // edge case [12 cycles]
		n = HL;
		value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, n));
		_cycleCounter += 12;
	}
	else if (opcode == 0x3C) { // edge case [4 cycles]
		n = A;
		value = _reg->Read8(_reg, n);
		_cycleCounter += 4;
	}
	else { // [4 cycles] 
		value = _reg->Read8(_reg, n);
		_cycleCounter += 4;
	}

	value++; //Increment value
	_reg->Write8(_reg, n, value);

	//Set flags
	_flags->SetFlag(FLAG_Z, (value == 0x00));
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetFlag(FLAG_H, ((value & 0x0f) + 0x01) > 0x0f);
	//FLAG_C not affected
}

//Decrement register n
void CPU::DecN(uint8_t opcode) {
	uint8_t n = (opcode - 5) / 8;
	uint8_t value;
	if (opcode == 0x35) { // edge case [12 cycles]
		n = HL;
		value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, n));
		_cycleCounter += 12;
	}
	else if (opcode == 0x3D) { // edge case [4 cycles]
		n = A;
		value = _reg->Read8(_reg, n); //duplicate below i know, but easy read
		_cycleCounter += 4;
	}
	else { // [4 cycles] 
		value = _reg->Read8(_reg, n);
		_cycleCounter += 4;
	}
	value--;
	_reg->Write8(_reg, n, value);
	//Set flags
	_flags->SetFlag(FLAG_Z, (value == 0x00));
	_flags->SetOneAtMask(FLAG_N);
	_flags->SetFlag(FLAG_H, (ntz(value) >= 4));
	//FLAG_C not affected
}


//Add n to HL [8 cycles]
void CPU::AddHlN16(uint8_t opcode) {
	uint16_t hl_value = _reg->Read16(_reg, HL);
	uint8_t n = opcode == 0x39 ? SP : (((opcode - 1) / 8) - 1); //SP is offset by A
	std::cout << "ADD (" << _reg->labels16[n] << ") to HL";
	uint16_t n_value = _reg->Read16(_reg, n);
	_reg->Write16(_reg, HL, hl_value + n_value);

	//Set flags
	//FLAG_Z not affected
	_flags->SetZeroAtMask(FLAG_N);
	
	//                0xF =         00001111
	// if hl_value is 0x16: 0000000000010110
	// bitwise AND &        0000000000000110 (only 1 if both bits are 1)
	_flags->SetFlag(FLAG_H, (hl_value & 0x0FFF) + (n_value & 0x0FFF) > 0x0FFF);

	// 0xFF =  11111111
	// 0000000000000110
	_flags->SetFlag(FLAG_C, (hl_value + n_value) > 0xFFFF);

	_cycleCounter += 8;
}

//Add n to Stack Pointer (only the first signed byte) [16 cycles]
// p91
void CPU::AddSpN16(uint8_t opcode) {
	int8_t n = (int8_t)_mmu->ReadMemory8(_mmu, _reg->Read16(_reg, PC));;
	uint16_t sp_value = _reg->Read16(_reg, SP);
	_reg->Write16(_reg, SP, sp_value + n);
	
	//Set Flags
	_flags->SetZeroAtMask(FLAG_Z);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetFlag(FLAG_H, (sp_value & 0x000F) + (n & 0x000F) > 0x000F);
	_flags->SetFlag(FLAG_C, (sp_value & 0x00FF) + (n & 0x00FF) > 0x00FF);
	_cycleCounter += 16;
	_reg->array[PC]++;
}

//Increment nn [8 cycles]
void CPU::IncNn16(uint8_t opcode) {
	uint8_t n = opcode == 0x33 ? SP : ((opcode - 3) / 8); //SP is offset by A
	uint16_t nn_value = _reg->Read16(_reg, n);
	_reg->Write16(_reg, n, nn_value + 1);
	//No flag changes
	_cycleCounter += 8;
}

//Decrement nn [8 cycles]
void CPU::DecNn16(uint8_t opcode) {
	uint8_t n = opcode == 0x3B ? SP : (((opcode - 3) / 8) - 1); //SP is offset by A
	uint16_t nn_value = _reg->Read16(_reg, n);
	_reg->Write16(_reg, n, nn_value - 1);
	//No flag changes
	_cycleCounter += 8;
}

//No cycles
void CPU::Cb(uint8_t opcode) {
	uint8_t cb_opcode = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, PC));
	_reg->array[PC]++;
	std::cout << std::hex << (int)cb_opcode << " ";
	switch (cb_opcode) {
		case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35:
		case 0x36: case 0x37:
			std::cout << "SWAP n";
			SwapN(cb_opcode);
			break;
		case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x05:
		case 0x06: case 0x07:
			std::cout << "RL c";
			RlcN(cb_opcode);
			break;
		case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15:
		case 0x16: case 0x17:
			std::cout << "RL n";
			RlN(cb_opcode);
			break;
		case 0x08: case 0x09: case 0x0A: case 0x0B: case 0x0C: case 0x0D:
		case 0x0E: case 0x0F:
			std::cout << "RR c";
			RrcN(cb_opcode);
			break;
		case 0x18: case 0x19: case 0x1A: case 0x1B: case 0x1C: case 0x1D:
		case 0x1E: case 0x1F:
			std::cout << "RR n";
			RrN(cb_opcode);
			break;
		case 0x20: case 0x21: case 0x22: case 0x23: case 0x24: case 0x25:
		case 0x26: case 0x27:
			std::cout << "SL a";
			SlaN(cb_opcode);
			break;
		case 0x28: case 0x29: case 0x2A: case 0x2B: case 0x2C: case 0x2D:
		case 0x2E: case 0x2F:
			std::cout << "SR n";
			SraN(cb_opcode);
			break;
		case 0x38: case 0x39: case 0x3A: case 0x3B: case 0x3C: case 0x3D:
		case 0x3E: case 0x3F:
			std::cout << "SRL n";
			SrlN(cb_opcode);
			break;
		case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45:
		case 0x46: case 0x47:
			std::cout << "BIT 0";
			Bit0(cb_opcode);
			break;
		case 0x48: case 0x49: case 0x4A: case 0x4B: case 0x4C: case 0x4D:
		case 0x4E: case 0x4F:
			std::cout << "BIT 1";
			Bit1(cb_opcode);
			break;
		case 0x50: case 0x51: case 0x52: case 0x53: case 0x54: case 0x55:
		case 0x56: case 0x57:
			std::cout << "BIT 2";
			Bit2(cb_opcode);
			break;
		case 0x58: case 0x59: case 0x5A: case 0x5B: case 0x5C: case 0x5D:
		case 0x5E: case 0x5F:
			std::cout << "BIT 3";
			Bit3(cb_opcode);
			break;
		case 0x60: case 0x61: case 0x62: case 0x63: case 0x64: case 0x65:
		case 0x66: case 0x67:
			std::cout << "BIT 4";
			Bit4(cb_opcode);
			break;
		case 0x68: case 0x69: case 0x6A: case 0x6B: case 0x6C: case 0x6D:
		case 0x6E: case 0x6F:
			std::cout << "BIT 5";
			Bit5(cb_opcode);
			break;
		case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75:
		case 0x76: case 0x77:
			std::cout << "BIT 6";
			Bit6(cb_opcode);
			break;
		case 0x78: case 0x79: case 0x7A: case 0x7B: case 0x7C: case 0x7D:
		case 0x7E: case 0x7F:
			std::cout << "BIT 7";
			Bit7(cb_opcode);
			break;
		case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85:
		case 0x86: case 0x87:
			std::cout << "RES 0";
			Res0(cb_opcode);
			break;
		case 0x88: case 0x89: case 0x8A: case 0x8B: case 0x8C: case 0x8D:
		case 0x8E: case 0x8F:
			std::cout << "RES 1";
			Res1(cb_opcode);
			break;
		case 0x90: case 0x91: case 0x92: case 0x93: case 0x94: case 0x95:
		case 0x96: case 0x97:
			std::cout << "RES 2";
			Res2(cb_opcode);
			break;
		case 0x98: case 0x99: case 0x9A: case 0x9B: case 0x9C: case 0x9D:
		case 0x9E: case 0x9F:
			std::cout << "RES 3";
			Res3(cb_opcode);
			break;
		case 0xA0: case 0xA1: case 0xA2: case 0xA3: case 0xA4: case 0xA5:
		case 0xA6: case 0xA7:
			std::cout << "RES 4";
			Res4(cb_opcode);
			break;
		case 0xA8: case 0xA9: case 0xAA: case 0xAB: case 0xAC: case 0xAD:
		case 0xAE: case 0xAF:
			std::cout << "RES 5";
			Res5(cb_opcode);
			break;
		case 0xB0: case 0xB1: case 0xB2: case 0xB3: case 0xB4: case 0xB5:
		case 0xB6: case 0xB7:
			std::cout << "RES 6";
			Res6(cb_opcode);
			break;
		case 0xB8: case 0xB9: case 0xBA: case 0xBB: case 0xBC: case 0xBD:
		case 0xBE: case 0xBF:
			std::cout << "RES 7";
			Res7(cb_opcode);
			break;
		case 0xC0: case 0xC1: case 0xC2: case 0xC3: case 0xC4: case 0xC5:
		case 0xC6: case 0xC7:
			std::cout << "SET 0";
			Set0(cb_opcode);
			break;
		case 0xC8: case 0xC9: case 0xCA: case 0xCB: case 0xCC: case 0xCD:
		case 0xCE: case 0xCF:
			std::cout << "SET 1";
			Set1(cb_opcode);
			break;
		case 0xD0: case 0xD1: case 0xD2: case 0xD3: case 0xD4: case 0xD5:
		case 0xD6: case 0xD7:
			std::cout << "SET 2";
			Set2(cb_opcode);
			break;
		case 0xD8: case 0xD9: case 0xDA: case 0xDB: case 0xDC: case 0xDD:
		case 0xDE: case 0xDF:
			std::cout << "SET 3";
			Set3(cb_opcode);
			break;
		case 0xE0: case 0xE1: case 0xE2: case 0xE3: case 0xE4: case 0xE5:
		case 0xE6: case 0xE7:
			std::cout << "SET 4";
			Set4(cb_opcode);
			break;
		case 0xE8: case 0xE9: case 0xEA: case 0xEB: case 0xEC: case 0xED:
		case 0xEE: case 0xEF:
			std::cout << "SET 5";
			Set5(cb_opcode);
			break;
		case 0xF0: case 0xF1: case 0xF2: case 0xF3: case 0xF4: case 0xF5:
		case 0xF6: case 0xF7:
			std::cout << "SET 6";
			Set6(cb_opcode);
			break;
		case 0xF8: case 0xF9: case 0xFA: case 0xFB: case 0xFC: case 0xFD:
		case 0xFE: case 0xFF:
			std::cout << "SET 7";
			Set7(cb_opcode);
			break;
		default:
			std::cout << "CB type instruction not mapped: " << std::hex << cb_opcode << std::endl;
	}
}


//Swap upper & lower nibles of n.
void CPU::SwapN(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0x36) {
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read8(_reg, HL));
	}
	else if (cb_opcode == 0x37) {
		n_value = _reg->Read8(_reg, A);
	}
	else {
		n_value = _reg->Read8(_reg, cb_opcode - 30);
	}
	uint8_t result = ((n_value & 0xF) && 15) || (((n_value & 15) & 0xF) >> 4); //Do the switcharoo
	//uint8_t result = ((n_value & 0xF) << 4) | ((n_value & 0xF0) >> 4); // TODO_CHATGPT
	if (cb_opcode == 0x36) { //(HL) edge case [16 cycles]
		_mmu->WriteMemory8(_mmu, _reg->Read8(_reg, HL), result);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x37) { //A edge case [8 cycles]
		_reg->Write8(_reg, A, result);
		_cycleCounter += 8;
	}
	else { // [8 cycles]
		_reg->Write8(_reg, cb_opcode - 30, result);
		_cycleCounter += 8;
	}
	//Set flags
	_flags->SetFlag(FLAG_Z, (result == 0x00));
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetZeroAtMask(FLAG_C);
}

// Decimal adjust register A
// Mixed documentation on this function. Subtraction condition added thanks to CrociDB [4 cycles]
void CPU::Daa() {
	uint8_t a_value = _reg->a;
	if (_flags->GetFlag(FLAG_N) == 0x01) {
		if (_flags->GetFlag(FLAG_H) == 0x01) {
			a_value -= 0x06;
		}
		if (_flags->GetFlag(FLAG_C) == 0x01) {
			a_value -= 0x60;
		}
	}
	else {
		//if the least significant four bits of A contain a non - BCD digit(i.e.it is greater than 9) or the H flag is set,
		if ((_reg->a && 15) > 9 || _flags->GetFlag(FLAG_H) == 0x01) {
			//then $06 is added to the register.
			a_value += 0x06;
		}
		//Then the four most significant bits are checked.
		//If this more significant digit also happens to be greater than 9 or the C flag is set, 
		if ((_reg->a >> 4) > 9 || _flags->GetFlag(FLAG_C) == 0x01) {
			//then $60 is added.
			a_value += 0x60;
		}
	}
	_reg->Write8(_reg, A, a_value);

	//Set flags
	_flags->SetFlag(FLAG_Z, (a_value == 0x00));
	//FLAG_N Not affect
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetFlag(FLAG_C, (a_value > 0xFF));
	_cycleCounter += 4;
}

//Complement A register. (Flip all bits.) [4 cycles]
void CPU::Cpl() {
	_reg->Write8(_reg, A, ~(_reg->a));
	//Set flags
	//FLAG_Z Not affected
	_flags->SetOneAtMask(FLAG_N);
	_flags->SetOneAtMask(FLAG_H);
	//FLAG_C Not affected
	_cycleCounter += 4;
}

//Complement FLAG_C [4 cycles]
void CPU::Ccf() {
	//Set flags
	//FLAG_Z Not affected
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetBitFlipAtMask(FLAG_C);
	_cycleCounter += 4;
}

//Set Carry flag. [4 cycles]
void CPU::Scf() {
	//Set flags
	//FLAG_Z Not affected
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetOneAtMask(FLAG_C);
	_cycleCounter += 4;
}

//No operation [4 cycles]
void CPU::Nop() {
	_cycleCounter += 4;
}

//Power down CPU until an interrupt occurs. [4 cycles]
void CPU::Halt() {
	_halt = true;
	Nop(); //As per manual suggestions
	//TODO wait until interupt occurs.
	_cycleCounter += 4;
}

//Only used for STOP instruction, no cycles
void CPU::Ten() {
	uint8_t ten_opcode = _reg->pc_first;
	switch (ten_opcode) {
	case 0x00:
		Stop();
		break;
	default:
		std::cout << "TEN type instruction not mapped: " << std::hex << ten_opcode << std::endl;
	}
}

//Halt CPU & LCD display until button pressed. [4 cycles]
void CPU::Stop() {
	_halt = true;
	//TODO HALT LCD display
	//TODO WAIT UNTIL BUTTON PRESS
	_cycleCounter += 4;
}

//disables interrupts (ime) [4 cycles]
void CPU::Di() {
	_ime = false;
	_cycleCounter += 4;
}

//enables interrupts (ime) [4 cycles]
void CPU::Ei() {
	_ime = true;
	_cycleCounter += 4;
}

//Rotate A left, old bit 7 in carry flag [4 cycles]
void CPU::Rlca() {

	uint8_t carry = (_reg->a > 7);
	uint8_t result = (_reg->a << 1) | carry;

	_reg->Write8(_reg, A, result);

	//Set remaining flags
	_flags->SetFlag(FLAG_Z, result == 0x00);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetFlag(FLAG_C, carry);
	_cycleCounter += 4;
}

//Rotate A left through Carry flag. [4 cycles]
void CPU::Rla() {
	
	uint8_t result = (_reg->a << 1) + _flags->GetFlag(FLAG_C);

	_reg->Write8(_reg, A, result);
	
	//Set remaining flags
	_flags->SetFlag(FLAG_Z, result == 0x00);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetFlag(FLAG_C, _reg->a > 7);
	_cycleCounter += 4;
	// TODO MONHANDSON sets flag Z to 0 after this function, but instructions says conditional?
}

//Rotate A right, old bit 0 in carry flag [4 cycles]
// p100
void CPU::Rrca() {

	uint8_t carry = (_reg->a & 1);
	uint8_t result = carry ? (0x80 | _reg->a >> 1) : (_reg->a >> 1);

	_reg->Write8(_reg, A, result);

	//Set remaining flags
	_flags->SetFlag(FLAG_Z, result == 0x00);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetFlag(FLAG_C, carry);
	_cycleCounter += 4;
	// TODO MONHANDSON sets flag Z to 0 after this function, but instructions says conditional?
}

//Rotate A right through carry flag [4 cycles]
void CPU::Rra() {
	uint8_t carry = (_reg->a & 1);
	uint8_t result = _flags->GetFlag(FLAG_C) ? (0x80 | _reg->a >> 1) : (_reg->a >> 7);

	_reg->Write8(_reg, A, result);

	//Set remaining flags
	_flags->SetFlag(FLAG_Z, result == 0x00);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetFlag(FLAG_C, carry);
	_cycleCounter += 4;
	// TODO MONHANDSON sets flag Z to 0 after this function, but instructions says conditional?
}

//Rotate n left. Old bit 7 to Carry flag.
void CPU::RlcN(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0x06) {
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
	}
	else if (cb_opcode == 0x07) {
		n_value = _reg->Read8(_reg, A);
	}
	else {
		n_value = _reg->Read8(_reg, cb_opcode);
	}

	uint8_t carry = (n_value & 0x80) >> 7;
	uint8_t result = (n_value << 1) | carry;

	if (cb_opcode == 0x06) { // [16 cycles]
		_mmu->WriteMemory8(_mmu, _reg->Read16(_reg, HL), result);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x07) { // [8 cycles]
		_reg->Write8(_reg, A, result);
		_cycleCounter += 8;
	}
	else { // [8 cycles]
		_reg->Write8(_reg, cb_opcode, result);
		_cycleCounter += 8;
	}
	
	//Set remaining flags
	_flags->SetFlag(FLAG_Z, (result == 0x00));
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetFlag(FLAG_C, carry); // Use old bit 7 as carry
}

//Rotate n left through Carry flag.
void CPU::RlN(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0x16) {
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
	}
	else if (cb_opcode == 0x17) {
		n_value = _reg->Read8(_reg, A);
	}
	else {
		n_value = _reg->Read8(_reg, cb_opcode - 10);
	}
	
	uint8_t carry = _flags->GetFlag(FLAG_C);
	uint8_t result = (n_value << 1) + carry;

	if (cb_opcode == 0x16) { // [16 cycles]
		_mmu->WriteMemory8(_mmu, _reg->Read16(_reg, HL), result);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x17) { // [8 cycles]
		_reg->Write8(_reg, A, result);
		_cycleCounter += 8;
	}
	else { // [8 cycles]
		_reg->Write8(_reg, cb_opcode - 10, result);
		_cycleCounter += 8;
	}

	//Set remaining flags
	_flags->SetFlag(FLAG_Z, (result == 0x00));
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetFlag(FLAG_C, (n_value & 0x80) >> 7); //Don't use old carry flag
}

//Rotate n right. Old bit 7 to Carry flag.
void CPU::RrcN(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0x0E) {
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
	}
	else if (cb_opcode == 0x0F) {
		n_value = _reg->Read8(_reg, A);
	}
	else {
		n_value = _reg->Read8(_reg, cb_opcode - 8);
	}
	
	uint8_t carry = (n_value & 1);
	uint8_t result = carry ? (0x80 | n_value >> 1) : (n_value >> 1);
	if (cb_opcode == 0x0E) { // [16 cycles]
		_mmu->WriteMemory8(_mmu, _reg->Read16(_reg, HL), result);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x0F) { // [8 cycles]
		_reg->Write8(_reg, A, result);
		_cycleCounter += 8;
	}
	else { // [8 cycles]
		_reg->Write8(_reg, cb_opcode - 8, result);
		_cycleCounter += 8;
	}

	//Set remaining flags
	_flags->SetFlag(FLAG_Z, (result == 0x00));
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetFlag(FLAG_C, carry); // This is the old bit
}

//Rotate n right. Old bit 7 to Carry flag.
void CPU::RrN(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0x1E) {
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
	}
	else if (cb_opcode == 0x1F) {
		n_value = _reg->Read8(_reg, A);
	}
	else {
		n_value = _reg->Read8(_reg, cb_opcode - 18);
	}

	uint8_t result = _flags->GetFlag(FLAG_C) ? ( 0x80 | (n_value >> 1)) : (n_value >> 1);
	if (cb_opcode == 0x1E) { // [16 cycles]
		_mmu->WriteMemory8(_mmu, _reg->Read16(_reg, HL), result);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x1F) { // [8 cycles]
		_reg->Write8(_reg, A, result);
		_cycleCounter += 8;
	}
	else { // [8 cycles]
		_reg->Write8(_reg, cb_opcode - 18, result);
		_cycleCounter += 8;
	}

	//Set remaining flags
	_flags->SetFlag(FLAG_Z, (result == 0x00));
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetFlag(FLAG_C, (n_value & 0x01)); // Carry old result
}

//Shift n left into Carry. LSB of n set to 0.
void CPU::SlaN(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0x26) { //(hl)
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg,HL));
	}
	else if (cb_opcode == 0x27) { //A
		n_value = _reg->Read8(_reg, A);
	}
	else {
		n_value = _reg->Read8(_reg, cb_opcode - 20);
	}

	uint8_t result = (n_value << 1);
	if (cb_opcode == 0x26) { //(hl) [16 cycles]
		_mmu->WriteMemory8(_mmu, _reg->Read16(_reg, HL), result);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x27) { //A [8 cycles]
		_reg->Write8(_reg, A, result);
		_cycleCounter += 8;
	}
	else { //[8 cycles]
		_reg->Write8(_reg, cb_opcode - 20, result);
		_cycleCounter += 8;
	}
	
	//Set remaining flags
	_flags->SetFlag(FLAG_Z, (result == 0x00));
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetFlag(FLAG_C, (n_value & 0x80) >> 7);
}

//Shift n right into Carry. MSB doesn't change.
void CPU::SraN(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0x2E) { //(hl)
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
	}
	else if (cb_opcode == 0x2F) { //A
		n_value = _reg->Read8(_reg, A);
	}
	else {
		n_value = _reg->Read8(_reg, cb_opcode - 28);
	}

	uint8_t result = (n_value >> 1) | (n_value & 0x80);
	if (cb_opcode == 0x2E) { //(hl) [16 cycles]
		_mmu->WriteMemory8(_mmu, _reg->Read16(_reg, HL), result);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x2F) { //A [8 cycles]
		_reg->Write8(_reg, A, result);
		_cycleCounter += 8;
	}
	else { //[8 cycles]
		_reg->Write8(_reg, cb_opcode - 28, result);
		_cycleCounter += 8;
	}

	//Set remaining flags
	_flags->SetFlag(FLAG_Z, (result == 0x00));
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetFlag(FLAG_C, (n_value & 0x01));
}

//Shift n right into Carry. MSB set to 0
void CPU::SrlN(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0x3E) { //(hl)
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
	}
	else if (cb_opcode == 0x3F) { //A
		n_value = _reg->Read8(_reg, A);
	}
	else {
		n_value = _reg->Read8(_reg, cb_opcode - 38);
	}

	uint8_t result = n_value >> 1;
	if (cb_opcode == 0x3E) { //(hl) [16 cycles]
		_mmu->WriteMemory8(_mmu, _reg->Read16(_reg, HL), result);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x3F) { //A [8 cycles]
		_reg->Write8(_reg, A, result);
		_cycleCounter += 8;
	}
	else { //[8 cycles]
		_reg->Write8(_reg, cb_opcode - 38, result);
		_cycleCounter += 8;
	}

	//Set remaining flags
	_flags->SetFlag(FLAG_Z, (result == 0x00));
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetZeroAtMask(FLAG_H);
	_flags->SetFlag(FLAG_C, (n_value & 0x01));
}

//Test bit at position 0
void CPU::Bit0(uint8_t cb_opcode) {
	int test;
	if (cb_opcode == 0x46) { //HL [16 cycles]
		test = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x47) { //A [8 cycles] 
		test = _reg->Read8(_reg, A);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		test = _reg->Read8(_reg, cb_opcode - 64);
		_cycleCounter += 8;
	}

	//Set flags
	_flags->SetFlag(FLAG_Z, (test & 1) == 0x00);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetOneAtMask(FLAG_H);
	//Flag_C not affected
}

//Test bit at position 1
void CPU::Bit1(uint8_t cb_opcode) {
	int test;
	if (cb_opcode == 0x4E) { //HL [ 16 cycles]
		test = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x4F) { //A [8 cycles] 
		test = _reg->Read8(_reg, A);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		test = _reg->Read8(_reg, cb_opcode - 72);
		_cycleCounter += 8;
	}
	//Set flags
	_flags->SetFlag(FLAG_Z, (test & 2) == 0x00);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetOneAtMask(FLAG_H);
	//Flag_C not affected
}

//Test bit at position 2
void CPU::Bit2(uint8_t cb_opcode) {
	int test;
	if (cb_opcode == 0x56) { //HL [ 16 cycles]
		test = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x57) { //A [8 cycles] 
		test = _reg->Read8(_reg, A);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		test = _reg->Read8(_reg, cb_opcode - 80);
		_cycleCounter += 8;
	}
	//Set flags
	_flags->SetFlag(FLAG_Z, (test & 4) == 0x00);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetOneAtMask(FLAG_H);
	//Flag_C not affected
}

//Test bit at position 3
void CPU::Bit3(uint8_t cb_opcode) {
	int test;
	if (cb_opcode == 0x5E) { //HL [ 16 cycles]
		test = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x5F) { //A [8 cycles] 
		test = _reg->Read8(_reg, A);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		test = _reg->Read8(_reg, cb_opcode - 88);
		_cycleCounter += 8;
	}
	//Set flags
	_flags->SetFlag(FLAG_Z, (test & 8) == 0x00);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetOneAtMask(FLAG_H);
	//Flag_C not affected
}

//Test bit at position 4
void CPU::Bit4(uint8_t cb_opcode) {
	int test;
	if (cb_opcode == 0x66) { //HL [ 16 cycles]
		test = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x67) { //A [8 cycles] 
		test = _reg->Read8(_reg, A);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		test = _reg->Read8(_reg, cb_opcode - 96);
		_cycleCounter += 8;
	}

	//Set flags
	_flags->SetFlag(FLAG_Z, (test & 16) == 0x00);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetOneAtMask(FLAG_H);
	//Flag_C not affected
}

//Test bit at position 5
void CPU::Bit5(uint8_t cb_opcode) {
	int test;
	if (cb_opcode == 0x6E) { //HL [ 16 cycles]
		test = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x6F) { //A [8 cycles] 
		test = _reg->Read8(_reg, A);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		test = _reg->Read8(_reg, cb_opcode - 104);
		_cycleCounter += 8;
	}

	//Set flags
	_flags->SetFlag(FLAG_Z, (test & 32) == 0x00);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetOneAtMask(FLAG_H);
	//Flag_C not affected
}

//Test bit at position 6
void CPU::Bit6(uint8_t cb_opcode) {
	int test;
	if (cb_opcode == 0x76) { //HL [ 16 cycles]
		test = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x77) { //A [8 cycles] 
		test = _reg->Read8(_reg, A);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		test = _reg->Read8(_reg, cb_opcode - 112);
		_cycleCounter += 8;
	}

	//Set flags
	_flags->SetFlag(FLAG_Z, (test & 64) == 0x00);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetOneAtMask(FLAG_H);
	//Flag_C not affected
}

//Test bit at position 7
void CPU::Bit7(uint8_t cb_opcode) {
	int test;
	if (cb_opcode == 0x7E) { //HL [ 16 cycles]
		test = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x7F) { //A [8 cycles] 
		test = _reg->Read8(_reg, A);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		test = _reg->Read8(_reg, cb_opcode - 124);
		_cycleCounter += 8;
	}

	//Set flags
	_flags->SetFlag(FLAG_Z, (test & 128) == 0x00);
	_flags->SetZeroAtMask(FLAG_N);
	_flags->SetOneAtMask(FLAG_H);
	//Flag_C not affected
}


//Set bit at position 0
void CPU::Set0(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0xC6) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 0)) | (1 << 0);
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0xC7) { //A [8 cycles] 
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 0)) | (1 << 0);
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 192));
		n_value = (n_value & ~(1 << 0)) | (1 << 0);
		_reg->Write8(_reg, (cb_opcode - 192), n_value);
		_cycleCounter += 8;
	}
}

//Set bit at position 1
void CPU::Set1(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0xCE) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 1)) | (1 << 1);
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0xCF) { //A [8 cycles] 
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 1)) | (1 << 1);
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 200));
		n_value = (n_value & ~(1 << 1)) | (1 << 1);
		_reg->Write8(_reg, (cb_opcode - 200), n_value);
		_cycleCounter += 8;
	}
}

//Set bit at position 2
void CPU::Set2(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0xD6) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 2)) | (1 << 2);
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0xD7) { //A [8 cycles] 
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 2)) | (1 << 2);
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 208));
		n_value = (n_value & ~(1 << 2)) | (1 << 2);
		_reg->Write8(_reg, (cb_opcode - 208), n_value);
		_cycleCounter += 8;
	}
}

//Set bit at position 3
void CPU::Set3(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0xDE) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 3)) | (1 << 3);
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0xDF) { //A [8 cycles] 
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 3)) | (1 << 3);
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 210));
		n_value = (n_value & ~(1 << 3)) | (1 << 3);
		_reg->Write8(_reg, (cb_opcode - 210), n_value);
		_cycleCounter += 8;
	}
}

//Set bit at position 4
void CPU::Set4(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0xE6) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 4)) | (1 << 4);
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0xE8) { //A [8 cycles] 
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 4)) | (1 << 4);
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 218));
		n_value = (n_value & ~(1 << 4)) | (1 << 4);
		_reg->Write8(_reg, (cb_opcode - 218), n_value);
		_cycleCounter += 8;
	}
}

//Set bit at position 5
void CPU::Set5(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0xEE) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 5)) | (1 << 5);
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0xEF) { //A [8 cycles] 
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 5)) | (1 << 5);
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 220));
		n_value = (n_value & ~(1 << 5)) | (1 << 5);
		_reg->Write8(_reg, (cb_opcode - 220), n_value);
		_cycleCounter += 8;
	}
}

//Set bit at position 6
void CPU::Set6(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0xF6) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 6)) | (1 << 6);
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0xF7) { //A [8 cycles] 
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 6)) | (1 << 6);
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 228));
		n_value = (n_value & ~(1 << 6)) | (1 << 6);
		_reg->Write8(_reg, (cb_opcode - 228), n_value);
		_cycleCounter += 8;
	}
}

//Set bit at position 7
void CPU::Set7(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0xFE) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 7)) | (1 << 7);
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0xFF) { //A [8 cycles]  //Thanks ChatGPT!
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 7)) | (1 << 7);
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 230));
		n_value = (n_value & ~(1 << 7)) | (1 << 7);
		_reg->Write8(_reg, (cb_opcode - 230), n_value);
		_cycleCounter += 8;
	}
}

//Reset bit at position 0
void CPU::Res0(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0x86) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 0));
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x87) { //A [8 cycles] 
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 0));
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 128));
		n_value = (n_value & ~(1 << 0));
		_reg->Write8(_reg, (cb_opcode - 128), n_value);
		_cycleCounter += 8;
	}
}

//Reset bit at position 1
void CPU::Res1(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0x8E) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 1));
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x8F) { //A [8 cycles] 
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 1));
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 136));
		n_value = (n_value & ~(1 << 1));
		_reg->Write8(_reg, (cb_opcode - 136), n_value);
		_cycleCounter += 8;
	}
}

//Reset bit at position 2
void CPU::Res2(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0x96) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 2));
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x97) { //A [8 cycles] 
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 2));
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 144));
		n_value = (n_value & ~(1 << 2));
		_reg->Write8(_reg, (cb_opcode - 144), n_value);
		_cycleCounter += 8;
	}
}

//Reset bit at position 3
void CPU::Res3(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0x9E) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 3));
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0x9F) { //A [8 cycles] 
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 3));
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 152));
		n_value = (n_value & ~(1 << 3));
		_reg->Write8(_reg, (cb_opcode - 152), n_value);
		_cycleCounter += 8;
	}
}

//Reset bit at position 4
void CPU::Res4(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0xA6) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 4));
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0xA8) { //A [8 cycles] 
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 4));
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 160));
		n_value = (n_value & ~(1 << 4));
		_reg->Write8(_reg, (cb_opcode - 160), n_value);
		_cycleCounter += 8;
	}
}

//Reset bit at position 5
void CPU::Res5(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0xAE) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 5));
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0xAF) { //A [8 cycles] 
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 5));
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 168));
		n_value = (n_value & ~(1 << 5));
		_reg->Write8(_reg, (cb_opcode - 168), n_value);
		_cycleCounter += 8;
	}
}

//Reset bit at position 6
void CPU::Res6(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0xB6) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 6));
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0xB7) { //A [8 cycles] 
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 6));
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 176));
		n_value = (n_value & ~(1 << 6));
		_reg->Write8(_reg, (cb_opcode - 176), n_value);
		_cycleCounter += 8;
	}
}

//Reset bit at position 7
void CPU::Res7(uint8_t cb_opcode) {
	uint8_t n_value;
	if (cb_opcode == 0xBE) { //HL [ 16 cycles]
		n_value = _mmu->ReadMemory8(_mmu, _reg->Read16(_reg, HL));
		n_value = (n_value & ~(1 << 7)) | (0 << 7);
		_mmu->WriteMemory8(_mmu, HL, n_value);
		_cycleCounter += 16;
	}
	else if (cb_opcode == 0xBF) { //A [8 cycles] //Thanks ChatCPT!
		n_value = _reg->Read8(_reg, A);
		n_value = (n_value & ~(1 << 7));
		_reg->Write8(_reg, A, n_value);
		_cycleCounter += 8;
	}
	else {// [8 cycles]
		n_value = _reg->Read8(_reg, (cb_opcode - 184));
		n_value = (n_value & ~(1 << 7)) | (0 << 7);
		_reg->Write8(_reg, (cb_opcode - 184), n_value);
		_cycleCounter += 8;
	}
}

//Jump to address nn [12 cycles]
void CPU::JpNn() {
	std::cout << "jumping..";
	uint16_t addr = _mmu->ReadMemory16(_mmu, _reg->Read16(_reg, PC));
	_reg->Write16(_reg, PC, addr);
	_cycleCounter += 12;
	_reg->array[PC]+=2;
}

//Jump to address n if following condition is true: [12 cycles, maybe already recorded by JpNn]
void CPU::JpCcNn(uint8_t opcode) {
	switch (opcode) {
	case 0xC2:
		if (_flags->GetFlag(FLAG_Z) == 0x00) {
			return JpNn();
		}
		break;
	case 0xCA:
		if (_flags->GetFlag(FLAG_Z) == 0x01) {
			return JpNn();
		}
		break;
	case 0xD2:
		if (_flags->GetFlag(FLAG_C) == 0x00) { 
			return JpNn();
		}
		break;
	case 0xDA:
		if (_flags->GetFlag(FLAG_C) == 0x01) {
			return JpNn();
		}
		break;
	}
	// If it doesn't jump, we need to step over the jump addresses.
	_cycleCounter += 12;
	_reg->array[PC] += 2;
}

//Jump to address contained in HL [4 cycles]
void CPU::JpHl() {
	std::cout << "jumping..";
	uint16_t addr = _mmu->ReadMemory16(_mmu, _reg->Read16(_reg, HL));
	_reg->Write16(_reg, PC, addr);
	_cycleCounter += 4;
}

//Add n to current address and jump to it [8 cycles]
void CPU::JrN() {
	std::cout << "jumping..";
	uint16_t addr = _reg->Read16(_reg, PC) + (int8_t)_mmu->ReadMemory8(_mmu, _reg->Read16(_reg, PC)) + 0x01;
	_reg->Write16(_reg, PC, addr);
	_cycleCounter += 8;
}

//if following condition is true then add n to current  address and jump to it
// P
void CPU::JrCcN(uint8_t opcode) {
	uint16_t addr_debug = _reg->Read16(_reg, PC) + (int8_t)_mmu->ReadMemory8(_mmu, _reg->Read16(_reg, PC)) + 0x01;
	switch (opcode) {
	case 0x20:
		std::cout << "JR NZ" << ", Addr_" << std::hex << addr_debug << " (Z=" << (bool)_flags->GetFlag(FLAG_Z) << ") ";
		if (_flags->GetFlag(FLAG_Z) == 0x00) {
			return JrN();
		}
		break;
	case 0x28:
		std::cout << "JR Z" << ", Addr_" << addr_debug << " (Z=" << (bool)_flags->GetFlag(FLAG_Z) << ") ";
		if (_flags->GetFlag(FLAG_Z) == 0x01) {
			return JrN();
		}
		break;
	case 0x30:
		std::cout << "JR NC" << ", Addr_" << addr_debug << " (C=" << (bool)_flags->GetFlag(FLAG_C) << ") ";
		if (_flags->GetFlag(FLAG_C) == 0x00) {
			return JrN();
		}
		break;
	case 0x38:
		std::cout << "JR C" << ", Addr_" << addr_debug << " (C=" << (bool)_flags->GetFlag(FLAG_C) << ") ";
		if (_flags->GetFlag(FLAG_C) == 0x01) {
			return JrN();
		}
		break;
	}
	_cycleCounter += 8; //TODO Is this really 8, if it didn't do any operation?
	_reg->array[PC]++;
}

//Push address of next instruction onto stack and then jump to address nn. [12 cycles]
void CPU::CallNn() {
	uint16_t addr = _mmu->ReadMemory16(_mmu, _reg->Read16(_reg, PC));
	_reg->array[PC] += 2;
	std::cout << "CALL Addr_" << addr;
	_reg->Write16(_reg, SP, _reg->Read16(_reg, SP) - 2);
	_mmu->WriteMemory16(_mmu, _reg->Read16(_reg, SP), _reg->Read16(_reg, PC));
	_reg->Write16(_reg, PC, addr);
	_cycleCounter += 12;
}

//Call address n if following condition is true
void CPU::CallCcNn(uint8_t opcode) {
	switch (opcode) {
	case 0xC4:
		if (_flags->GetFlag(FLAG_Z) == 0x00) {
			return CallNn();
		}
		break;
	case 0xCC:
		if (_flags->GetFlag(FLAG_Z) == 0x01) {
			return CallNn();
		}
		break;
	case 0xD4:
		if (_flags->GetFlag(FLAG_C) == 0x00) {
			return CallNn();
		}
		break;
	case 0xDC:
		if (_flags->GetFlag(FLAG_C) == 0x01) {
			return CallNn();
		}
		break;
	}
}

//Push present address onto stack.  Jump to address $0000 + n.
void CPU::RstN(uint8_t opcode) {
	uint16_t addr = _mmu->ReadMemory16(_mmu, _reg->Read16(_reg, PC));
	_reg->Write16(_reg, SP, _reg->Read16(_reg, SP) - 2);
	_mmu->WriteMemory16(_mmu, _reg->Read16(_reg, SP), addr); //TODO, should this be byte swap?
	switch (opcode) {
	case 0xC7:
		_reg->Write16(_reg, PC, 0x0000 + 0x00);
		break;
	case 0xCF:
		_reg->Write16(_reg, PC, 0x0000 + 0x08);
		break;
	case 0xD7:
		_reg->Write16(_reg, PC, 0x0000 + 0x10);
		break;
	case 0xDF:
		_reg->Write16(_reg, PC, 0x0000 + 0x18);
		break;
	case 0xE7:
		_reg->Write16(_reg, PC, 0x0000 + 0x20);
		break;
	case 0xEF:
		_reg->Write16(_reg, PC, 0x0000 + 0x28);
		break;
	case 0xF7:
		_reg->Write16(_reg, PC, 0x0000 + 0x30);
		break;
	case 0xFF:
		_reg->Write16(_reg, PC, 0x0000 + 0x38);
		break;
	default:
		std::cout << "ERROR UNKNOWN OPCODE (CALL)" << std::hex << (int)opcode;
	}
	_cycleCounter += 16;
}

// Pop two bytes from stack& jump to that address. [8 cycles]
void CPU::Ret() {
	uint16_t stackAddr = _reg->Read16(_reg, SP);
	uint16_t value = _mmu->ReadMemory16(_mmu, stackAddr);
	_reg->Write16(_reg, SP, (stackAddr + 2));
	_reg->Write16(_reg, PC, value);
	_cycleCounter += 8;
}

//Pop two bytes if following condition is true 
void CPU::RetCc(uint8_t opcode) {
	switch (opcode) {
	case 0xC0:
		if (_flags->GetFlag(FLAG_Z) == 0x00) {
			Ret();
		}
		break;
	case 0xC8:
		if (_flags->GetFlag(FLAG_Z) == 0x01) {
			Ret();
		}
		break;
	case 0xD0:
		if (_flags->GetFlag(FLAG_C) == 0x00) {
			Ret();
		}
		break;
	case 0xD8:
		if (_flags->GetFlag(FLAG_C) == 0x01) {
			Ret();
		}
		break;
	}
}

//Pop two bytes off stack and enable interrupts
void CPU::RetI() {
	Ret();
	_ime = true;
}

void CPU::DestroyCpu(CPU* cpu) {
	delete cpu;
}
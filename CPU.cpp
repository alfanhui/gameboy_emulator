#include <iostream>
#include <string>
#include <uchar.h>
#include "CPU.h"

void CPU::runInstruction(uint16_t opcode)
{
	switch (opcode) {
		case 0x06: case 0x0E: case 0x16: case 0x1E:	case 0x26: case 0x2E:
			LDnn_n(opcode); 
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
			LDr1_r2(opcode);
			break;
		case 0x0A: case 0x1A: case 0xFA: case 0x3E:
			LDA_n(opcode);
			break;
		case 0x47: case 0x4F: case 0x57: case 0x5F: case 0x67: case 0x6F:
		case 0x02: case 0x12: case 0x77: case 0xEA:
			LDn_A(opcode);
			break;
		case 0xF2: 
			LDA_C(opcode);
			break;
		case 0xE2: 
			LDC_A(opcode);
			break;
		case 0x3A: 
			LDA_HLneg(opcode);
			break;
		case 0x2A:
			LDDA_HLpos(opcode);
			break;
		case 0x22: 
			LDIHL_A(opcode);
			break;
		case 0xE0:
			LDN_A(opcode);
			break;
		case 0xF0: 
			LDA_N(opcode);
			break;
		case 0x01: case 0x11: case 0x21: case 0x31:
			LDn_nn16(opcode);
			break;
		case 0xF9:
			LDSP_HL(opcode);
			break;
		case 0xF8: 
			LDHL_SPn(opcode);
			break;
		case 0x08: 
			LDNN_SP(opcode);
			break;
		case 0xF5: case 0xC5: case 0xD5: case 0xE5:
			PUSHnn(opcode);
			break;
		case 0xF1: case 0xC1: case 0xD1: case 0xE1:
			POPnn(opcode);
		case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: 
		case 0x86: case 0x87: case 0xC6:
			ADDA_n(opcode);
			break;
		case 0x88: case 0x89: case 0x8A: case 0x8B: case 0x8C: case 0x8D:
		case 0x8E: case 0x8F: case 0xCE:
			ABCA_n(opcode);
			break;
		case 0x90: case 0x91: case 0x92: case 0x93: case 0x94: case 0x95:
		case 0x96: case 0x97: case 0xD6:
			SUBA_n(opcode);
			break;
		case 0x98: case 0x99: case 0x9A: case 0x9B: case 0x9C: case 0x9D:
		case 0x9E: case 0x9F: //case ?? wonderful documentation
			SBCA_n(opcode);
			break;
		case 0xA0: case 0xA1: case 0xA2: case 0xA3: case 0xA4: case 0xA5:
		case 0xA6: case 0xA7: case 0xE6:
			ANDA_n(opcode);
			break;
		case 0xB0: case 0xB1: case 0xB2: case 0xB3: case 0xB4: case 0xB5:
		case 0xB6: case 0xB7: case 0xF6:
			ORA_n(opcode);
			break;
		case 0xA8: case 0xA9: case 0xAA: case 0xAB: case 0xAC: case 0xAD:
		case 0xAE: case 0xAF: case 0xEE:
			XORA_n(opcode);
			break;
		case 0xB8: case 0xB9: case 0xBA: case 0xBB: case 0xBC: case 0xBD:
		case 0xBE: case 0xBF: case 0xFE:
			CPA_n(opcode);
			break;
		case 0x04: case 0x0C: case 0x14: case 0x1C: case 0x24: case 0x2C:
		case 0x34: case 0x3C:
			break;
		default: 
			std::cout << "Instruction not mapped: " << std::hex << opcode << std::endl;
	}
}

//all variations 8 cycles
//Desc: Put value n into _reg.
void CPU::LDnn_n(uint16_t opcode) {
	_reg->write8(_reg, ((opcode + 2) / 8) - 1, _reg->pc_first);
}

//Put value r2 into r1.
void CPU::LDr1_r2(uint16_t opcode) {
	//12 cycles
	if (opcode == 0x36) { //edge case
		_mmu->writeMemory8(_mmu, _reg->read16(_reg, HL), _reg->pc_first);
		return;
	}
	float r = (opcode / 8.0f) - 8.0f;
	uint8_t r1_orig = floor(r);
	uint8_t r2_orig = (fmod(r, 8.0f) - (float)r1_orig) / 0.125f;
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
	//8 cycles
	if(r1_orig == 6)
	{   //r1 is HL
		_mmu->writeMemory8(_mmu, _reg->read16(_reg, HL), _reg->array[r2]);
		return;
	}
	//8 cycles
	if (r2_orig == 6) {
		//r2 is HL
		_reg->write8(_reg, r1, _mmu->readBios16(_mmu, _reg->read16(_reg, HL))); 
		return;
	}
	//4 cycles
	_reg->write8(_reg, r1, _reg->array[r2]);
}

//Put value n into A.
void CPU::LDA_n(uint16_t opcode) {
	uint8_t n_value = BC;
	switch (opcode) {
	case 0x1A:
		n_value = DE; // 4 cycles
		break;
	case 0xFA:
		_reg->write8(_reg, A, _mmu->readMemory8(_mmu, _mmu->readMemory16(_mmu, _reg->read16(_reg, PC)))); // 16 cycles
		return;
	case 0x3E:
		_reg->write8(_reg, A, _mmu->readMemory8(_mmu, _reg->read16(_reg, PC))); // 8 cycles
		return;
	default:
		break;
	}
	_reg->write8(_reg, A, _mmu->readMemory16(_mmu, _reg->read16(_reg, n_value)));
}

//Put value A into n
void CPU::LDn_A(uint16_t opcode) {
	uint16_t n = (((opcode + 1) / 8) - 9);
	switch (opcode) {
	case 0x02:
		n = _reg->read16(_reg,BC); //8 cycles
		break;
	case 0x12:
		n = _reg->read16(_reg,DE); //8 cycles 
		break;
	case 0x77:
		n = _reg->read16(_reg, HL); //8 cycles
break;
	case 0xEA:
		n = _reg->read16(_reg, PC); //16 cycles
		break;
	}
	_mmu->writeMemory8(_mmu, n, _reg->a); //4 cycles
}

//Put value at address $FF00 + C into A. [8 cycles]
void CPU::LDA_C(uint16_t opcode) {
	_reg->write8(_reg, A, _mmu->readMemory8(_mmu, 0xFF00 + _reg->c));
}

//Put value A into $FF00 + C. [8 cycles]
void CPU::LDC_A(uint16_t opcode) {
	_mmu->writeMemory8(_mmu, (0xFF00 + _reg->c), _reg->a);
}

//Put value at address HL into A, then Decrement HL. [8 cycles]
void CPU::LDA_HLneg(uint16_t opcode) {
	_reg->write8(_reg, A, _mmu->readMemory16(_mmu, _reg->read16(_reg, HL)));
	_reg->write16(_reg, HL, _reg->read16(_reg, HL) - 1);
}

//Put value at address HL into A, then Increment HL. [8 cycles] 
void CPU::LDDA_HLpos(uint16_t opcode) {
	_reg->write8(_reg, A, _mmu->readMemory16(_mmu, _reg->read16(_reg, HL)));
	_reg->write16(_reg, HL, _reg->read16(_reg, HL) + 1);
}

//Put A in the address HL, then Increment HL. [8 cycles]
void CPU::LDIHL_A(uint16_t opcode) {
	_mmu->writeMemory8(_mmu, _reg->read16(_reg, HL), _reg->read8(_reg, A));
	_reg->write16(_reg, HL, _reg->read16(_reg, HL) + 1);
}

//Put value A into $FF00 + n. [12 cycles]
void CPU::LDN_A(uint16_t opcode) {
	_mmu->writeMemory8(_mmu, (0xFF00 + _reg->pc_first), _reg->a);
}

//Put memory address $FF00 + n into A. [12 cycles]
void CPU::LDA_N(uint16_t opcode) {
	_reg->write8(_reg, A, _mmu->readBios16(_mmu, 0xFF00 + _reg->pc_first));
}

//Put 16byte value nn into n. 12 cycles
void CPU::LDn_nn16(uint16_t opcode) {
	_mmu->writeMemory16(_mmu, _reg->read16(_reg, (((opcode - 1) / 16) * 2)), _reg->read16(_reg, PC));
}

//Put HL into SP [8 cycles]
void CPU::LDSP_HL(uint16_t opcode) {
	_reg->write16(_reg, SP, _reg->read16(_reg, HL));
}

//LDHLSPn Put SP + n effective address into HL. [12 cycles]
void CPU::LDHL_SPn(uint16_t opcode) {
	_reg->write16(_reg, HL, _mmu->readMemory16(_mmu, _reg->read16(_reg, SP) + _reg->pc_first));
	//Set flags
	_flags->setFlag(FLAG_C, (_reg->read16(_reg, SP) + _reg->pc_first) > 0xFF);
	_flags->setFlag(FLAG_C, ((_reg->read16(_reg, SP) & 0xF) + (_reg->pc_first & 0xF)) > 0xF);
	_flags->setFlag(FLAG_Z, false);
	_flags->setFlag(FLAG_N, false);
}

//Put Stack Pointer (SP) at address nn [20 cycles]
void CPU::LDNN_SP(uint16_t opcode) {
	_mmu->writeMemory16(_mmu, _reg->read16(_reg, PC), _reg->read16(_reg, SP));
}

//Push register pair nn onto stack. Decrement Stack Pointer (SP) twice [16 cycles]
void CPU::PUSHnn(uint16_t opcode) {
	_mmu->writeMemory16(_mmu, _reg->read16(_reg, SP), _reg->read16(_reg, ((int)floor(opcode / 8) - 24)));
	_reg->write16(_reg, SP, _reg->read16(_reg, SP) - 2);
}

//Pop two bytes off stack into register pair nn. Increment Stack Pointer (SP) twice. [12 cycles]
void CPU::POPnn(uint16_t opcode) {
	_reg->write16(_reg, (uint16_t)((int)floor(opcode / 8) - 24), _mmu->readMemory16(_mmu, _reg->read16(_reg, SP)));
	_reg->write16(_reg, SP, _reg->read16(_reg, SP) + 2);
}

//Add n to A.
void CPU::ADDA_n(uint16_t opcode) {
	uint8_t n;
	if (opcode == 0x86) { //edge case [8 cycles]
		n = _mmu->readMemory8(_mmu, _reg->read16(_reg, HL));
	}
	else if (opcode == 0xC6) { //edge case [8 cycles]
		n = _mmu->readMemory8(_mmu, _reg->read16(_reg, SP));
	}
	else if (opcode == 0x87) { //A,A, edge case [4 cycles]
		n = _reg->read8(_reg, (opcode - 129));
	}
	else {
		n = _reg->read8(_reg, (opcode - 128)); //[4 cycles]
	}
	uint8_t value = n + _reg->a;
	_reg->write8(_reg, A, value);

	//Set flags
	_flags->setFlag(FLAG_C, (value > 0xFF));
	_flags->setFlag(FLAG_H, (((_reg->a & 0xF) + (n & 0xF)) > 0xF));
	_flags->setFlag(FLAG_N, false); //Not a subtraction method
	_flags->setFlag(FLAG_Z, (value == 0));
}

//Add n + carry flag to A.
void CPU::ABCA_n(uint16_t opcode) {
	uint8_t n;
	if (opcode == 0x8E) { //edge case [8 cycles]
		n = _mmu->readMemory8(_mmu, _reg->read16(_reg, HL));
	}
	else if (opcode == 0xCE) { //edge case [8 cycles]
		n = _mmu->readMemory8(_mmu, _reg->read16(_reg, SP));
	}
	else if (opcode == 0x97) { //A,A edge case [4 cycles]
		n = _reg->read8(_reg, (opcode - 137));
	}
	else {
		n = _reg->read8(_reg, (opcode - 136));
	}
	uint8_t value = n + _flags->getFlag(FLAG_C) + _reg->a;
	_reg->write8(_reg, A, (_reg->a + value));

	//Set flags
	_flags->setFlag(FLAG_C, (value) > 0xFF);
	_flags->setFlag(FLAG_H, (((_reg->a & 0xF) + (n & 0xF) + (_flags->getFlag(FLAG_C)) > 0xF)));
	_flags->setFlag(FLAG_N, false); //Not a subtraction method
	_flags->setFlag(FLAG_Z, (value) == 0);
}

//Subtract n from A. 
void CPU::SUBA_n(uint16_t opcode){
	uint8_t n;
	if (opcode == 0x96) { //edge case [8 cycles]
		n = _mmu->readMemory8(_mmu, _reg->read16(_reg, HL));
	}
	else if (opcode == 0xCE) { //edge case [8 cycles]
		n = _mmu->readMemory8(_mmu, _reg->read16(_reg, SP));
	}
	else if (opcode == 0x9F) { //A,A edge case [4 cycles]
		n = _reg->read8(_reg, (opcode - 145));
	}
	else {
		n = _reg->read8(_reg, (opcode - 144)); //4 cycles
	}
	int8_t value = (int8_t)(_reg->a - n); //we need to check if goes beyond neg for flag wavin'
	_reg->write8(_reg, A, (uint8_t)value);

	//Set flags
	_flags->setFlag(FLAG_C, (value < 0));
	_flags->setFlag(FLAG_H, ((_reg->a & 0xF) < (n & 0xF)));
	_flags->setFlag(FLAG_N, true);
	_flags->setFlag(FLAG_Z, (value == 0));
}

//Subtract n + carry flag from A. 
void CPU::SBCA_n(uint16_t opcode) {
	uint8_t n;
	if (opcode == 0x9E) { //edge case [8 cycles]
		n = _mmu->readMemory8(_mmu, _reg->read16(_reg, HL));
	}
	else if (opcode == 0xA7) { //A,A edge case [4 cycles]
		n = _reg->read8(_reg, (opcode - 153));
	}
	//case ?? lost opcode #
	else {
		n = _reg->read8(_reg, (opcode - 152)); //4 cycles
	}
	int8_t value = (int8_t)(_reg->a - (n + _flags->getFlag(FLAG_C))); //we need to check if goes beyond neg for flag wavin'
	_reg->write8(_reg, A, (uint8_t)value);

	//Set flags
	_flags->setFlag(FLAG_C, (value < 0));
	_flags->setFlag(FLAG_H, ((_reg->a & 0xF) < ((n + _flags->getFlag(FLAG_C)) &0xF)));
	_flags->setFlag(FLAG_N, true);
	_flags->setFlag(FLAG_Z, (value == 0));
}

//Logically AND n with A, result in A.
void CPU::ANDA_n(uint16_t opcode) {
	uint8_t n;
	if (opcode == 0xA6) { //edge case [8 cycles]
		n = _mmu->readMemory8(_mmu, _reg->read16(_reg, HL));
	} 
	else if (opcode == 0xE6) { //edge case [8 cycles]
		n = _mmu->readMemory8(_mmu, _reg->read16(_reg, SP));
	} 
	else if (opcode == 0xA7) { //A,A edge case [4 cycles]
		n = _reg->read8(_reg, (opcode - 161));
	}
	else {
		n = _reg->read8(_reg, (opcode - 160)); //4 cycles
	}
	uint8_t value = (_reg->a & n);
	_reg->write8(_reg, A, value);

	//Set flags
	_flags->setFlag(FLAG_C, false);
	_flags->setFlag(FLAG_H, (((_reg->a & 0xF) & (n & 0xF)) > 0xF));
	_flags->setFlag(FLAG_N, false);
	_flags->setFlag(FLAG_Z, (value == 0));
}

// Logical OR n with register A, result in A.
void CPU::ORA_n(uint16_t opcode) {
	uint8_t n;
	if (opcode == 0xB6) { //edge case [8 cycles]
		n = _mmu->readMemory8(_mmu, _reg->read16(_reg, HL));
	}
	else if (opcode == 0xF6) { //edge case [8 cycles]
		n = _mmu->readMemory8(_mmu, _reg->read16(_reg, SP));
	}
	else if (opcode == 0xB7) { //A,A edge case [4 cycles]
		n = _reg->read8(_reg, (opcode - 177));
	}
	else {
		n = _reg->read8(_reg, (opcode - 176)); //4 cycles
	}
	uint8_t value = (_reg->a | n);
	_reg->write8(_reg, A, value);

	//Set flags
	_flags->setFlag(FLAG_C, false);
	_flags->setFlag(FLAG_H, false);
	_flags->setFlag(FLAG_N, false);
	_flags->setFlag(FLAG_Z, (value == 0));
}

//Logical exclusive OR n with register A, result in A.
void CPU::XORA_n(uint16_t opcode) {
	uint8_t n;
	if (opcode == 0xAE) { //edge case [8 cycles]
		n = _mmu->readMemory8(_mmu, _reg->read16(_reg, HL));
	}
	else if (opcode == 0xEE) { //edge case [8 cycles]
		n = _mmu->readMemory8(_mmu, _reg->read16(_reg, SP));
	}
	else if (opcode == 0xAF) { //A,A edge case [4 cycles]
		n = _reg->read8(_reg, (opcode - 169));
	}
	else {
		n = _reg->read8(_reg, (opcode - 168)); //4 cycles
	}
	uint8_t value = (_reg->a ^ n);
	_reg->write8(_reg, A, value);

	//Set flags
	_flags->setFlag(FLAG_C, false);
	_flags->setFlag(FLAG_H, false);
	_flags->setFlag(FLAG_N, false);
	_flags->setFlag(FLAG_Z, (value == 0));
}

//Compare A with n. Basically A - n, but don't store results
void CPU::CPA_n(uint16_t opcode) {
	uint8_t n;
	if (opcode == 0xBE) { //edge case [8 cycles]
		n = _mmu->readMemory8(_mmu, _reg->read16(_reg, HL));
	}
	else if (opcode == 0xFE) { //edge case [8 cycles]
		n = _mmu->readMemory8(_mmu, _reg->read16(_reg, SP));
	}
	else if (opcode == 0xBF) { //A,A edge case [4 cycles]
		n = _reg->read8(_reg, (opcode - 185));
	}
	else {
		n = _reg->read8(_reg, (opcode - 184)); //4 cycles
	}

	//Set flags
	_flags->setFlag(FLAG_C, (_reg->a < n));
	_flags->setFlag(FLAG_H, (_reg->a & 0xF) < (n & 0xF));
	_flags->setFlag(FLAG_N, true);
	_flags->setFlag(FLAG_Z, ((_reg->a - n) == 0));
}

//Increment register n
void CPU::INCN(uint16_t opcode) {
	//04 B		04 0
	//0C C		12 1
	//14 D		20 2
	//1C E		28 3
	//24 H		36 4
	//2C L		44 5
	//34 (HL)	52 4
	//3C A		60 6
}

void CPU::destroyCpu(CPU* cpu) {
	delete cpu;
}
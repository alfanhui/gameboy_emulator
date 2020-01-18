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
		case 0xF2: //LD A,(C) Put value at address $FF00 + C into A. [8 cycles]
			_reg->write8(_reg, A, _mmu->readMemory8(_mmu, 0xFF00 + _reg->c));
			break;
		case 0xE2: //LD (C),A Put value A into $FF00 + C. [8 cycles]
			_mmu->writeMemory8(_mmu, (0xFF00 + _reg->c), _reg->a);
			break;
		case 0x3A: //LD A,HL- Put value at address HL into A, then Decrement HL. [8 cycles]
			_reg->write8(_reg, A, _mmu->readMemory16(_mmu, _reg->read16(_reg, HL)));
			_reg->write16(_reg, HL, _reg->read16(_reg, HL) - 1);
			break;
		case 0x2A: //LD A,HL+ Put value at address HL into A, then Increment HL. [8 cycles]
			_reg->write8(_reg, A, _mmu->readMemory16(_mmu, _reg->read16(_reg, HL)));
			_reg->write16(_reg, HL, _reg->read16(_reg, HL) + 1);
			break;
		case 0x22: //LD HL+,A Put A in the address HL, then Increment HL. [8 cycles]
			_mmu->writeMemory8(_mmu, _reg->read16(_reg, HL), _reg->read8(_reg, A));
			_reg->write16(_reg, HL, _reg->read16(_reg, HL) + 1);
			break;
		case 0xE0: //LD (n),A Put value A into $FF00 + n. [12 cycles]
			_mmu->writeMemory8(_mmu, (0xFF00 + _reg->pc_first), _reg->a);
			break;
		case 0xF0: //LD A,(n) Put memory address $FF00 + n into A. [12 cycles]
			_reg->write8(_reg, A, _mmu->readBios16(_mmu, 0xFF00 + _reg->pc_first));
			break;
		case 0x01: case 0x11: case 0x21: case 0x31:
			LDn_nn16(opcode);
			break;
		case 0xF9:
			//Put HL into SP [8 cycles]
			_reg->write16(_reg, SP, _reg->read16(_reg, HL));
			break;
		default: 
			std::cout << "Instruction not mapped." << std::endl;
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
	_mmu->writeMemory8(_mmu, n, _reg->a ); //4 cycles
}

//Put 16byte value nn into n. 12 cycles
void CPU::LDn_nn16(uint16_t opcode) {
	_mmu->writeMemory16(_mmu, _reg->read16(_reg,(((opcode - 1) / 16) * 2)), _reg->read16(_reg, PC));
}




void CPU::destroyCpu(CPU* cpu) {
	delete cpu;
}
#include <iostream>
#include <string>
#include "CPU.h"
#include "MMU.h"
#include <uchar.h>

CPU::CPU() {
	reg = new CPURegister();
	reg->write16(reg, PC, 0x100);
}

void CPU::runInstruction(uint8_t opcode, uint8_t n)
{
	switch (opcode) {
		case 0x06: case 0x0E: case 0x16: case 0x1E:	case 0x26: case 0x2E:
			LDnn_n(opcode, n); 
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
			LDr1_r2(opcode, n);
			break;
		case 0x0A: case 0x1A: case 0xFA: case 0x3E:
			LDA_n(opcode, n);
			break;
		default: 
			std::cout << "Instruction not mapped." << std::endl;
	}
}

//all variations 8 cycles
//Desc: Put value n into reg.
void CPU::LDnn_n(uint8_t opcode, uint8_t n) {
	reg->write8(reg, ((opcode + 2) / 8) - 1, n);
}

//Put value r2 into r1.
void CPU::LDr1_r2(uint8_t opcode, uint8_t n) {
	//12 cycles
	if (opcode == 0x36) { //edge case
		reg->write16(reg, HL, n);
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
		reg->write16(reg, H, reg->array[r2]);
		return;
	}
	//8 cycles
	if (r2_orig == 6) {
		//r2 is HL
		reg->write8(reg, r1, reg->array[H]);
		return;
	}
	//4 cycles
	reg->write8(reg, r1, reg->array[r2]);
}

void CPU::LDA_n(uint16_t opcode, uint16_t n) {

}

void CPU::destroyCpu(CPU* cpu) {
	delete cpu;
}

#include "CPURegister.h"

// Read8(this, addr)
uint8_t CPURegister::Read8(CPURegister* reg, uint8_t addr) {
	return *(reg->array + addr);
}

// Write8(this, addr, data)
void CPURegister::Write8(CPURegister* reg, uint8_t addr, uint8_t data) {
	reg->array[addr] = data;
}

// Read16(this, addr)
uint16_t CPURegister::Read16(CPURegister* reg, uint16_t addr)
{
	return *((uint16_t*)(reg->array + addr));
}

// Write16(this, addr, data)
void CPURegister::Write16(CPURegister* reg, uint16_t addr, uint16_t data)
{
	uint16_t* pos = ((uint16_t*)(reg->array + addr));
	*pos = data;
}


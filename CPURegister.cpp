#include "CPURegister.h"


uint8_t CPURegister::Read8(CPURegister* reg, uint8_t addr) {
	return *(reg->array + addr);
}

void CPURegister::Write8(CPURegister* reg, uint8_t addr, uint8_t data) {
	reg->array[addr] = data;
}

uint16_t CPURegister::Read16(CPURegister* reg, uint16_t addr)
{
	return *((uint16_t*)(reg->array + addr));
}

void CPURegister::Write16(CPURegister* reg, uint16_t addr, uint16_t data)
{
	uint16_t* pos = ((uint16_t*)(reg->array + addr));
	*pos = data;
}


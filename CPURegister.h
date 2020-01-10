#pragma once
#include <cstdint>

#define B,G 0x00
#define C 0x01
#define D 0x02
#define E 0x03
#define H 0x04
#define L 0x05
#define A 0x0a
#define F 0x0b
#define BC 0x00
#define DE 0x02
#define HL 0x04
#define SP 0x06
#define PC 0x08
#define AF 0x10

struct CPURegister
{
	union {
		uint8_t array[12];
		struct {
			uint8_t b;
			uint8_t c;
			uint8_t d;
			uint8_t e;
			uint8_t h;
			uint8_t l;
			uint8_t s1;
			uint8_t p1;
			uint8_t p2;
			uint8_t c2;
			uint8_t a;
			uint8_t f;
		};
	};
	uint8_t read8(CPURegister* reg, uint8_t addr);
	void write8(CPURegister* reg, uint8_t addr, uint8_t data);
	uint16_t read16(CPURegister* reg, uint16_t addr);
	void write16(CPURegister* reg, uint16_t addr, uint16_t data);
};
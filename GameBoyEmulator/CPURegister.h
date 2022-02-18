#pragma once
#include <cstdint>

//Due to opcodes numbering, the following order is representative for easily mapping to opcodes.
constexpr auto B = 0x00;
constexpr auto C = 0x01;
constexpr auto D = 0x02;
constexpr auto E = 0x03;
constexpr auto H = 0x04;
constexpr auto L = 0x05;
constexpr auto A = 0x06;
constexpr auto F = 0x07;
constexpr auto BC = 0x00;
constexpr auto DE = 0x02;
constexpr auto HL = 0x04;
constexpr auto AF = 0x06;
constexpr auto SP = 0x08;
constexpr auto PC = 0x0A;

struct CPURegister
{
	const char* labels[8] = { "B", "C", "D", "E", "H", "L", "A", "F"};
	const char* labels16[11] = { "BC", "?", "DE", "?", "HL", "?", "AF", "?", "SP", "?", "PC"};
	union {
		uint8_t array[12];
		struct {
			uint8_t b;
			uint8_t c;
			uint8_t d;
			uint8_t e;
			uint8_t h;
			uint8_t l;
			uint8_t a;
			uint8_t f;
			uint8_t sp_first;
			uint8_t sp_last;
			uint8_t pc_first;
			uint8_t pc_last;
		};
	};
	uint8_t Read8(CPURegister* reg, uint8_t addr);
	void Write8(CPURegister* reg, uint8_t addr, uint8_t data);
	uint16_t Read16(CPURegister* reg, uint16_t addr);
	void Write16(CPURegister* reg, uint16_t addr, uint16_t data);
};
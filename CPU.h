#pragma once
#include <cstdint>
#include <string>

constexpr auto AF = 0x00;
constexpr auto BC = 0x01;
constexpr auto DE = 0x02;
constexpr auto HL = 0x03;
constexpr auto SP = 0x04;
constexpr auto PC = 0x05;

class CPU
{
public:
	struct registers {
		union {
			char array[0x60];
			struct {
				char a;
				char f;
				char b;
				char c;
				char e;
				char d;
				char l;
				char h;
				//char sppc[0x20]; //appears unnecessary and safe to remove
			};
		};
		char16_t read16(CPU::registers* reg, char addr);
		void write16(CPU::registers* reg, char addr, char16_t data);
	};
	void runInstruction();
	void destroyCpu(CPU* cpu);
};



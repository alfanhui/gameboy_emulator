#pragma once
#include <cstdint>
#include <bitset>

constexpr auto FLAG_0 = 0;
constexpr auto FLAG_1 = 1;
constexpr auto FLAG_2 = 2;
constexpr auto FLAG_3 = 3;
constexpr auto FLAG_C = 4; //(C)Carry Flag: Is set if a carry occurred from the last math op OR if register A is the smaller value when executing CP instuction.
constexpr auto FLAG_H = 5; //(H)Half Carry Flag: Is set if a carry occurred from the lower nibble in last math op.
constexpr auto FLAG_N = 6; //(N)Subtract flag: Is set if subtraction was performed in the last math instruction.
constexpr auto FLAG_Z = 7; //(Z)Zero Flag: Is set when result of math opertation is zero or two values (when using CP instruction)

class CPUFlags {
	std::bitset<8> _mask0{ 0b0000'0001 };
	std::bitset<8> _mask1{ 0b0000'0010 };
	std::bitset<8> _mask2{ 0b0000'0100 };
	std::bitset<8> _mask3{ 0b0000'1000 };
	std::bitset<8> _mask4{ 0b0001'0000 }; 
	std::bitset<8> _mask5{ 0b0010'0000 }; 
	std::bitset<8> _mask6{ 0b0100'0000 }; 
	std::bitset<8> _mask7{ 0b1000'0000 }; 
	std::bitset<8> GetMasker(int mask);
public:
	std::bitset<8> flags{ }; //8 bit comparer
	int GetFlag(int mask);
	void SetFlag(int mask, bool isOn);
	void BitFlip(int mask);
};
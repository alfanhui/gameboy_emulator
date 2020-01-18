#pragma once
#include <cstdint>
#include <bitset>

constexpr auto FLAG_0 = 0;
constexpr auto FLAG_1 = 1;
constexpr auto FLAG_2 = 2;
constexpr auto FLAG_3 = 3;
constexpr auto FLAG_C = 4;
constexpr auto FLAG_H = 5;
constexpr auto FLAG_n = 6;
constexpr auto FLAG_Z = 7;

class CPUFlags {
	std::bitset<8> mask0{ 0b0000'0001 };
	std::bitset<8> mask1{ 0b0000'0010 };
	std::bitset<8> mask2{ 0b0000'0100 };
	std::bitset<8> mask3{ 0b0000'1000 };
	std::bitset<8> mask4{ 0b0001'0000 }; //C
	std::bitset<8> mask5{ 0b0010'0000 }; //H
	std::bitset<8> mask6{ 0b0100'0000 }; //N
	std::bitset<8> mask7{ 0b1000'0000 }; //Z
	std::bitset<8> getMasker(int mask);
public:
	std::bitset<8> flags{ }; //8 bit comparer
	int getFlag(int mask);
	void setFlag(int mask, bool isOn);
	void bitFlip(int mask);
};
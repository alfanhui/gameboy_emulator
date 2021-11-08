#include "CPUFlags.h"
#include <iostream>
#include <optional>

std::bitset<8> CPUFlags::GetMask(int mask) {
	switch (mask) {
	case 0:
		return _mask0;
	case 1:
		return _mask1;
	case 2:
		return _mask2;
	case 3:
		return _mask3;
	case 4:
		return _mask4;
	case 5:
		return _mask5;
	case 6:
		return _mask6;
	case 7:
		return _mask7;
	default:
		//Error!
		throw std::invalid_argument("getMasker was given out of bound int");
	}
}

int CPUFlags::GetFlag(int mask){
	GetMask(mask); //Test if value is in mask
	return flags.test(mask);
}

//Deprecated
void CPUFlags::SetFlag(int mask, bool value) {
	std::bitset<8> masker = GetMask(mask);
	if (value) {
		flags |= masker; //OR
	}
	else {
		flags &= ~masker; //AND
	}
}

// Logic gate AND - only true if both are true (mask is always 1, so it resets bit to zero)
void CPUFlags::SetZeroAtMask(int mask) {
	std::bitset<8> masker = GetMask(mask);
	flags &= ~masker;
}

// Logic gate OR - only TRUE if either are true (turns on, mask is always 1)
void CPUFlags::SetOneAtMask(int mask) {
	std::bitset<8> masker = GetMask(mask);
	flags |= masker;
}

// Logic gate XOR - only TRUE if they are opposing values (bit switches)
void CPUFlags::SetBitFlipAtMask(int mask) {
	std::bitset<8> masker = GetMask(mask);
	flags ^= masker;
}
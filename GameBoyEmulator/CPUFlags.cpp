#include "CPUFlags.h"
#include <iostream>

std::bitset<8> CPUFlags::GetMasker(int mask) {
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
	return flags.test(mask);
}

//Theres probably a more neater way of doing this, but does it really matter?
void CPUFlags::SetFlag(int mask, bool isOn) {
	std::bitset<8> masker = GetMasker(mask);
	if (isOn) {
		flags |= masker;
	}
	else {
		flags &= ~masker;
	}
}

void CPUFlags::BitFlip(int mask) {
	std::bitset<8> masker = GetMasker(mask);
	flags ^= masker;
}
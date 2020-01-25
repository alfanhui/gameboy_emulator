#include "CPUFlags.h"
#include <iostream>

std::bitset<8> CPUFlags::getMasker(int mask) {
	switch (mask) {
	case 0:
		return mask0;
	case 1:
		return mask1;
	case 2:
		return mask2;
	case 3:
		return mask3;
	case 4:
		return mask4;
	case 5:
		return mask5;
	case 6:
		return mask6;
	case 7:
		return mask7;
	default:
		//Error!
		throw std::invalid_argument("getMasker was given out of bound int");
	}
}

int CPUFlags::getFlag(int mask){
	return flags.test(mask);
}

//Theres probably a more neater way of doing this, but does it really matter?
void CPUFlags::setFlag(int mask, bool isOn) {
	std::bitset<8> masker = getMasker(mask);
	if (isOn) {
		flags |= masker;
	}
	else {
		flags &= ~masker;
	}
}

void CPUFlags::bitFlip(int mask) {
	std::bitset<8> masker = getMasker(mask);
	flags ^= masker;
}
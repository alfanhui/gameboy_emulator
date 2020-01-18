#include "CPUFlags.h"

std::bitset<8> CPUFlags::getMasker(int mask) {
	switch (mask) {
	case 0:
		return mask0;
		break;
	case 1:
		return mask1;
		break;
	case 2:
		return mask2;
		break;
	case 3:
		return mask3;
		break;
	case 4:
		return mask4;
		break;
	case 5:
		return mask5;
		break;
	case 6:
		return mask6;
		break;
	case 7:
		return mask7;
		break;
	default:
		//Error!
		break;
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
#include "MMU.h"
#include "FileLoader.h"
#include <cstdint>
#include <iostream>
#include <string.h>
#include <exception>

class mmuException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Virtual Memory Management Unit Exception: ";
	}
} mmuException;

void MMU::loadBios(MMU* mmu, std::string filePath) {
	FileLoader fileLoader;
	char* bios = fileLoader.ReadFile(filePath);
	try {
		memcpy(mmu->bios, bios, sizeof(bios));
		if (sizeof(mmu->bios) != 256) {
			throw mmuException;
		}
	} catch (std::exception & e) {
		std::cout << e.what() << "Not expected bios size (256).";
	}
	std::cout << "BIOS Loaded.\n";
}

char MMU::readBios8(MMU* mmu, char addr) {
	return *(mmu->bios + addr);
}

void MMU::writeBios8(MMU* mmu, char addr, char data) {
	mmu->bios[addr] = data;
}

//not used?
char16_t MMU::readBios16(MMU* mmu, char addr) {
	return *((char16_t*)(mmu->bios + addr));
}

//not used?
void MMU::writeBios16(MMU* mmu, char16_t addr, char16_t data) {
	char16_t* pos = ((char16_t*)(mmu->bios + addr));
	*pos = data;
}

char16_t MMU::readMemory16(MMU* mmu, char16_t addr) {
	return *((char16_t*) (mmu->memory + addr));
}

void MMU::writeMemory16(MMU* mmu, char16_t addr, char16_t data) {
	char16_t* pos = ((char16_t*)(mmu->memory + addr));
	*pos = data;
}

void MMU::destroy(MMU* mmu) {
	delete mmu;
}
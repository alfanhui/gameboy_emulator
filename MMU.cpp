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
		memcpy(mmu->bios, bios, 0xFF);
		if (sizeof(mmu->bios) != 256) {
			throw mmuException;
		}
	} catch (std::exception & e) {
		std::cout << e.what() << "Not expected bios size (256).";
	}
	std::cout << "BIOS Loaded.\n";
}

uint8_t MMU::readBios8(MMU* mmu, uint8_t addr) {
	return *(mmu->bios + addr);
}

void MMU::writeBios8(MMU* mmu, uint8_t addr, uint8_t data) {
	mmu->bios[addr] = data;
}

//not used?
uint16_t MMU::readBios16(MMU* mmu, uint16_t addr) {
	return *((char16_t*)(mmu->bios + addr));
}

//not used?
void MMU::writeBios16(MMU* mmu, uint16_t addr, uint16_t data) {
	uint16_t* pos = ((uint16_t*)(mmu->bios + addr));
	*pos = data;
}

uint16_t MMU::readMemory16(MMU* mmu, uint16_t addr) {
	return *((uint16_t*) (mmu->memory + addr));
}

void MMU::writeMemory16(MMU* mmu, uint16_t addr, uint16_t data) {
	uint16_t* pos = ((uint16_t*)(mmu->memory + addr));
	*pos = data;
}

void MMU::destroy(MMU* mmu) {
	delete mmu;
}
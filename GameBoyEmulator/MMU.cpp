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

void MMU::LoadBios(MMU* mmu, std::string filePath) {
	FileLoader fileLoader;
	uint8_t* bios = fileLoader.ReadFile(filePath);
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

void MMU::LoadCartridge(MMU* mmu, std::string filePath) {
	FileLoader fileLoader;
	uint8_t* rom = fileLoader.ReadFile(filePath);
	std::cout << "ROM size: " << fileLoader.SizeOfFile(filePath) << " RAM size: " << sizeof(mmu->rom) << std::endl;
	memcpy(mmu->rom, rom, fileLoader.SizeOfFile(filePath));
	std::cout << "ROM Loaded.\n";
}

uint8_t MMU::ReadMemory8(MMU* mmu, uint16_t addr) {
	return *(mmu->memory + addr);
}

void MMU::WriteMemory8(MMU* mmu, uint16_t addr, uint8_t data) {
	mmu->memory[addr] = data;
}

uint16_t MMU::ReadMemory16(MMU* mmu, uint16_t addr) {
	return *((uint16_t*) (mmu->memory + addr));
}

void MMU::WriteMemory16(MMU* mmu, uint16_t addr, uint16_t data) {
	uint16_t* pos = ((uint16_t*)(mmu->memory + addr));
	*pos = data;
}

void MMU::Destroy(MMU* mmu) {
	delete mmu;
}
#include "MMU.h"
#include "FileLoader.h"
#include <cstdint>
#include <iostream>
#include <string.h>

void MMU::loadBios(MMU* mmu, std::string filePath) {
	FileLoader fileLoader;
	char* bios = fileLoader.ReadFile(filePath);
	memcpy(mmu->bios, bios, sizeof(bios));
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

char16_t MMU::readMemory16(MMU* mmu, char16_t addr) {
	return *((char16_t*) (mmu->memory + addr));
}

void MMU::writeMemory16(MMU* mmu, char16_t addr, char16_t data) {
	mmu->memory[addr] = data;
}

void MMU::destroy(MMU* mmu) {
	delete mmu;
}

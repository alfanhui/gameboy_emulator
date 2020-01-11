// GameBoy Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CPU.h"
#include "FileLoader.h"
#include "MMU.h"
#define BIOS_FILE_PATH "dmg_boot.bin"

int main()
{
    std::cout << "GameBoy Emulator Started.\n";
    MMU* mmu = new MMU();
    mmu->loadBios(mmu, BIOS_FILE_PATH);

    CPU* cpu = new CPU();
    cpu->runInstruction(0x00, 0x00);

    mmu->destroy(mmu);
    std::cout << "GameBoy Emulator Exited.\n";
}
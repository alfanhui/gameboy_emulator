// GameBoy Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CPU.h"
#define BIOS_FILE_PATH "dmg_boot.bin"

int main()
{
    std::cout << "GameBoy Emulator Started.\n";
    MMU* mmu = new MMU();
    CPURegister* reg = new CPURegister();
    CPUFlags* flags = new CPUFlags();

    reg->write16(reg, PC, 0x100);
    mmu->loadBios(mmu, BIOS_FILE_PATH);

    CPU* cpu = new CPU(mmu, reg, flags);
    cpu->runInstruction(0x00);

    mmu->destroy(mmu);
    std::cout << "GameBoy Emulator Exited.\n";
}
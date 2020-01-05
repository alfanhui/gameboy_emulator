// GameBoy Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CPU.h"
#include "FileLoader.h"
#include "MMU.h"

int main()
{
    std::cout << "GameBoy Emulator Started.\n";

    MMU* mmu = new MMU;
    mmu->loadBios(mmu, "dmg_boot.bin");
    
    CPU cpu;
    unsigned char test_instruction = 0xCe;
    cpu.run_instruction("AA", test_instruction);

    mmu->destroy(mmu);
    std::cout << "GameBoy Emulator closed.\n";
}
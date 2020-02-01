// GameBoy Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "CPU.h"
constexpr auto BIOS_FILE_PATH = "dmg_boot.bin";
constexpr auto BIOS_SKIP = false;

int main()
{
    std::cout << "GameBoy Emulator Started.\n";
    MMU* mmu = new MMU();
    CPURegister* reg = new CPURegister();
    CPUFlags* flags = new CPUFlags();

    BIOS_SKIP ? reg->Write16(reg, PC, 0x0100) : reg->Write16(reg, PC, 0x0000);
    mmu->LoadBios(mmu, BIOS_FILE_PATH);

    CPU* cpu = new CPU(mmu, reg, flags);

    //game loop
    do {
        uint8_t opcode = mmu->ReadMemory8(mmu, reg->Read8(reg, PC));
        std::cout << "Execute: " << std::hex << (int)opcode << " ";
        reg->Write16(reg, PC, (reg->Read16(reg, PC) + 1));
        cpu->RunInstruction(opcode);
        std::cout << std::endl;
        Sleep(500);
    } while (reg->Read16(reg, PC) != 0x0100);   //while not the end of bios

    mmu->Destroy(mmu);
    std::cout << "GameBoy Emulator Exited.\n";
}
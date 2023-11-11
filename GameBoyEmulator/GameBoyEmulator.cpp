// GameBoy Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "CPU.h"
constexpr auto BIOS_FILE_PATH = "dmg_boot.bin";
constexpr auto CARTRIDGE_FILE_PATH = "Tetris.gb"; //Tetris is used as it doesnt require MBC
constexpr auto BIOS_SKIP = false;
constexpr auto POLLING_DELAY = 1; //150

int main()
{
    std::cout << "GameBoy Emulator Started.\n";
    MMU* mmu = new MMU();
    CPURegister* reg = new CPURegister();
    CPUFlags* flags = new CPUFlags();

    BIOS_SKIP ? reg->Write16(reg, PC, 0x0100) : reg->Write16(reg, PC, 0x0000);
    mmu->LoadBios(mmu, BIOS_FILE_PATH);
    mmu->LoadCartridge(mmu, CARTRIDGE_FILE_PATH);

    CPU* cpu = new CPU(mmu, reg, flags);
    //game loop
    do {
        uint8_t opcode = mmu->ReadMemory8(mmu, reg->Read8(reg, PC));
        std::cout << "Execute " << (int)reg->Read16(reg, PC) << ": " << std::hex << (int)opcode << " ";
        reg->array[PC]++; //Next value
        cpu->RunInstruction(opcode);
        std::cout << std::endl;
        //sleep:
        #ifdef _WIN32
        Sleep(POLLING_DELAY);
        #else
        usleep(POLLING_DELAY*1000);
        #endif
    } while (reg->Read16(reg, PC) != 0x0100);   //while not the end of bios

    mmu->Destroy(mmu);
    std::cout << "GameBoy Emulator Exited.\n";
}
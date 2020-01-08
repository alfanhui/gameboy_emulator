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
    cpu->runInstruction();
    CPU::registers* re = new CPU::registers();
    re->a = 0x05;
    re->f = 0x15;
    re->b = 0x20;
    re->c = 0x25;
    re->e = 0x30;
    re->d = 0x35;
    re->h = 0x40;
    re->l = 0x45;
    re->write16(re, SP, u'd');
    re->write16(re, PC, u'e');
    std::cout << std::hex << (int)re->a << std::hex << (int)re->f << std::endl;
    std::cout << re->read16(re, BC) << std::endl;
    std::cout << re->read16(re, DE) << std::endl;
    std::cout << re->read16(re, HL) << std::endl;
    std::cout << re->read16(re, SP) << std::endl;
    std::cout << re->read16(re, PC) << std::endl;


    mmu->destroy(mmu);
    std::cout << "GameBoy Emulator Exited.\n";
}
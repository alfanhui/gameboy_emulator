#include "pch.h"
#include "CppUnitTest.h"
#include "../GameBoyEmulator/CPU.h"
#include "../GameBoyEmulator/CPU.cpp"
#include "../GameBoyEmulator/CPURegister.h"
#include "../GameBoyEmulator/CPURegister.cpp"
#include "../GameBoyEmulator/MMU.h"
#include "../GameBoyEmulator/MMU.cpp"
#include "../GameBoyEmulator/FileLoader.h"
#include "../GameBoyEmulator/FileLoader.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPUTests
{
	TEST_CLASS(CPUTests)
	{
	public:
		MMU* mmu;
		CPURegister* reg;
		CPUFlags* flags;
		CPU* cpu;

		TEST_METHOD_INITIALIZE(Init) {
			mmu = new MMU();
			reg = new CPURegister();
			flags = new CPUFlags();
			cpu = new CPU(mmu, reg, flags);
			//Set PC to zero
			reg->Write16(reg, PC, 0x0000);
			cpu->SetCycleCounter(0);
			std::cout << "PC" << (int)reg->Read16(reg, PC);
		}

		void LdNnnTest(uint8_t opcode, uint8_t random_number1, uint8_t random_number2)
		{
			//Setup reg and next 8bit number for test
			reg->Write8(reg, ((opcode + 2) / 8) - 1, random_number1);
			mmu->WriteMemory8(mmu, 0x0000, random_number2);
			//Test
			cpu->LdNnn(opcode);
			//Results
			uint8_t value = mmu->ReadMemory8(mmu, random_number2);
			Assert::AreEqual(random_number1, value);
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
			Assert::AreEqual((uint8_t)1, reg->Read8(reg, PC)); //Must increase as it read next value
		}

		TEST_METHOD(LdNnnForBWorks) {
			Assert::AreEqual(B, ((0x06 + 2) / 8) - 1);
			LdNnnTest(0x06, 0x01, 0x05);
		}

		TEST_METHOD(LdNnnForCWorks) {
			Assert::AreEqual(C, ((0x0E + 2) / 8) - 1);
			LdNnnTest(0x0E, 0x10, 0x15);
		}

		TEST_METHOD(LdNnnForDWorks) {
			Assert::AreEqual(D, ((0x16 + 2) / 8) - 1);
			LdNnnTest(0x16, 0x20, 0x25);
		}

		TEST_METHOD(LdNnnForEWorks) {
			Assert::AreEqual(E, ((0x1E + 2) / 8) - 1);
			LdNnnTest(0x1E, 0x30, 0x35);
		}

		TEST_METHOD(LdNnnForHWorks) {
			Assert::AreEqual(H, ((0x26 + 2) / 8) - 1);
			LdNnnTest(0x26, 0x40, 0x45);
		}

		TEST_METHOD(LdNnnForLWorks) {
			Assert::AreEqual(L, ((0x2E + 2) / 8) - 1);
			LdNnnTest(0x2E, 0x50, 0x55);
		}
	};
}
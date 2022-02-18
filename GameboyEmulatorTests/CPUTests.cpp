#include "pch.h"
#include "CppUnitTest.h"
#include "../GameBoyEmulator/CPU.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPUTests
{
	TEST_CLASS(UtilFuncs)
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
		}

		TEST_METHOD(ByteSwapWorks) {
			uint16_t value = 0x01 << 8 | 0x02;
			uint16_t expected = 0x02 << 8 | 0x01;
			Assert::IsTrue(value != expected);
			uint16_t switched_value = cpu->ByteSwap(value);
			Assert::IsTrue(switched_value == expected);
		}

		TEST_METHOD(TestBit) {
			uint8_t value = 0x01;
			Assert::IsTrue((value & 1) ? 1 : 0);
		}
	};

	TEST_CLASS(LdNnn)
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
		}

		TEST_METHOD(LdNnnForBWorks) {
			//Setup reg and next 8bit number for test
			mmu->WriteMemory8(mmu, reg->Read8(reg, PC), 0x01);
			//Test
			cpu->LdNnn(0x06);
			//Results
			uint8_t value = reg->Read8(reg, B);
			Assert::AreEqual((uint8_t)0x01, value);
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
			Assert::AreEqual((uint8_t)1, reg->Read8(reg, PC)); //Must increase as it read next value
		}

		TEST_METHOD(LdNnnForCWorks) {
			//Setup reg and next 8bit number for test
			mmu->WriteMemory8(mmu, reg->Read8(reg, PC), 0x10);
			//Test
			cpu->LdNnn(0x0E);
			//Results
			uint8_t value = reg->Read8(reg, C);
			Assert::AreEqual((uint8_t)0x10, value);
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
			Assert::AreEqual((uint8_t)1, reg->Read8(reg, PC)); //Must increase as it read next value
		}

		TEST_METHOD(LdNnnForDWorks) {
			//Setup reg and next 8bit number for test
			mmu->WriteMemory8(mmu, reg->Read8(reg, PC), 0x20);
			//Test
			cpu->LdNnn(0x16);
			//Results
			uint8_t value = reg->Read8(reg, D);
			Assert::AreEqual((uint8_t)0x20, value);
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
			Assert::AreEqual((uint8_t)1, reg->Read8(reg, PC)); //Must increase as it read next value
		}

		TEST_METHOD(LdNnnForEWorks) {
			//Setup reg and next 8bit number for test
			mmu->WriteMemory8(mmu, reg->Read8(reg, PC), 0x30);
			//Test
			cpu->LdNnn(0x1E);
			//Results
			uint8_t value = reg->Read8(reg, E);
			Assert::AreEqual((uint8_t)0x30, value);
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
			Assert::AreEqual((uint8_t)1, reg->Read8(reg, PC)); //Must increase as it read next value
		}

		TEST_METHOD(LdNnnForHWorks) {
			//Setup reg and next 8bit number for test
			mmu->WriteMemory8(mmu, reg->Read8(reg, PC), 0x40);
			//Test
			cpu->LdNnn(0x26);
			//Results
			uint8_t value = reg->Read8(reg, H);
			Assert::AreEqual((uint8_t)0x40, value);
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
			Assert::AreEqual((uint8_t)1, reg->Read8(reg, PC)); //Must increase as it read next value
		}

		TEST_METHOD(LdNnnForLWorks) {
			//Setup reg and next 8bit number for test
			mmu->WriteMemory8(mmu, reg->Read8(reg, PC), 0x50);
			//Test
			cpu->LdNnn(0x2E);
			//Results
			uint8_t value = reg->Read8(reg, L);
			Assert::AreEqual((uint8_t)0x50, value);
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
			Assert::AreEqual((uint8_t)1, reg->Read8(reg, PC)); //Must increase as it read next value
		}
	};

	TEST_CLASS(LdR1R2)
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
		}

		TEST_METHOD(LdNnnForAAWorks) {
			reg->Write8(reg, A, 0x01);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, A));
			cpu->LdR1R2(0x7F);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, A));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForABWorks) {
			reg->Write8(reg, B, 0x01);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, B));
			cpu->LdR1R2(0x78);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, A));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForACWorks) {
			reg->Write8(reg, C, 0x02);
			Assert::AreEqual((uint8_t)0x02, reg->Read8(reg, C));
			cpu->LdR1R2(0x79);
			Assert::AreEqual((uint8_t)0x02, reg->Read8(reg, A));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForADWorks) {
			reg->Write8(reg, D, 0x03);
			Assert::AreEqual((uint8_t)0x03, reg->Read8(reg, D));
			cpu->LdR1R2(0x7A);
			Assert::AreEqual((uint8_t)0x03, reg->Read8(reg, A));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForAEWorks) {
			reg->Write8(reg, E, 0x04);
			Assert::AreEqual((uint8_t)0x04, reg->Read8(reg, E));
			cpu->LdR1R2(0x7B);
			Assert::AreEqual((uint8_t)0x04, reg->Read8(reg, A));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForAHWorks) {
			reg->Write8(reg, H, 0x05);
			Assert::AreEqual((uint8_t)0x05, reg->Read8(reg, H));
			cpu->LdR1R2(0x7C);
			Assert::AreEqual((uint8_t)0x05, reg->Read8(reg, A));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}
		TEST_METHOD(LdNnnForALWorks) {
			reg->Write8(reg, L, 0x06);
			Assert::AreEqual((uint8_t)0x06, reg->Read8(reg, L));
			cpu->LdR1R2(0x7D);
			Assert::AreEqual((uint8_t)0x06, reg->Read8(reg, A));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForAHLWorks) {
			reg->Write16(reg, HL, 0x1010);
			mmu->WriteMemory8(mmu, reg->Read16(reg, HL), 0x07);
			Assert::AreEqual((uint8_t)0x07, mmu->ReadMemory8(mmu, reg->Read16(reg, HL)));
			cpu->LdR1R2(0x7E);
			Assert::AreEqual((uint8_t)0x07, reg->Read8(reg, A));
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
		}
		TEST_METHOD(LdNnnForBBWorks) {
			reg->Write8(reg, B, 0x01);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, B));
			cpu->LdR1R2(0x40);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, B));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForBCWorks) {
			reg->Write8(reg, C, 0x02);
			Assert::AreEqual((uint8_t)0x02, reg->Read8(reg, C));
			cpu->LdR1R2(0x41);
			Assert::AreEqual((uint8_t)0x02, reg->Read8(reg, B));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForBDWorks) {
			reg->Write8(reg, D, 0x03);
			Assert::AreEqual((uint8_t)0x03, reg->Read8(reg, D));
			cpu->LdR1R2(0x42);
			Assert::AreEqual((uint8_t)0x03, reg->Read8(reg, B));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForBEWorks) {
			reg->Write8(reg, E, 0x04);
			Assert::AreEqual((uint8_t)0x04, reg->Read8(reg, E));
			cpu->LdR1R2(0x43);
			Assert::AreEqual((uint8_t)0x04, reg->Read8(reg, B));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForBHWorks) {
			reg->Write8(reg, H, 0x05);
			Assert::AreEqual((uint8_t)0x05, reg->Read8(reg, H));
			cpu->LdR1R2(0x44);
			Assert::AreEqual((uint8_t)0x05, reg->Read8(reg, B));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForBLWorks) {
			reg->Write8(reg, L, 0x06);
			Assert::AreEqual((uint8_t)0x06, reg->Read8(reg, L));
			cpu->LdR1R2(0x45);
			Assert::AreEqual((uint8_t)0x06, reg->Read8(reg, B));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForBHLWorks) {
			reg->Write16(reg, HL, 0x1010);
			mmu->WriteMemory8(mmu, reg->Read16(reg, HL), 0x07);
			Assert::AreEqual((uint8_t)0x07, mmu->ReadMemory8(mmu, reg->Read16(reg, HL)));
			cpu->LdR1R2(0x46);
			Assert::AreEqual((uint8_t)0x07, reg->Read8(reg, B));
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
		}
		TEST_METHOD(LdNnnForCBWorks) {
			reg->Write8(reg, B, 0x01);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, B));
			cpu->LdR1R2(0x48);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, C));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForCCWorks) {
			reg->Write8(reg, C, 0x02);
			Assert::AreEqual((uint8_t)0x02, reg->Read8(reg, C));
			cpu->LdR1R2(0x49);
			Assert::AreEqual((uint8_t)0x02, reg->Read8(reg, C));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForCDWorks) {
			reg->Write8(reg, D, 0x03);
			Assert::AreEqual((uint8_t)0x03, reg->Read8(reg, D));
			cpu->LdR1R2(0x4A);
			Assert::AreEqual((uint8_t)0x03, reg->Read8(reg, C));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForCEWorks) {
			reg->Write8(reg, E, 0x04);
			Assert::AreEqual((uint8_t)0x04, reg->Read8(reg, E));
			cpu->LdR1R2(0x4B);
			Assert::AreEqual((uint8_t)0x04, reg->Read8(reg, C));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForCHWorks) {
			reg->Write8(reg, H, 0x05);
			Assert::AreEqual((uint8_t)0x05, reg->Read8(reg, H));
			cpu->LdR1R2(0x4C);
			Assert::AreEqual((uint8_t)0x05, reg->Read8(reg, C));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForCLWorks) {
			reg->Write8(reg, L, 0x06);
			Assert::AreEqual((uint8_t)0x06, reg->Read8(reg, L));
			cpu->LdR1R2(0x4D);
			Assert::AreEqual((uint8_t)0x06, reg->Read8(reg, C));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForCHLWorks) {
			reg->Write16(reg, HL, 0x1010);
			mmu->WriteMemory8(mmu, reg->Read16(reg, HL), 0x07);
			Assert::AreEqual((uint8_t)0x07, mmu->ReadMemory8(mmu, reg->Read16(reg, HL)));
			cpu->LdR1R2(0x4E);
			Assert::AreEqual((uint8_t)0x07, reg->Read8(reg, C));
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForDBWorks) {
			reg->Write8(reg, B, 0x01);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, B));
			cpu->LdR1R2(0x50);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, D));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForDCWorks) {
			reg->Write8(reg, C, 0x02);
			Assert::AreEqual((uint8_t)0x02, reg->Read8(reg, C));
			cpu->LdR1R2(0x51);
			Assert::AreEqual((uint8_t)0x02, reg->Read8(reg, D));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForDDWorks) {
			reg->Write8(reg, D, 0x03);
			Assert::AreEqual((uint8_t)0x03, reg->Read8(reg, D));
			cpu->LdR1R2(0x52);
			Assert::AreEqual((uint8_t)0x03, reg->Read8(reg, D));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForDEWorks) {
			reg->Write8(reg, E, 0x04);
			Assert::AreEqual((uint8_t)0x04, reg->Read8(reg, E));
			cpu->LdR1R2(0x53);
			Assert::AreEqual((uint8_t)0x04, reg->Read8(reg, D));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForDHWorks) {
			reg->Write8(reg, H, 0x05);
			Assert::AreEqual((uint8_t)0x05, reg->Read8(reg, H));
			cpu->LdR1R2(0x54);
			Assert::AreEqual((uint8_t)0x05, reg->Read8(reg, D));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForDLWorks) {
			reg->Write8(reg, L, 0x06);
			Assert::AreEqual((uint8_t)0x06, reg->Read8(reg, L));
			cpu->LdR1R2(0x55);
			Assert::AreEqual((uint8_t)0x06, reg->Read8(reg, D));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForDHLWorks) {
			reg->Write16(reg, HL, 0x1010);
			mmu->WriteMemory8(mmu, reg->Read16(reg, HL), 0x07);
			Assert::AreEqual((uint8_t)0x07, mmu->ReadMemory8(mmu, reg->Read16(reg, HL)));
			cpu->LdR1R2(0x56);
			Assert::AreEqual((uint8_t)0x07, reg->Read8(reg, D));
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForEBWorks) {
			reg->Write8(reg, B, 0x01);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, B));
			cpu->LdR1R2(0x58);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, E));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForECWorks) {
			reg->Write8(reg, C, 0x02);
			Assert::AreEqual((uint8_t)0x02, reg->Read8(reg, C));
			cpu->LdR1R2(0x59);
			Assert::AreEqual((uint8_t)0x02, reg->Read8(reg, E));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForEDWorks) {
			reg->Write8(reg, D, 0x03);
			Assert::AreEqual((uint8_t)0x03, reg->Read8(reg, D));
			cpu->LdR1R2(0x5A);
			Assert::AreEqual((uint8_t)0x03, reg->Read8(reg, E));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForEEWorks) {
			reg->Write8(reg, E, 0x04);
			Assert::AreEqual((uint8_t)0x04, reg->Read8(reg, E));
			cpu->LdR1R2(0x5B);
			Assert::AreEqual((uint8_t)0x04, reg->Read8(reg, E));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForEHWorks) {
			reg->Write8(reg, H, 0x05);
			Assert::AreEqual((uint8_t)0x05, reg->Read8(reg, H));
			cpu->LdR1R2(0x5C);
			Assert::AreEqual((uint8_t)0x05, reg->Read8(reg, E));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForELWorks) {
			reg->Write8(reg, L, 0x06);
			Assert::AreEqual((uint8_t)0x06, reg->Read8(reg, L));
			cpu->LdR1R2(0x5D);
			Assert::AreEqual((uint8_t)0x06, reg->Read8(reg, E));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForEHLWorks) {
			reg->Write16(reg, HL, 0x1010);
			mmu->WriteMemory8(mmu, reg->Read16(reg, HL), 0x07);
			Assert::AreEqual((uint8_t)0x07, mmu->ReadMemory8(mmu, reg->Read16(reg, HL)));
			cpu->LdR1R2(0x5E);
			Assert::AreEqual((uint8_t)0x07, reg->Read8(reg, E));
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
		}


		TEST_METHOD(LdNnnForHBWorks) {
			reg->Write8(reg, B, 0x01);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, B));
			cpu->LdR1R2(0x60);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, H));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForHCWorks) {
			reg->Write8(reg, C, 0x02);
			Assert::AreEqual((uint8_t)0x02, reg->Read8(reg, C));
			cpu->LdR1R2(0x61);
			Assert::AreEqual((uint8_t)0x02, reg->Read8(reg, H));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForHDWorks) {
			reg->Write8(reg, D, 0x03);
			Assert::AreEqual((uint8_t)0x03, reg->Read8(reg, D));
			cpu->LdR1R2(0x62);
			Assert::AreEqual((uint8_t)0x03, reg->Read8(reg, H));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForHEWorks) {
			reg->Write8(reg, E, 0x04);
			Assert::AreEqual((uint8_t)0x04, reg->Read8(reg, E));
			cpu->LdR1R2(0x63);
			Assert::AreEqual((uint8_t)0x04, reg->Read8(reg, H));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForHHWorks) {
			reg->Write8(reg, H, 0x05);
			Assert::AreEqual((uint8_t)0x05, reg->Read8(reg, H));
			cpu->LdR1R2(0x64);
			Assert::AreEqual((uint8_t)0x05, reg->Read8(reg, H));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForHLWorks) {
			reg->Write8(reg, L, 0x06);
			Assert::AreEqual((uint8_t)0x06, reg->Read8(reg, L));
			cpu->LdR1R2(0x65);
			Assert::AreEqual((uint8_t)0x06, reg->Read8(reg, H));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForHHLWorks) {
			reg->Write16(reg, HL, 0x1010);
			mmu->WriteMemory8(mmu, reg->Read16(reg, HL), 0x07);
			Assert::AreEqual((uint8_t)0x07, mmu->ReadMemory8(mmu, reg->Read16(reg, HL)));
			cpu->LdR1R2(0x66);
			Assert::AreEqual((uint8_t)0x07, reg->Read8(reg, H));
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForLBWorks) {
			reg->Write8(reg, B, 0x01);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, B));
			cpu->LdR1R2(0x68);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, L));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForLCWorks) {
			reg->Write8(reg, C, 0x02);
			Assert::AreEqual((uint8_t)0x02, reg->Read8(reg, C));
			cpu->LdR1R2(0x69);
			Assert::AreEqual((uint8_t)0x02, reg->Read8(reg, L));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForLDWorks) {
			reg->Write8(reg, D, 0x03);
			Assert::AreEqual((uint8_t)0x03, reg->Read8(reg, D));
			cpu->LdR1R2(0x6A);
			Assert::AreEqual((uint8_t)0x03, reg->Read8(reg, L));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForLEWorks) {
			reg->Write8(reg, E, 0x04);
			Assert::AreEqual((uint8_t)0x04, reg->Read8(reg, E));
			cpu->LdR1R2(0x6B);
			Assert::AreEqual((uint8_t)0x04, reg->Read8(reg, L));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForLHWorks) {
			reg->Write8(reg, H, 0x05);
			Assert::AreEqual((uint8_t)0x05, reg->Read8(reg, H));
			cpu->LdR1R2(0x6C);
			Assert::AreEqual((uint8_t)0x05, reg->Read8(reg, L));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForLLWorks) {
			reg->Write8(reg, L, 0x06);
			Assert::AreEqual((uint8_t)0x06, reg->Read8(reg, L));
			cpu->LdR1R2(0x6D);
			Assert::AreEqual((uint8_t)0x06, reg->Read8(reg, L));
			Assert::AreEqual((uint32_t)4, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForLHLWorks) {
			reg->Write16(reg, HL, 0x1010);
			mmu->WriteMemory8(mmu, reg->Read16(reg, HL), 0x07);
			Assert::AreEqual((uint8_t)0x07, mmu->ReadMemory8(mmu, reg->Read16(reg, HL)));
			cpu->LdR1R2(0x6E);
			Assert::AreEqual((uint8_t)0x07, reg->Read8(reg, L));
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForHLBWorks) {
			reg->Write8(reg, B, 0x01);
			Assert::AreEqual((uint8_t)0x01, reg->Read8(reg, B));
			cpu->LdR1R2(0x70);
			Assert::AreEqual((uint8_t)0x01, mmu->ReadMemory8(mmu, reg->Read16(reg, HL)));
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForHLCWorks) {
			reg->Write8(reg, C, 0x02);
			Assert::AreEqual((uint8_t)0x02, reg->Read8(reg, C));
			cpu->LdR1R2(0x71);
			Assert::AreEqual((uint8_t)0x02, mmu->ReadMemory8(mmu, reg->Read16(reg, HL)));
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForHLDWorks) {
			reg->Write8(reg, D, 0x03);
			Assert::AreEqual((uint8_t)0x03, reg->Read8(reg, D));
			cpu->LdR1R2(0x72);
			Assert::AreEqual((uint8_t)0x03, mmu->ReadMemory8(mmu, reg->Read16(reg, HL)));
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForHLEWorks) {
			reg->Write8(reg, E, 0x04);
			Assert::AreEqual((uint8_t)0x04, reg->Read8(reg, E));
			cpu->LdR1R2(0x73);
			Assert::AreEqual((uint8_t)0x04, mmu->ReadMemory8(mmu, reg->Read16(reg, HL)));
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForHLHWorks) {
			reg->Write8(reg, H, 0x05);
			Assert::AreEqual((uint8_t)0x05, reg->Read8(reg, H));
			cpu->LdR1R2(0x74);
			Assert::AreEqual((uint8_t)0x05, mmu->ReadMemory8(mmu, reg->Read16(reg, HL)));
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForHLLWorks) {
			reg->Write8(reg, L, 0x06);
			Assert::AreEqual((uint8_t)0x06, reg->Read8(reg, L));
			cpu->LdR1R2(0x75);
			Assert::AreEqual((uint8_t)0x06, mmu->ReadMemory8(mmu, reg->Read16(reg, HL)));
			Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
		}

		TEST_METHOD(LdNnnForHLNWorks) {			
			mmu->WriteMemory8(mmu, reg->Read8(reg, PC), 0x11);
			Assert::AreEqual((uint8_t)0x11, mmu->ReadMemory8(mmu, reg->Read16(reg, PC)));
			cpu->LdR1R2(0x36);
			Assert::AreEqual((uint8_t)0x11, mmu->ReadMemory8(mmu, reg->Read16(reg, HL)));
			Assert::AreEqual((uint32_t)12, cpu->GetCycleCounter());
			Assert::AreEqual((uint8_t)1, reg->Read8(reg, PC)); //Must increase as it read next value
		}
	};


	TEST_CLASS(LdNnn16)
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

			//Set all flags to be different to aid tests
			reg->Write16(reg, BC, 0x10);
			reg->Write16(reg, DE, 0x20);
			reg->Write16(reg, AF, 0x30);
			reg->Write16(reg, HL, 0x40);
			reg->Write16(reg, SP, 0x50);
		}

		TEST_METHOD(LdNNn16ForBCWorks) {		
			//Setup reg and next 16bit number for test
			mmu->WriteMemory16(mmu, reg->Read16(reg, PC), (uint16_t)0x37);
			//Test
			cpu->LdNNn16(0x01);
			//Results
			uint16_t value = mmu->ReadMemory16(mmu, reg->Read16(reg, BC));
			Assert::IsTrue((uint16_t)0x37 == value);
			Assert::AreEqual((uint32_t)12, cpu->GetCycleCounter());
			Assert::AreEqual((uint8_t)2, reg->Read8(reg, PC)); //Must increase as it read next value
		}

		TEST_METHOD(LdNNn16ForDEWorks) {
			//Setup reg and next 16bit number for test
			mmu->WriteMemory16(mmu, reg->Read16(reg, PC), (uint16_t)0x47);
			//Test
			cpu->LdNNn16(0x11);
			//Results
			uint16_t value = mmu->ReadMemory16(mmu, reg->Read16(reg, DE));
			Assert::IsTrue((uint16_t)0x47 == value);
			Assert::AreEqual((uint32_t)12, cpu->GetCycleCounter());
			Assert::AreEqual((uint8_t)2, reg->Read8(reg, PC)); //Must increase as it read next value
		}

		TEST_METHOD(LdNNn16ForHLWorks) {
			//Setup reg and next 16bit number for test
			mmu->WriteMemory16(mmu, reg->Read16(reg, PC), (uint16_t)0x57);
			//Test
			cpu->LdNNn16(0x21);
			//Results
			uint16_t value = mmu->ReadMemory16(mmu, reg->Read16(reg, HL));
			Assert::IsTrue((uint16_t)0x57 == value);
			Assert::AreEqual((uint32_t)12, cpu->GetCycleCounter());
			Assert::AreEqual((uint8_t)2, reg->Read8(reg, PC)); //Must increase as it read next value
		}

		TEST_METHOD(LdNNn16ForSPWorks) {
			//Setup reg and next 16bit number for test
			mmu->WriteMemory16(mmu, reg->Read16(reg, PC), (uint16_t)0x67);
			//Test
			cpu->LdNNn16(0x31);
			//Results
			uint16_t value = mmu->ReadMemory16(mmu, reg->Read16(reg, SP));
			Assert::IsTrue((uint16_t)0x67 == value);
			Assert::AreEqual((uint32_t)12, cpu->GetCycleCounter());
			Assert::AreEqual((uint8_t)2, reg->Read8(reg, PC)); //Must increase as it read next value
		}
	};

	TEST_CLASS(AddHlN16)
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
		}

		void AddHlN16Test(uint8_t opcode, uint8_t random_number1, uint8_t random_number2)
		{
			////Setup reg and next 8bit number for test
			//mmu->WriteMemory8(mmu, reg->Read8(reg, PC), random_number1);
			////Test
			//cpu->LdNNn16(opcode);
			////Results
			//uint8_t value = reg->Read8(reg, ((opcode + 2) / 8) - 1);
			//Assert::AreEqual(random_number1, value);
			//Assert::AreEqual((uint32_t)8, cpu->GetCycleCounter());
			//Assert::AreEqual((uint8_t)1, reg->Read8(reg, PC)); //Must increase as it read next value
		}

		TEST_METHOD(AddHlN16ForBCWorks) {
			Assert::AreEqual(BC, 0x09 == 0x39 ? SP : ((0x09 - 1) / 8) - 1);
			//AddANTest(0x06, 0x01, 0x05);
		}

		TEST_METHOD(AddHlN16ForDEWorks) {
			Assert::AreEqual(DE, 0x19 == 0x39 ? SP : ((0x19 - 1) / 8) - 1);
			//AddANTest(0x0E, 0x10, 0x15);
		}

		TEST_METHOD(AddHlN16ForHLWorks) {
			Assert::AreEqual(HL, 0x29 == 0x39 ? SP : ((0x29 - 1) / 8) - 1);
			//AddANTest(0x16, 0x20, 0x25);
		}

		TEST_METHOD(AddHlN16ForSPWorks) {
			Assert::AreEqual(SP, 0x39 == 0x39 ? SP : ((0x39 - 1) / 8) - 1);
			//AddANTest(0x1E, 0x30, 0x35);
		}
	};
}
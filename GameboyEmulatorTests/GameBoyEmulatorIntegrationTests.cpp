#include "pch.h"
#include "CppUnitTest.h"
#include "../GameBoyEmulator/CPU.h"


constexpr auto BIOS_FILE_PATH = "dmg_boot.bin";

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameBoyEmulatorIntegrationTests
{
	TEST_CLASS(BiosInstructionTest)
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

			mmu->LoadBios(mmu, BIOS_FILE_PATH);
			cpu = new CPU(mmu, reg, flags);
		}

		void AssertNextInstruction(uint8_t expected_opcode) {
			uint8_t opcode = mmu->ReadMemory8(mmu, reg->Read8(reg, PC));
			Assert::AreEqual(expected_opcode, opcode);
			reg->array[PC]++; //Next opcode
			cpu->RunInstruction(opcode);
		}

		TEST_METHOD(BiosLoadsInstructions) {
			AssertNextInstruction(0x31);
		}
	};
}
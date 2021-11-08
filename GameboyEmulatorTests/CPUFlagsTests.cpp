#include "pch.h"
#include "CppUnitTest.h"
#include "../GameBoyEmulator/CPUFlags.h"
#include "../GameBoyEmulator/CPUFlags.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPUFlagsTests
{
	TEST_CLASS(CPUFlagsTests)
	{
	public:
		
		CPUFlags cpuFlags;

		TEST_METHOD_INITIALIZE(Init) {
			cpuFlags.flags = 0b0000'0000;
		}

		TEST_METHOD(GetFlagValuesTest)
		{
			cpuFlags.flags = 0b1010'1010;
			Assert::AreEqual(0, cpuFlags.GetFlag(0));
			Assert::AreEqual(1, cpuFlags.GetFlag(1));
			Assert::AreEqual(0, cpuFlags.GetFlag(2));
			Assert::AreEqual(1, cpuFlags.GetFlag(3));
			Assert::AreEqual(0, cpuFlags.GetFlag(4));
			Assert::AreEqual(1, cpuFlags.GetFlag(5));
			Assert::AreEqual(0, cpuFlags.GetFlag(6));
			Assert::AreEqual(1, cpuFlags.GetFlag(7));
		}

		//OOB - Out of bounds
		TEST_METHOD(GetMaskThrowsErrorIfOOB) {
			auto func = [this] { cpuFlags.GetFlag(8); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		//OOB - Out of bounds
		TEST_METHOD(SetZeroAtMaskThrowsErrorIfOOB) {
			auto func = [this] { cpuFlags.SetZeroAtMask(8); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		//OOB - Out of bounds
		TEST_METHOD(SetOneAtMaskThrowsErrorIfOOB) {
			auto func = [this] { cpuFlags.SetOneAtMask(8); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		//OOB - Out of bounds
		TEST_METHOD(SetBitFlipAtMaskThrowsErrorIfOOB) {
			auto func = [this] { cpuFlags.SetBitFlipAtMask(8); };
			Assert::ExpectException<std::invalid_argument>(func);
		}
		TEST_METHOD(SetBitFlipAtMaskTest)
		{
			cpuFlags.SetBitFlipAtMask(0);
			Assert::IsTrue((std::bitset<8>)0b0000'0001 == cpuFlags.flags);
			cpuFlags.SetBitFlipAtMask(0);
			Assert::IsTrue((std::bitset<8>)0b0000'0000 == cpuFlags.flags);
		}

		TEST_METHOD(SetZeroAtMaskTest)
		{
			cpuFlags.SetZeroAtMask(0);
			Assert::IsTrue((std::bitset<8>)0b0000'0000 == cpuFlags.flags);
			cpuFlags.SetBitFlipAtMask(0); //Flip bit
			Assert::IsTrue((std::bitset<8>)0b0000'0001 == cpuFlags.flags);
			cpuFlags.SetZeroAtMask(0);
			Assert::IsTrue((std::bitset<8>)0b0000'0000 == cpuFlags.flags);
		}

		TEST_METHOD(SetOneAtMaskTest) {
			cpuFlags.SetOneAtMask(0);
			Assert::IsTrue((std::bitset<8>)0b0000'0001 == cpuFlags.flags);
			cpuFlags.SetOneAtMask(0);
			Assert::IsTrue((std::bitset<8>)0b0000'0001 == cpuFlags.flags);
		}
	};
}

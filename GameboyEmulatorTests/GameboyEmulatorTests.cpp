#include "pch.h"
#include "CppUnitTest.h"
#include "../GameBoyEmulator/Test.h"
#include "../GameBoyEmulator/Test.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameboyEmulatorTests
{
	TEST_CLASS(GameboyEmulatorTests)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(1, 1);
		}

		TEST_METHOD(TestMethod2)
		{
			Assert::AreEqual(1, 2);
		}

		TEST_METHOD(TestMethod3)
		{
			Test test;
			Assert::AreEqual(1, test.factorial(1));
		}
	};
}

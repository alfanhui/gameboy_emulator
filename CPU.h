#pragma once
#include <cstdint>
#include <string>

class CPU
{
	public:
		CPU();
		void run_instruction(std::string type, unsigned char instuction);
};



#pragma once
#include <string>

class FileLoader
{
	public:
		uint8_t* ReadFile(std::string fileName);
		int SizeOfFile(std::string filePath);
		void PrintPointerHex(uint8_t* buffer, int bufferLength, int location);
};


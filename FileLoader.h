#include <string>

class FileLoader
{
	public:
		char* ReadFile(std::string fileName);
		int SizeOfFile(std::string filePath);
		void PrintPointerHex(char* buffer, int bufferLength, int location);
};


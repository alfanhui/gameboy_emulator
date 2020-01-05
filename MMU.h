#include <string>
struct MMU
{
	char bios[0x100]; //outside for as originally overriden by ROM
	struct {
		union {
			char memory[0x1000];
			struct {
				char rom[0x8000];
				char videoRam[0x2000];
				char externalRam[0x2000];
				char Ram[0x2000];
				char echoRam[0x1E00];
				char oamRam[0xA0];
				char space[0x60];
				char iO[0x80];
				char hRam[0x7F];
			};
		};
	};

	void loadBios(MMU* mmu, std::string filePath);
	char readBios8(MMU* mmu, char addr);
	void writeBios8(MMU* mmu, char addr, char data);
	char16_t readBios16(MMU* mmu, char addr);
	char16_t readMemory16(MMU* mmu, char16_t addr);
	void writeMemory16(MMU* mmu, char16_t addr, char16_t data);
	void destroy(MMU* mmu);
};
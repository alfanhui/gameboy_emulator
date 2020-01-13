#include <string>
struct MMU
{
	uint8_t bios[0x100]; //outside but originally overridden by ROM
	struct {
		union {
			uint8_t memory[0xFFFF];
			struct {
				uint8_t rom[0x8000];
				uint8_t videoRam[0x2000];
				uint8_t externalRam[0x2000];
				uint8_t Ram[0x2000];
				uint8_t echoRam[0x1E00];
				uint8_t oamRam[0xA0];
				uint8_t space[0x60];
				uint8_t iO[0x80];
				uint8_t hRam[0x7F];
			};
		};
	};

	void loadBios(MMU* mmu, std::string filePath);
	uint8_t readBios8(MMU* mmu, uint8_t addr);
	void writeBios8(MMU* mmu, uint8_t addr, uint8_t data);
	uint16_t readBios16(MMU* mmu, uint16_t addr);
	void writeBios16(MMU* mmu, uint16_t addr, uint16_t data);
	uint8_t readMemory8(MMU* mmu, uint16_t addr);
	void writeMemory8(MMU* mmu, uint16_t addr, uint8_t data);
	uint16_t readMemory16(MMU* mmu, uint16_t addr);
	void writeMemory16(MMU* mmu, uint16_t addr, uint16_t data);
	void destroy(MMU* mmu);
};
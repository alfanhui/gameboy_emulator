#include <string>
struct MMU
{
	struct {
		union {
			uint8_t memory[0xFFFF];
			struct {
				uint8_t bios[0x100];
				uint8_t rom[0x7900];
				uint8_t video_ram[0x2000];
				uint8_t external_ram[0x2000];
				uint8_t ram[0x2000];
				uint8_t echo_ram[0x1E00];
				uint8_t oam_ram[0xA0];
				uint8_t space[0x60];
				uint8_t i_o[0x80];
				uint8_t h_ram[0x7F];
			};
		};
	};

	void LoadBios(MMU* mmu, std::string filePath);
	/*uint8_t ReadBios8(MMU* mmu, uint8_t addr);
	void WriteBios8(MMU* mmu, uint8_t addr, uint8_t data);
	uint16_t ReadBios16(MMU* mmu, uint16_t addr);
	void WriteBios16(MMU* mmu, uint16_t addr, uint16_t data);*/
	uint8_t ReadMemory8(MMU* mmu, uint16_t addr);
	void WriteMemory8(MMU* mmu, uint16_t addr, uint8_t data);
	uint16_t ReadMemory16(MMU* mmu, uint16_t addr);
	void WriteMemory16(MMU* mmu, uint16_t addr, uint16_t data);
	void Destroy(MMU* mmu);
};
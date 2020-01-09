#pragma once
#include <cstdint>
struct CPURegister {
	union {
		uint16_t joined;
		struct {
			uint8_t first;
			uint8_t last;
		};
	};
};

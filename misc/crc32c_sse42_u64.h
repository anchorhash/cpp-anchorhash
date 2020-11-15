// Harware based crc calculation

static inline uint32_t crc32c_sse42_u64(uint64_t key, uint64_t seed) {
	__asm__ volatile(
			"crc32q %[key], %[seed];"
			: [seed] "+r" (seed)
			: [key] "rm" (key));
	return seed;
}


#include "bench.h"

void
ascii_to_utf16_scalar(uint16_t *restrict dest, uint8_t const *restrict src, size_t len)
{
	while (len--) *dest++ = *src++;
}

#define IMPLS(f) \
	f(scalar) \
	f(rvv_ext_m1) f(rvv_ext_m2) f(rvv_ext_m4) \
	f(rvv_vsseg_m1) f(rvv_vsseg_m2) f(rvv_vsseg_m4) \
	f(rvv_vss_m1) f(rvv_vss_m2) f(rvv_vss_m4) \

typedef void Func(uint16_t *restrict dest, uint8_t const *restrict src, size_t len);

#define DECLARE(f) extern Func ascii_to_utf16_##f;
IMPLS(DECLARE)

#define EXTRACT(f) { #f, &ascii_to_utf16_##f },
Impl impls[] = { IMPLS(EXTRACT) };

uint16_t *dest;
uint8_t *src;

void init(void) { }

uint64_t checksum(size_t n) {
	uint64_t sum = 0;
	for (size_t i = 0; i < n+9; ++i)
		sum = hash64(sum) + dest[i];
	return sum;
}

void common(size_t n, size_t dOff, size_t sOff) {
	dest = ((uint16_t*)mem) + dOff/2;
	src = (uint8_t*)(dest + 9 + MAX_MEM/3) + sOff;
	for (size_t i = 0; i < MAX_MEM/3; ++i)
		src[i] |= 0x7F;
	memset(dest, 1, (n+9)*2);
}

BENCH(base) {
	common(n, randu64() & 255, randu64() & 255);
	TIME f(dest, src, n);
} BENCH_END

BENCH(aligned) {
	common(n, 0, 0);
	TIME f(dest, src, n);
} BENCH_END

Bench benches[] = {
	{ MAX_MEM/3 - 512-9*2, "ascii to utf16", bench_base },
	{ MAX_MEM/3 - 512-9*2, "ascii to utf16 aligned", bench_aligned },
}; BENCH_MAIN(impls, benches)

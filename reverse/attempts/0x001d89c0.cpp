// _Wmt_idct1
// partial score=0.6 date=2026-10-10
// cl: /O2 /G6 /MD /arch:SSE2
#include <emmintrin.h>

extern "C" void __cdecl Wmt_idct1(const short *input, const short *table, short *output)
{
	__m128i bias = _mm_cvtsi32_si128(15);
	__m128i value = _mm_loadl_epi64((const __m128i *)input);
	__m128i scale = _mm_loadl_epi64((const __m128i *)table);
	value = _mm_mullo_epi16(value, scale);
	value = _mm_add_epi16(value, bias);
	value = _mm_srai_epi16(value, 5);
	value = _mm_unpacklo_epi16(value, value);
	value = _mm_unpacklo_epi32(value, value);
	value = _mm_unpacklo_epi64(value, value);
	_mm_store_si128((__m128i *)output, value);
	_mm_store_si128((__m128i *)(output + 8), value);
	_mm_store_si128((__m128i *)(output + 16), value);
	_mm_store_si128((__m128i *)(output + 24), value);
	_mm_store_si128((__m128i *)(output + 32), value);
	_mm_store_si128((__m128i *)(output + 40), value);
	_mm_store_si128((__m128i *)(output + 48), value);
	_mm_store_si128((__m128i *)(output + 56), value);
}

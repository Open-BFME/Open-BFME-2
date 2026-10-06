// ?Rva009C80C0@@YAXPBF0PAT__m128i@@@Z
// partial score=0.612 date=2026-10-06
// cl: /O2 /MD /arch:SSE2
#include <emmintrin.h>
void Rva009C80C0(const short *a,const short *b,__m128i *destination)
{
 __m128i round=_mm_cvtsi32_si128(15);
 __m128i x=_mm_loadl_epi64((const __m128i *)a);
 __m128i y=_mm_loadl_epi64((const __m128i *)b);
 x=_mm_mullo_epi16(x,y);
 x=_mm_add_epi16(x,round);
 x=_mm_srai_epi16(x,5);
 x=_mm_unpacklo_epi16(x,x);
 x=_mm_unpacklo_epi32(x,x);
 x=_mm_unpacklo_epi64(x,x);
 __m128i second=x;
 _mm_store_si128(destination,x);_mm_store_si128(destination+1,second);
 _mm_store_si128(destination+2,x);_mm_store_si128(destination+3,second);
 _mm_store_si128(destination+4,x);_mm_store_si128(destination+5,second);
 _mm_store_si128(destination+6,x);_mm_store_si128(destination+7,second);
}

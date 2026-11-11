// cl: /MD /Oi- /O1
//
// ?NetworkBufferAppend@@YAPADPADPBD0@Z @0x004478A9 96B.
// Checked strncpy copy: with limit require dst below limit with room, strncpy
// dst from src for limit-dst, truncate at limit-1 when dst+strlen(src) reaches
// limit; without limit _mbscpy; return dst+strlen(src)+1. Evidence: unlock
// lane; callees strncpy IAT 0x00BBA620 strlen thunk 0x00629170 _mbscpy thunk
// 0x00629176 rowed; caller at 0x00447D3F; neighbours share flags.
#include <string.h>
// Retail reaches _mbscpy through its direct-call import thunk.
#pragma push_macro("_CRTIMP")
#undef _CRTIMP
#define _CRTIMP
#include <mbstring.h>
#pragma pop_macro("_CRTIMP")

// WorldBuilder NetworkBufferAppend, WB VA 0x014A7E60 (align lead, score 1.0).
char *__cdecl NetworkBufferAppend(char *dst, const char *src, char *limit)
{
	if (limit != 0) {
		if (dst >= limit)
			return dst;
		if (limit - dst < 1)
			return dst;
		strncpy(dst, src, limit - dst);
		if (dst + strlen(src) >= limit) {
			limit[-1] = 0;
			return limit;
		}
	} else {
		_mbscpy(reinterpret_cast<unsigned char *>(dst),
			reinterpret_cast<const unsigned char *>(src));
	}
	return dst + strlen(src) + 1;
}

char *NetworkBufferAppendRaw(char*,void*,unsigned int,char*);
char *Rva00447891Write1(char *dst,unsigned char value,char *limit)
{
    return NetworkBufferAppendRaw(dst,&value,1,limit);
}

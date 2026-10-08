// cl: /MD /Oi- /O1
//
// ?Rva004478A9Copy@@YAPADPADPBD0@Z @0x004478A9 96B.
// Checked strncpy copy: with limit require dst below limit with room, strncpy
// dst from src for limit-dst, truncate at limit-1 when dst+strlen(src) reaches
// limit; without limit _mbscpy; return dst+strlen(src)+1. Evidence: unlock
// lane; callees strncpy IAT 0x00BBA620 strlen thunk 0x00629170 _mbscpy thunk
// 0x00629176 rowed; caller at 0x00447D3F; neighbours share flags.
extern "C" __declspec(dllimport) char *__cdecl strncpy(char *dst, const char *src, unsigned int n);
extern "C" unsigned int __cdecl strlen(const char *s);
extern "C" char *__cdecl _mbscpy(char *dst, const char *src);

char *__cdecl Rva004478A9Copy(char *dst, const char *src, char *limit)
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
		_mbscpy(dst, src);
	}
	return dst + strlen(src) + 1;
}

char *Rva0044780FCopy(char*,void*,unsigned int,char*);
char *Rva00447891Write1(char *dst,unsigned char value,char *limit)
{
    return Rva0044780FCopy(dst,&value,1,limit);
}

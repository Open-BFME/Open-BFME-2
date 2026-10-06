// cl: /MD /Oi-
// ?Rva00447909Copy@@YAPADPADPAXI0@Z, retail 0x00447909, 54 bytes.
// Checked memcpy: copies size bytes from src to dst and returns src+size,
// or returns src unchanged when the copy would pass limit (null limit always
// copies). Evidence: unlock lane; callees rowed/pinned (memcpy via _memcpy pin
// at 0x006291A8); callers at 0x0044794F 0x0044797C 0x004479A8 0x0044865E;
// landing unblocks 0x0044793F 0x0044796C 0x0044799A 0x00448423.
extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long v);
extern "C" __declspec(dllimport) unsigned short __stdcall htons(unsigned short v);
char *__cdecl Rva00447909Copy(char *src, void *dst, unsigned int size, char *limit)
{
	if (limit != 0) {
		if (src > limit)
			return src;
		if (src + size > limit)
			return src;
	}
	memcpy(dst, src, size);
	return src + size;
}
// ?Rva0044799ACopy1@@YAPADPADPAX0@Z, retail 0x0044799A, 23 bytes.
// Fixed-size-1 checked copy: forwards to Rva00447909Copy. Evidence: chain lane
// calls 0x00447909 which this session landed; callers in 0x00448423.
char *__cdecl Rva0044799ACopy1(char *src, void *dst, char *limit)
{
	return Rva00447909Copy(src, dst, 1, limit);
}
// ?Rva0044793FReadU32@@YAPADPADPAI0@Z, retail 0x0044793F, 45 bytes.
// Checked 4-byte read with htonl: copies via Rva00447909Copy into the src slot
// then byte-swaps to *out. Evidence: chain lane calls 0x00447909; IAT htonl;
// callers in 0x00448423.
char *__cdecl Rva0044793FReadU32(char *src, unsigned int *out, char *limit)
{
	char *next = Rva00447909Copy(src, &src, 4, limit);
	*out = htonl(*(unsigned int *)&src);
	return next;
}
// ?Rva0044796CReadU16@@YAPADPADPAG0@Z, retail 0x0044796C, 46 bytes.
// Checked 2-byte read with htons: copies via Rva00447909Copy into the src slot
// then byte-swaps to *out. Evidence: chain lane calls 0x00447909; IAT htons;
// callers at 0x004484BE 0x004486CB.
char *__cdecl Rva0044796CReadU16(char *src, unsigned short *out, char *limit)
{
	char *next = Rva00447909Copy(src, &src, 2, limit);
	*out = htons(*(unsigned short *)&src);
	return next;
}

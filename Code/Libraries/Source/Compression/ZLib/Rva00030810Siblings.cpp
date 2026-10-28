// cl: /MD
// Sibling of the rowed zlib _inflateInit_ at 0x00690860 (26B). Retail
// 0x00030810 is a 27-byte 4-argument thunk that shuffles its arguments
// through registers and calls the runtime-resolved function pointer at
// 0x00DE0400. The middle argument is the immediate 3. The pointer is
// g_00DE0400, defined in GameMemory.cpp (which stores it from
// GetProcAddress); this thunk calls it through its four-argument type.
extern void *__gameMemReallocatePtr;

int __cdecl rva00030810(void *z, const char *version, int stream_size)
{
	return ((int (__cdecl *)(void *, const char *, int, int))__gameMemReallocatePtr)(z, version, 3, stream_size);
}

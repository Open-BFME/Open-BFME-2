// ?Rva005BCA60@@YAHHHPBDIHH@Z
// partial score=0.96 date=2026-10-07
// cl: /MD /EHsc /DNDEBUG

extern "C" void *__cdecl memcpy(void *destination, const void *source, unsigned int bytes);
void __cdecl operator delete[](void *memory);
void *__cdecl operator new[](unsigned int bytes);
extern void __cdecl b_00042a50(void);
extern void __cdecl Rva005BC887(void);
extern unsigned int g_Va00E06558;

// ?Rva005BCA60@@YAHHHPBDIHH@Z @0x005BCA60 145B
// Target evidence: six stack arguments; argument six is compared with the
// word at VA 0x00E06564. The body releases/replaces the buffer at 0x00E0656C,
// decrements the word at 0x00E06560, and gates the flag at 0x00E06574 before
// its two zero-argument calls. Those global roles and this address-derived
// function identity remain inferred. The 0x005BC887 callee pin is address-only.
int __cdecl Rva005BCA60(int arg1, int arg2, const char *source,
    unsigned int length, int allowEmpty, int owner)
{
	if (owner != *reinterpret_cast<int *>(0x00E06564))
		return 1;

	char *previous = *reinterpret_cast<char **>(0x00E0656C);
	if (previous != 0)
	{
		::operator delete[](previous);
		*reinterpret_cast<char **>(0x00E0656C) = 0;
	}

	if (source != 0 && allowEmpty >= 0 && (allowEmpty > 0 || length > 0))
	{
		*reinterpret_cast<char **>(0x00E0656C) = reinterpret_cast<char *>(::operator new[](length));
		memcpy(*reinterpret_cast<char **>(0x00E0656C), source, length);
		(*reinterpret_cast<char **>(0x00E0656C))[length - 1] = 0;
	}

	// Both C++ prefix-decrement trials emit sub [absolute],1 under MSVC 7.1;
	// retail uses the one-byte-shorter dec form and branches depend on it.
	__asm { dec dword ptr [g_Va00E06558+8] }
	if (*reinterpret_cast<unsigned char *>(0x00E06574) != 0)
	{
		if (*reinterpret_cast<int *>(0x00E06560) == 0)
		{
			b_00042a50();
			*reinterpret_cast<unsigned char *>(0x00E06574) = 0;
		}
	}
	if (*reinterpret_cast<int *>(0x00E06560) == 0)
		Rva005BC887();
	return 1;
}

// cl: /DNDEBUG /MD
// ?Rva00360C1FEqual@@YAHPBX0@Z, retail 0x00360C1F, 24 bytes.
// Returns !memcmp(a, b, 0x1C): 28-byte equality via rowed import thunk.
// Evidence: unlock lane, rowed ji_0062929e memcmp, callers at 0x00360EBC/D3
// 0x005079F7 0x00508738; neg/sbb/inc not idiom proves unsigned char.

extern "C" int __cdecl memcmp(const void *a, const void *b, unsigned int n);

class Rva00360C1FEqualHolder
{
};

int __cdecl Rva00360C1FEqual(const void *a, const void *b)
{
	return memcmp(a, b, 0x1c) == 0;
}

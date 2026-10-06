// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// ?Rva002AA32FEqual@@YA_NPBM00@Z @0x002AA32F 45B: float range equal via ucomiss; caller 0x002AAC9E pushes 3 ptrs and add esp,0xc (__cdecl); unblocks 0x002AAC9E.
bool __cdecl Rva002AA32FEqual(float const* first, float const* last, float const* other)
{
	if (first == last)
		return true;
	for (; first != last; ++first, ++other) {
		if (*first != *other)
			return false;
	}
	return true;
}

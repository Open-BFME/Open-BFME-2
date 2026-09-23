// Cold-slice bool-false returners without vtable carriage (twin-free TU).
//
// Same discipline as ConstZeroGetters.cpp and ConstBoolTrueGetters.cpp
// (opaque address-derived names for unclaimed leaves with no callers,
// no branch sources and no .rdata vtable slot) but for the 3-byte shape
// (xor al,al / ret). Each follows a ret (prev C3) and is followed by a
// function prologue, so the boundary is proven. Kept in a fresh TU to
// avoid contending with hot getter files.
// No // cl: line (defaults match the frameless 3-byte shape; verified
// `32c0c3` with zero relocs for `bool Name(void) { return false; }`).

// ?Rva002B4C32Get@@YA_NXZ @ 0x002b4c32 (3B): returns false.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
bool Rva002B4C32Get(void)
{
	return false;
}

// ?Rva0020D7B9Get@@YA_NXZ @ 0x0020d7b9 (3B): returns false.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
bool Rva0020D7B9Get(void)
{
	return false;
}

// ?Rva005D1F42Get@@YA_NXZ @ 0x005d1f42 (3B): returns false.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
bool Rva005D1F42Get(void)
{
	return false;
}

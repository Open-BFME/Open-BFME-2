// Cold-slice xor-eax zero returners without vtable carriage (twin-free TU).
//
// Same discipline as ConstIntGetters5.cpp (opaque address-derived names for
// unclaimed leaves with no callers, no branch sources and no .rdata vtable
// slot) but for the 3-byte shape (xor eax,eax / ret). Each follows a ret
// (prev C3) and is followed by a function prologue, so the boundary is
// proven. Kept in a fresh TU to avoid contending with hot getter files.
// No // cl: line (defaults match the frameless 3-byte shape).

// ?Rva0028D4DDGet@@YAHXZ @ 0x0028d4dd (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0028D4DDGet(void)
{
	return 0;
}

// ?Rva003E46B1Get@@YAHXZ @ 0x003e46b1 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva003E46B1Get(void)
{
	return 0;
}

// ?Rva003FE25AGet@@YAHXZ @ 0x003fe25a (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva003FE25AGet(void)
{
	return 0;
}

// ?Rva0035BD7BGet@@YAHXZ @ 0x0035bd7b (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0035BD7BGet(void)
{
	return 0;
}

// ?Rva0053EC1EGet@@YAHXZ @ 0x0053ec1e (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0053EC1EGet(void)
{
	return 0;
}

// ?Rva004318C3Get@@YAHXZ @ 0x004318c3 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004318C3Get(void)
{
	return 0;
}

// ?Rva004FC217Get@@YAHXZ @ 0x004fc217 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004FC217Get(void)
{
	return 0;
}


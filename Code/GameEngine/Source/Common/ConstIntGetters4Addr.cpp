// The members of the ConstIntGetters4.cpp family whose constant is a .text
// address no ledger row names yet (code entry points with no matched row),
// split out so the rest of the family links; each moves back once its target
// has a definition to name.
//
// Same 6-byte shape as ConstIntGetters4.cpp (mov eax,<IMM32> / ret).

// ?Rva0008FC9DGet@@YAHXZ @ 0x0008fc9d (6B): returns 0x0049DCEE.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0008FC9DGet(void)
{
	return 0x0049DCEE;
}

// ?Rva0008FFBEGet@@YAHXZ @ 0x0008ffbe (6B): returns 0x0048FF84.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0008FFBEGet(void)
{
	return 0x0048FF84;
}

// ?Rva001052F9Get@@YAHXZ @ 0x001052f9 (6B): returns 0x00504FD5.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva001052F9Get(void)
{
	return 0x00504FD5;
}

// ?Rva0044643DGet@@YAHXZ @ 0x0044643d (6B): returns 0x006D1F77.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0044643DGet(void)
{
	return 0x006D1F77;
}

// ?Rva004E4DFFGet@@YAHXZ @ 0x004e4dff (6B): returns 0x006d1feb.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004E4DFFGet(void)
{
	return 0x006d1feb;
}

// ?Rva004E8D86Get@@YAHXZ @ 0x004e8d86 (6B): returns 0x006d1f3d.
// Follows a ret-12 (prev C2-0C-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004E8D86Get(void)
{
	return 0x006d1f3d;
}

// ?Rva00512C82Get@@YAHXZ @ 0x00512c82 (6B): returns 0x006d1e8f.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00512C82Get(void)
{
	return 0x006d1e8f;
}

// ?Rva0051482FGet@@YAHXZ @ 0x0051482f (6B): returns 0x006d1f03.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0051482FGet(void)
{
	return 0x006d1f03;
}

// ?Rva00516D03Get@@YAHXZ @ 0x00516d03 (6B): returns 0x006d1fb1.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00516D03Get(void)
{
	return 0x006d1fb1;
}

// ?Rva0051AEE3Get@@YAHXZ @ 0x0051aee3 (6B): returns 0x006d205f.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0051AEE3Get(void)
{
	return 0x006d205f;
}

// ?Rva005206DCGet@@YAHXZ @ 0x005206dc (6B): returns 0x006d2147.
// Follows a ret-12 (prev C2-0C-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva005206DCGet(void)
{
	return 0x006d2147;
}

// ?Rva005232CAGet@@YAHXZ @ 0x005232ca (6B): returns 0x006d21bb.
// Follows a ret-12 (prev C2-0C-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva005232CAGet(void)
{
	return 0x006d21bb;
}

// ?Rva00523D54Get@@YAHXZ @ 0x00523d54 (6B): returns 0x006d21fb.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00523D54Get(void)
{
	return 0x006d21fb;
}

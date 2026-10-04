// Cold-slice B8-imm32 const-int returners (twin-free TU).
//
// Same 6-byte shape as ConstIntGetters6.cpp (mov eax,<IMM32> / ret) for
// bodies in regions siblings have not touched. Each is an unclaimed leaf, so
// the opaque address-derived name witnesses only the address and the returned
// constant. Kept in a fresh TU to avoid contending with hot getter files.
// No // cl: line (defaults match the frameless 6-byte shape).

// ?Rva006F67F1Get@@YAHXZ @ 0x006f67f1 (6B): returns 0x0000000d.
// Follows a jump-table dispatch (jmp [eax*4+0xaf6810]); first of five
// consecutive 6B getters. Opaque address-derived name.
int Rva006F67F1Get(void)
{
	return 0x0000000d;
}

// ?Rva006F67F7Get@@YAHXZ @ 0x006f67f7 (6B): returns 0x0000000e.
// Abuts the 0x006f67f1 getter above. Opaque address-derived name.
int Rva006F67F7Get(void)
{
	return 0x0000000e;
}

// ?Rva006F67FDGet@@YAHXZ @ 0x006f67fd (6B): returns 0x0000000f.
// Abuts the 0x006f67f7 getter above. Opaque address-derived name.
int Rva006F67FDGet(void)
{
	return 0x0000000f;
}

// ?Rva006F6803Get@@YAHXZ @ 0x006f6803 (6B): returns 0x0000000c.
// Abuts the 0x006f67fd getter above. Opaque address-derived name.
int Rva006F6803Get(void)
{
	return 0x0000000c;
}

// ?Rva006F6809Get@@YAHXZ @ 0x006f6809 (6B): returns 0x00000003.
// Abuts the 0x006f6803 getter above. Opaque address-derived name.
int Rva006F6809Get(void)
{
	return 0x00000003;
}

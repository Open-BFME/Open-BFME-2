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

// ?Rva0052349BGet@@YAHXZ @ 0x0052349b (6B): returns 0x00c622e4.
// Conditional-skip target (jne lands here); first of three 6B getters.
// Opaque address-derived name.
int Rva0052349BGet(void)
{
	return 0x00c622e4;
}

// ?Rva005234A1Get@@YAHXZ @ 0x005234a1 (6B): returns 0x00c622c0.
// Abuts the 0x0052349b getter above. Opaque address-derived name.
int Rva005234A1Get(void)
{
	return 0x00c622c0;
}

// ?Rva005234A7Get@@YAHXZ @ 0x005234a7 (6B): returns 0x00c62298.
// Abuts the 0x005234a1 getter above. Opaque address-derived name.
int Rva005234A7Get(void)
{
	return 0x00c62298;
}

// ?Rva00559F57Get@@YAHXZ @ 0x00559f57 (6B): returns 0x00dd2380.
// Follows a ret (xor eax,eax / ret); paired 6B getter below.
// Opaque address-derived name.
int Rva00559F57Get(void)
{
	return 0x00dd2380;
}

// ?Rva00559F5DGet@@YAHXZ @ 0x00559f5d (6B): returns 0x00dd236c.
// Abuts the 0x00559f57 getter above. Opaque address-derived name.
int Rva00559F5DGet(void)
{
	return 0x00dd236c;
}

// ?Rva00559F72Get@@YAHXZ @ 0x00559f72 (6B): returns 0x00dd2390.
// Follows a ret (xor eax,eax / ret); paired 6B getter below.
// Opaque address-derived name.
int Rva00559F72Get(void)
{
	return 0x00dd2390;
}

// ?Rva00559F78Get@@YAHXZ @ 0x00559f78 (6B): returns 0x00dd2374.
// Abuts the 0x00559f72 getter above. Opaque address-derived name.
int Rva00559F78Get(void)
{
	return 0x00dd2374;
}

// ?Rva006C5E87Get@@YAHXZ @ 0x006c5e87 (6B): returns 0x00bbac1c.
// Follows int3 padding. Opaque address-derived name.
int Rva006C5E87Get(void)
{
	return 0x00bbac1c;
}

// ?Rva006C5E97Get@@YAHXZ @ 0x006c5e97 (6B): returns 0x00bbac1c.
// Follows int3 padding; same constant as the 0x006c5e87 getter above.
// Opaque address-derived name.
int Rva006C5E97Get(void)
{
	return 0x00bbac1c;
}

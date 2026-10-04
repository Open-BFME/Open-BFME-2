// The members of the ConstIntGetters8.cpp family whose constant is an image address
// no unit defines yet, split out so the rest of the family links; each moves
// back once its target has a definition to name.
//
// Cold-slice B8-imm32 const-int returners (twin-free TU).
//
// Same 6-byte shape as ConstIntGetters7.cpp (mov eax,<IMM32> / ret) for
// bodies in regions siblings have not touched. Each is an unclaimed leaf, so
// the opaque address-derived name witnesses only the address and the returned
// constant. Kept in a fresh TU to avoid contending with hot getter files.
// No // cl: line (defaults match the frameless 6-byte shape).

// ?Rva00020E6BGet@@YAHXZ @ 0x00020e6b (6B): returns 0x00bbac1c.
// Conditional-skip target (test / jne +5). Opaque address-derived name.
int Rva00020E6BGet(void)
{
	return 0x00bbac1c;
}

// ?Rva000B4935Get@@YAHXZ @ 0x000b4935 (6B): returns 0x00de0878.
// Conditional-skip target (jne +5). Opaque address-derived name.
int Rva000B4935Get(void)
{
	return 0x00de0878;
}

// ?Rva000F1ECDGet@@YAHXZ @ 0x000f1ecd (6B): returns 0x00bbac1c.
// Follows a ret (add eax,8 / ret). Opaque address-derived name.
int Rva000F1ECDGet(void)
{
	return 0x00bbac1c;
}

// ?Rva001EF348Get@@YAHXZ @ 0x001ef348 (6B): returns 0x00c18f40.
// Follows padding plus leave / ret. Opaque address-derived name.
int Rva001EF348Get(void)
{
	return 0x00c18f40;
}

// ?Rva001FF282Get@@YAHXZ @ 0x001ff282 (6B): returns 0x00c039e8.
// Follows a ret (pop edi/esi/ebx/ecx / ret). Opaque address-derived name.
int Rva001FF282Get(void)
{
	return 0x00c039e8;
}

// ?Rva00203517Get@@YAHXZ @ 0x00203517 (6B): returns 0x00de0878.
// Conditional-skip target (jne +6). Opaque address-derived name.
int Rva00203517Get(void)
{
	return 0x00de0878;
}

// ?Rva0020D4DDGet@@YAHXZ @ 0x0020d4dd (6B): returns 0x00c082f0.
// Follows a ret (leave / ret 0x14). Opaque address-derived name.
int Rva0020D4DDGet(void)
{
	return 0x00c082f0;
}

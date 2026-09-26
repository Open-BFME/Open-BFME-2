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

// ?Rva000310ACGet@@YAHXZ @ 0x000310ac (6B): returns 0x00000001.
// Branch target (loopne / cmp al,6 / jne +6). Opaque address-derived name.
int Rva000310ACGet(void)
{
	return 0x00000001;
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

// ?Rva0011F519Get@@YAHXZ @ 0x0011f519 (6B): returns 0x00000001.
// Follows a ret (xor eax,eax / ret). Opaque address-derived name.
int Rva0011F519Get(void)
{
	return 0x00000001;
}

// ?Rva0014A0C0Get@@YAHXZ @ 0x0014a0c0 (6B): returns 0x00000001.
// Branch target (test byte ptr / je +6). Opaque address-derived name.
int Rva0014A0C0Get(void)
{
	return 0x00000001;
}

// ?Rva001542BDGet@@YAHXZ @ 0x001542bd (6B): returns 0x00000001.
// Branch target (cmp / ja +6). Opaque address-derived name.
int Rva001542BDGet(void)
{
	return 0x00000001;
}

// ?Rva0018123CGet@@YAHXZ @ 0x0018123c (6B): returns 0x00000001.
// Conditional-skip target (cmp / jne +6). Opaque address-derived name.
int Rva0018123CGet(void)
{
	return 0x00000001;
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

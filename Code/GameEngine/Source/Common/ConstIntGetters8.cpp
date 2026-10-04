// Cold-slice B8-imm32 const-int returners (twin-free TU).
//
// Same 6-byte shape as ConstIntGetters7.cpp (mov eax,<IMM32> / ret) for
// bodies in regions siblings have not touched. Each is an unclaimed leaf, so
// the opaque address-derived name witnesses only the address and the returned
// constant. Kept in a fresh TU to avoid contending with hot getter files.
// No // cl: line (defaults match the frameless 6-byte shape).

// ?Rva000310ACGet@@YAHXZ @ 0x000310ac (6B): returns 0x00000001.
// Branch target (loopne / cmp al,6 / jne +6). Opaque address-derived name.
int Rva000310ACGet(void)
{
	return 0x00000001;
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



// ?Rva0018123CGet@@YAHXZ @ 0x0018123c (6B): returns 0x00000001.
// Conditional-skip target (cmp / jne +6). Opaque address-derived name.
int Rva0018123CGet(void)
{
	return 0x00000001;
}

// Cold-slice B8-imm32 const-int returners (twin-free TU).
//
// Same 6-byte shape as ConstIntGetters8.cpp (mov eax,<IMM32> / ret).
// Every body below is strict-clean: previous byte is a ret (C3),
// no branch targets the B8 in the 16B window, and the next bytes open
// a new function. Opaque address-derived names witness only the address
// and the returned constant. Fresh TU to avoid hot-file contention.
// No // cl: line (defaults match the frameless 6-byte shape).

// ?Rva00309E2AGet@@YAHXZ @ 0x00309e2a (6B): returns 0x00c084c0.
// Third of a mov-ret triple with rowed 0x00309e1e/0x00309e24.
// Opaque address-derived name.
int Rva00309E2AGet(void)
{
	return 0x00c084c0;
}

// ?Rva0031A9ECGet@@YAHXZ @ 0x0031a9ec (6B): returns 0x00c38dd0.
// Follows a ret (xor/cmp/sete/ret). Next opens a new function.
// Opaque address-derived name.
int Rva0031A9ECGet(void)
{
	return 0x00c38dd0;
}

// ?Rva00328A5FGet@@YAHXZ @ 0x00328a5f (6B): returns 0x00dff0b8.
// Follows leave/ret; next is a separate global getter.
// Opaque address-derived name.
int Rva00328A5FGet(void)
{
	return 0x00dff0b8;
}

// ?Rva0033A3EEGet@@YAHXZ @ 0x0033a3ee (6B): returns 0x00dbe9b0.
// Follows leave/ret; next opens a new function.
// Opaque address-derived name.
int Rva0033A3EEGet(void)
{
	return 0x00dbe9b0;
}

// ?Rva0033A43EGet@@YAHXZ @ 0x0033a43e (6B): returns 0x00dbecd8.
// Follows a movsx/ret tiny getter; next is a movzx/ret getter.
// Opaque address-derived name.
int Rva0033A43EGet(void)
{
	return 0x00dbecd8;
}

// ?Rva00531295Get@@YAHXZ @ 0x00531295 (6B): returns -666 (0xfffffd66).
// Follows and/ret; next opens a switch-dispatch function.
// Opaque address-derived name.
int Rva00531295Get(void)
{
	return -666;
}

// The members of the ConstIntGetters7.cpp family whose constant is an image address
// no unit defines yet, split out so the rest of the family links; each moves
// back once its target has a definition to name.
//
// Cold-slice B8-imm32 const-int returners (twin-free TU).
//
// Same 6-byte shape as ConstIntGetters6.cpp (mov eax,<IMM32> / ret) for
// bodies in regions siblings have not touched. Each is an unclaimed leaf, so
// the opaque address-derived name witnesses only the address and the returned
// constant. Kept in a fresh TU to avoid contending with hot getter files.
// No // cl: line (defaults match the frameless 6-byte shape).

// ?Rva0052349BGet@@YAHXZ @ 0x0052349b (6B): returns 0x00c622e4.
// Conditional-skip target (jne lands here); first of three 6B getters.
// Opaque address-derived name.
int Rva0052349BGet(void)
{
	return (int)"GUI:PlayerAlive";
}

// ?Rva005234A1Get@@YAHXZ @ 0x005234a1 (6B): returns 0x00c622c0.
// Abuts the 0x0052349b getter above. Opaque address-derived name.
int Rva005234A1Get(void)
{
	return (int)"GUI:PlayerDead";
}

// ?Rva005234A7Get@@YAHXZ @ 0x005234a7 (6B): returns 0x00c62298.
// Abuts the 0x005234a1 getter above. Opaque address-derived name.
int Rva005234A7Get(void)
{
	return (int)"GUI:PlayerGone";
}

// Four 559F57/5D/72/78 return arms were retired: they belong to the
// complete 27-byte selectors at 559F48 and 559F63. Internal case branches
// target them; no independent function entry is proved.

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

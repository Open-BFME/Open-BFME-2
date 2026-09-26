// Cold-slice B8-imm32 const-int returners without vtable carriage (twin-free TU).
//
// Same 6-byte shape as ConstIntGetters4.cpp (mov eax,<IMM32> / ret) but for
// bodies with no .rdata vtable slot, no direct callers and no branch sources:
// each follows a ret-imm (C2-04-00) and is an unclaimed leaf, so the opaque
// address-derived name witnesses only the address and the returned constant.
// Kept in a fresh TU so this batch does not contend with the hot
// ConstIntGetters4 appends on origin/master. No // cl: line (defaults match
// the frameless 6-byte shape).

// ?Rva0004546DGet@@YAHXZ @ 0x0004546d (6B): returns 0x00dbaa98.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0004546DGet(void)
{
	return 0x00dbaa98;
}

// ?Rva00062A52Get@@YAHXZ @ 0x00062a52 (6B): returns 0x0000ffff.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00062A52Get(void)
{
	return 0x0000ffff;
}

// ?Rva001DB686Get@@YAHXZ @ 0x001db686 (6B): returns 0x00c0cd88.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva001DB686Get(void)
{
	return 0x00c0cd88;
}

// ?Rva001DFAA0Get@@YAHXZ @ 0x001dfaa0 (6B): returns 0x00bdc720.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva001DFAA0Get(void)
{
	return 0x00bdc720;
}

// ?Rva001EF361Get@@YAHXZ @ 0x001ef361 (6B): returns 0x00c18fb0.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva001EF361Get(void)
{
	return 0x00c18fb0;
}

// ?Rva0026EDB1Get@@YAHXZ @ 0x0026edb1 (6B): returns 0x00bfa6e8.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0026EDB1Get(void)
{
	return 0x00bfa6e8;
}

// ?Rva0028C77DGet@@YAHXZ @ 0x0028c77d (6B): returns 0x0000009a.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0028C77DGet(void)
{
	return 0x0000009a;
}

// ?Rva002A8922Get@@YAHXZ @ 0x002a8922 (6B): returns 0x00bfd804.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002A8922Get(void)
{
	return 0x00bfd804;
}

// ?Rva003B0FA0Get@@YAHXZ @ 0x003b0fa0 (6B): returns 0x00dc0e78.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva003B0FA0Get(void)
{
	return 0x00dc0e78;
}

// ?Rva003EE72EGet@@YAHXZ @ 0x003ee72e (6B): returns 0x00dc14c8.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva003EE72EGet(void)
{
	return 0x00dc14c8;
}

// ?Rva0041E6B8Get@@YAHXZ @ 0x0041e6b8 (6B): returns 0x00c3af18.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0041E6B8Get(void)
{
	return 0x00c3af18;
}

// ?Rva0041F310Get@@YAHXZ @ 0x0041f310 (6B): returns 0x00c3b050.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0041F310Get(void)
{
	return 0x00c3b050;
}

// ?Rva00420965Get@@YAHXZ @ 0x00420965 (6B): returns 0x00c3bc20.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00420965Get(void)
{
	return 0x00c3bc20;
}

// ?Rva004CFAE5Get@@YAHXZ @ 0x004cfae5 (6B): returns 0x00010000.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004CFAE5Get(void)
{
	return 0x00010000;
}

// ?Rva004FF2EEGet@@YAHXZ @ 0x004ff2ee (6B): returns 0x00e04544.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004FF2EEGet(void)
{
	return 0x00e04544;
}

// ?Rva00534B22Get@@YAHXZ @ 0x00534b22 (6B): returns 0x00c68ae8.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00534B22Get(void)
{
	return 0x00c68ae8;
}

// ?Rva002A893FGet@@YAHXZ @ 0x002a893f (6B): returns 0x00bfd85c.
// Follows a near ret (BrutalDifficultyCheats ctor tail), no .rdata vtable
// slot, no direct callers, no branch sources. Opaque address-derived name.
// The constant is the BrutalDifficultyCheats sub-table also pushed as an
// immediate by the rowed parser at 0x002a898a.
int Rva002A893FGet(void)
{
	return 0x00bfd85c;
}

// ?Rva002A88BBGet@@YAHXZ @ 0x002a88bb (6B): returns 0x00bfd768.
// Abuts the probability parser at 0x002a8845 (ends +118) and a twin getter
// below. Opaque address-derived name. The constant is the DifficultyTuning
// sub-table also pushed as an immediate by the rowed parser at 0x002a89d2.
int Rva002A88BBGet(void)
{
	return 0x00bfd768;
}

// ?Rva002A88C1Get@@YAHXZ @ 0x002a88c1 (6B): returns 0x00bfd7c0.
// Abuts the twin getter above and the CombatChainEntry ctor at 0x002a88c7.
// Opaque address-derived name. The constant is a sub-table VA in the same
// 0xBFD7xx family as the tuning table.
int Rva002A88C1Get(void)
{
	return 0x00bfd7c0;
}

// ?Rva00007450Get@@YAHXZ @ 0x00007450 (6B): returns -2.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00007450Get(void)
{
	return -2;
}

// ?Rva00016AC0Get@@YAHXZ @ 0x00016ac0 (6B): returns 0x00bbbddc.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00016AC0Get(void)
{
	return 0x00bbbddc;
}

// ?Rva00018080Get@@YAHXZ @ 0x00018080 (6B): returns INT_MIN.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00018080Get(void)
{
	return (int)0x80000000;
}

// ?Rva00018610Get@@YAHXZ @ 0x00018610 (6B): returns INT_MAX.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00018610Get(void)
{
	return 0x7fffffff;
}

// ?Rva00019B50Get@@YAHXZ @ 0x00019b50 (6B): returns 0x7ffffffe.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00019B50Get(void)
{
	return 0x7ffffffe;
}

// ?Rva0002BBC3Get@@YAHXZ @ 0x0002bbc3 (6B): returns 0x00ddf5b8.
// Follows a ret tail, next function starts with mov ecx plus call.
// No direct callers. Opaque address-derived name.
int Rva0002BBC3Get(void)
{
	return 0x00ddf5b8;
}

// ?Rva00030A40Get@@YAHXZ @ 0x00030a40 (6B): returns 16.
// Follows a ret tail, int3-padded after. No direct callers.
// Opaque address-derived name.
int Rva00030A40Get(void)
{
	return 16;
}

// ?Rva00030F58Get@@YAHXZ @ 0x00030f58 (6B): returns 126.
// Follows a ret tail. No direct callers. Opaque address-derived name.
int Rva00030F58Get(void)
{
	return 126;
}

// ?Rva000454CEGet@@YAHXZ @ 0x000454ce (6B): returns 0x00da5f30.
// Follows a tiny mov-al returner. No direct callers.
// Opaque address-derived name.
int Rva000454CEGet(void)
{
	return 0x00da5f30;
}

// ?Rva00051EA9Get@@YAHXZ @ 0x00051ea9 (6B): returns 1000000.
// Follows a ret tail. No direct callers. Opaque address-derived name.
int Rva00051EA9Get(void)
{
	return 1000000;
}

// ?Rva0011C460Get@@YAHXZ @ 0x0011c460 (6B): returns 0x00dec5e8.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva0011C460Get(void)
{
	return 0x00dec5e8;
}

// ?Rva002A8A0FGet@@YAHXZ @ 0x002a8a0f (6B): returns 0x00bfda50.
// Follows the BrutalDifficultyCheats parser tail. No direct callers.
// Opaque address-derived name. The constant is the table at 0x7fda50.
int Rva002A8A0FGet(void)
{
	return 0x00bfda50;
}

// ?Rva0008514EGet@@YAHXZ @ 0x0008514e (6B): returns 0x00e00944.
// Follows a ret tail. No direct callers. Opaque address-derived name.
int Rva0008514EGet(void)
{
	return 0x00e00944;
}

// ?Rva00176E30Get@@YAHXZ @ 0x00176e30 (6B): returns 0x00bd4e3c.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00176E30Get(void)
{
	return 0x00bd4e3c;
}

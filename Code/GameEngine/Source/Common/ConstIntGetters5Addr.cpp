// The members of the ConstIntGetters5.cpp family whose constant is an image address
// no unit defines yet, split out so the rest of the family links; each moves
// back once its target has a definition to name.
//
// Cold-slice B8-imm32 const-int returners without vtable carriage (twin-free TU).
//
// Same 6-byte shape as ConstIntGetters4.cpp (mov eax,<IMM32> / ret) but for
// bodies with no .rdata vtable slot, no direct callers and no branch sources:
// each follows a ret-imm (C2-04-00) and is an unclaimed leaf, so the opaque
// address-derived name witnesses only the address and the returned constant.
// Kept in a fresh TU so this batch does not contend with the hot
// ConstIntGetters4 appends on origin/master. No // cl: line (defaults match
// the frameless 6-byte shape).


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

// ?Rva00016AC0Get@@YAHXZ @ 0x00016ac0 (6B): returns 0x00bbbddc.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00016AC0Get(void)
{
	return (int)" ";
}

// ?Rva0002BBC3Get@@YAHXZ @ 0x0002bbc3 (6B): returns 0x00ddf5b8.
// Follows a ret tail, next function starts with mov ecx plus call.
// No direct callers. Opaque address-derived name.
int Rva0002BBC3Get(void)
{
	return 0x00ddf5b8;
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

// ?Rva001DAEB2Get@@YAHXZ @ 0x001daeb2 (6B): returns 0x00c03a28.
// Preceded by int3 padding. No direct callers. Opaque address-derived name.
int Rva001DAEB2Get(void)
{
	return 0x00c03a28;
}

// ?Rva001DAF77Get@@YAHXZ @ 0x001daf77 (6B): returns 0x00c15468.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva001DAF77Get(void)
{
	return 0x00c15468;
}

// ?Rva001DBA71Get@@YAHXZ @ 0x001dba71 (6B): returns 0x00bdbbcc.
// Follows an al-returner tail. No direct callers. Opaque address-derived
// name.
int Rva001DBA71Get(void)
{
	return 0x00bdbbcc;
}

// ?Rva001DCC3FGet@@YAHXZ @ 0x001dcc3f (6B): returns 0x00bdbe10.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva001DCC3FGet(void)
{
	return 0x00bdbe10;
}

// ?Rva001DFAB9Get@@YAHXZ @ 0x001dfab9 (6B): returns 0x00bdca18.
// Follows a setne-al returner tail. No direct callers. Opaque
// address-derived name.
int Rva001DFAB9Get(void)
{
	return 0x00bdca18;
}

// ?Rva001E392EGet@@YAHXZ @ 0x001e392e (6B): returns 0x00bde2f8.
// Follows a store plus pop plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva001E392EGet(void)
{
	return 0x00bde2f8;
}

// ?Rva0020049BGet@@YAHXZ @ 0x0020049b (6B): returns 0x00be29ec.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0020049BGet(void)
{
	return 0x00be29ec;
}

// ?Rva002009F5Get@@YAHXZ @ 0x002009f5 (6B): returns 0x00c0c3a8.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva002009F5Get(void)
{
	return 0x00c0c3a8;
}

// ?Rva00200BB4Get@@YAHXZ @ 0x00200bb4 (6B): returns 0x00c07fe0.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00200BB4Get(void)
{
	return 0x00c07fe0;
}

// ?Rva00201992Get@@YAHXZ @ 0x00201992 (6B): returns 0x00be3098.
// Preceded by int3 padding. No direct callers. Opaque address-derived name.
int Rva00201992Get(void)
{
	return 0x00be3098;
}

// ?Rva0020E2F2Get@@YAHXZ @ 0x0020e2f2 (6B): returns 0x00be4120.
// Follows an al-returner tail. No direct callers. Opaque
// address-derived name.
int Rva0020E2F2Get(void)
{
	return 0x00be4120;
}

// ?Rva00215C48Get@@YAHXZ @ 0x00215c48 (6B): returns 0x00c387c0.
// Follows a call plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00215C48Get(void)
{
	return 0x00c387c0;
}

// ?Rva00215C4EGet@@YAHXZ @ 0x00215c4e (6B): returns 0x00c38760.
// Abuts the twin getter above. No direct callers. Opaque
// address-derived name.
int Rva00215C4EGet(void)
{
	return 0x00c38760;
}


// ?Rva002C8E5AGet@@YAHXZ @ 0x002c8e5a (6B): returns 0x00c00b48.
// Follows an and-store plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva002C8E5AGet(void)
{
	return 0x00c00b48;
}

// ?Rva002D6AEFGet@@YAHXZ @ 0x002d6aef (6B): returns 0x00c031f0.
// Follows a word-load plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva002D6AEFGet(void)
{
	return 0x00c031f0;
}

// ?Rva00309E1EGet@@YAHXZ @ 0x00309e1e (6B): returns 0x00c08350.
// Follows byte-store plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00309E1EGet(void)
{
	return 0x00c08350;
}

// ?Rva00309E24Get@@YAHXZ @ 0x00309e24 (6B): returns 0x00c08400.
// Abuts the twin getter above. No direct callers. Opaque
// address-derived name.
int Rva00309E24Get(void)
{
	return 0x00c08400;
}

// ?Rva0033A507Get@@YAHXZ @ 0x0033a507 (6B): returns 0x00c1045c.
// Follows an or-store plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0033A507Get(void)
{
	return 0x00c1045c;
}

// ?Rva0033A7BBGet@@YAHXZ @ 0x0033a7bb (6B): returns 0x00dc85c4.
// Follows a call plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0033A7BBGet(void)
{
	return 0x00dc85c4;
}

// ?Rva0035C959Get@@YAHXZ @ 0x0035c959 (6B): returns 0x00c162a0.
// Follows a pop plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0035C959Get(void)
{
	return 0x00c162a0;
}

// ?Rva0039009BGet@@YAHXZ @ 0x0039009b (6B): returns 0x00790095.
// Follows a mov plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0039009BGet(void)
{
	return 0x00790095;
}




// ?Rva0040C344Get@@YAHXZ @ 0x0040c344 (6B): returns 0x00c18d18.
// Follows a call plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0040C344Get(void)
{
	return 0x00c18d18;
}

// ?Rva00417AE3Get@@YAHXZ @ 0x00417ae3 (6B): returns 0x00c3a658.
// Follows an SSE-store plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00417AE3Get(void)
{
	return 0x00c3a658;
}

// ?Rva00418060Get@@YAHXZ @ 0x00418060 (6B): returns 0x00c3a730.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00418060Get(void)
{
	return 0x00c3a730;
}

// ?Rva004186DAGet@@YAHXZ @ 0x004186da (6B): returns 0x00c3a8b0.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva004186DAGet(void)
{
	return 0x00c3a8b0;
}

// ?Rva0041901DGet@@YAHXZ @ 0x0041901d (6B): returns 0x00c3a9a8.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0041901DGet(void)
{
	return 0x00c3a9a8;
}

// ?Rva00419663Get@@YAHXZ @ 0x00419663 (6B): returns 0x00c3aac8.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00419663Get(void)
{
	return 0x00c3aac8;
}

// ?Rva0041F71AGet@@YAHXZ @ 0x0041f71a (6B): returns 0x00c3b5e8.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0041F71AGet(void)
{
	return 0x00c3b5e8;
}

// ?Rva00509DA5Get@@YAHXZ @ 0x00509da5 (6B): returns 0x00c64810.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00509DA5Get(void)
{
	return 0x00c64810;
}


// ?Rva005B729FGet@@YAHXZ @ 0x005b729f (6B): returns 0x00c737e8.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva005B729FGet(void)
{
	return 0x00c737e8;
}

// ?Rva00611030Get@@YAHXZ @ 0x00611030 (6B): returns 0x00e08c58.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00611030Get(void)
{
	return 0x00e08c58;
}

// ?Rva006882D0Get@@YAHXZ @ 0x006882d0 (6B): returns 0x00ce43b0.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva006882D0Get(void)
{
	return 0x00ce43b0;
}

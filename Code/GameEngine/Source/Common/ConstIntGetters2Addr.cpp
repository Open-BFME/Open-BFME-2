// The members of the ConstIntGetters2.cpp family whose constant is an image address
// no unit defines yet, split out so the rest of the family links; each moves
// back once its target has a definition to name.
//
// Cold-slice B8-imm32 const-int returners (twin-free TU).
//
// Same shape as ConstIntGetters.cpp (mov eax,<IMM32> / ret, 6B) but kept in
// a separate TU so this lane does not contend with the hot ConstIntGetters
// appends on origin/master. Rows are opaque address-derived names: each
// body is a CC-island or ret-prev leaf carried by .rdata vtable slots with
// no direct callers and no branch sources, so no class identity is
// witnessed. No // cl: line (defaults match the frameless 6-byte shape).

// ?Rva002BE8CEGet@@YAHXZ @ 0x002BE8CE (6B): returns 0x00BFE4D4.
// Follows a leave/ret-4 (prev C2-04-00), carried by 2 .rdata vtable slots
// (0x7C89D0 in the 0x49xxxx family, 0x7FE510 beside the 0x4B3FD0 slot),
// no direct callers, no branch sources. The imm falls in the .rdata VA
// window so it is kept as a plain int literal (no DIR32 for literals).
// Opaque address-derived name.
int Rva002BE8CEGet(void)
{
	return 0x00BFE4D4;
}

// ?Rva0009FDF5Get@@YAHXZ @ 0x0009FDF5 (6B): returns 0x0048F925.
// Follows a cmov-style ret (prev C3), carried by 1 .rdata slot (0x7C8CB0)
// in a vtable family shared with Rva0009FDFBGet (identical neighbours,
// parallel tables 44B apart), no direct callers, no branch sources.
// Opaque address-derived name.
int Rva0009FDF5Get(void)
{
	return 0x0048F925;
}

// ?Rva0009FDFBGet@@YAHXZ @ 0x0009FDFB (6B): returns 0x0048F95F.
// Immediately follows Rva0009FDF5Get (prev is its C3), carried by 1 .rdata
// slot (0x7C8CDC) in the parallel vtable, no direct callers, no branch
// sources. Opaque address-derived name.
int Rva0009FDFBGet(void)
{
	return 0x0048F95F;
}

// ?Rva00180778Get@@YAHXZ @ 0x00180778 (6B): returns 0x00424F58.
// Follows a leave/ret (prev C9-C3), carried by 1 .rdata slot (0x7D5044)
// in the 0x180xxx vtable family (prefix 530FCE/A1EE20/A1EE50, suffix
// 6A79A1/4B3FD0), no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00180778Get(void)
{
	return 0x00424F58;
}

// ?Rva00180E60Get@@YAHXZ @ 0x00180E60 (6B): returns 0x00BBE8D4.
// CC-island (16xCC before and after), carried by 1 .rdata slot (0x7D5090)
// in the 0x180xxx vtable family, no direct callers, no branch sources.
// The imm falls in the .rdata VA window so it is kept as a plain int
// literal (no DIR32 for literals). Opaque address-derived name.
int Rva00180E60Get(void)
{
	return 0x00BBE8D4;
}

// ?Rva000A08F1Get@@YAHXZ @ 0x000A08F1 (6B): returns 0x0048F6E1.
// Follows a pop/ret-4 (prev C2-04-00), carried by 1 .rdata slot (0x7C8CC8)
// in a vtable family shared with Rva000A08F7Get (identical neighbours,
// parallel tables 44B apart), no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A08F1Get(void)
{
	return 0x0048F6E1;
}

// ?Rva000A08F7Get@@YAHXZ @ 0x000A08F7 (6B): returns 0x0048F71B.
// Immediately follows Rva000A08F1Get (prev is its C3), carried by 1 .rdata
// slot (0x7C8CF4) in the parallel vtable, no direct callers, no branch
// sources. Opaque address-derived name.
int Rva000A08F7Get(void)
{
	return 0x0048F71B;
}

// ?Rva000A0D52Get@@YAHXZ @ 0x000A0D52 (6B): returns 0x0048FAF5.
// Follows a pop/ret-4 (prev C2-04-00), carried by 1 .rdata slot (0x7C8D90)
// in a vtable family shared with Rva000A0D58Get (identical neighbours,
// parallel tables 44B apart), no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A0D52Get(void)
{
	return 0x0048FAF5;
}

// ?Rva000A0D58Get@@YAHXZ @ 0x000A0D58 (6B): returns 0x0048FB2F.
// Immediately follows Rva000A0D52Get (prev is its C3), carried by 1 .rdata
// slot in the parallel vtable, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A0D58Get(void)
{
	return 0x0048FB2F;
}

// ?Rva000A135EGet@@YAHXZ @ 0x000A135E (6B): returns 0x0048FB69.
// Follows a pop/ret-4 (prev C2-04-00), carried by 1 .rdata slot
// in a vtable family shared with Rva000A1364Get (identical neighbours,
// parallel tables 44B apart), no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A135EGet(void)
{
	return 0x0048FB69;
}

// ?Rva000A1364Get@@YAHXZ @ 0x000A1364 (6B): returns 0x0048FBA3.
// Immediately follows Rva000A135EGet (prev is its C3), carried by 1 .rdata
// slot in the parallel vtable, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A1364Get(void)
{
	return 0x0048FBA3;
}

// ?Rva000A165EGet@@YAHXZ @ 0x000A165E (6B): returns 0x0048FBDD.
// Follows a pop/ret-4 (prev C2-04-00), carried by 1 .rdata slot
// in a vtable family shared with Rva000A1664Get (identical neighbours,
// parallel tables 44B apart), no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A165EGet(void)
{
	return 0x0048FBDD;
}

// ?Rva000A1664Get@@YAHXZ @ 0x000A1664 (6B): returns 0x0048FC17.
// Immediately follows Rva000A165EGet (prev is its C3), carried by 1 .rdata
// slot in the parallel vtable, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A1664Get(void)
{
	return 0x0048FC17;
}

// ?Rva000A2197Get@@YAHXZ @ 0x000A2197 (6B): returns 0x0048FA81.
// Follows a pop/ret-4 (prev C2-04-00), carried by 1 .rdata slot
// in a vtable family shared with Rva000A219DGet (identical neighbours,
// parallel tables 44B apart), no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A2197Get(void)
{
	return 0x0048FA81;
}

// ?Rva000A219DGet@@YAHXZ @ 0x000A219D (6B): returns 0x0048FABB.
// Immediately follows Rva000A2197Get (prev is its C3), carried by 1 .rdata
// slot in the parallel vtable, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A219DGet(void)
{
	return 0x0048FABB;
}

// ?Rva000A2727Get@@YAHXZ @ 0x000A2727 (6B): returns 0x0048F999.
// Follows a pop/ret-4 (prev C2-04-00), carried by 1 .rdata slot
// in a vtable family shared with Rva000A272DGet (identical neighbours,
// parallel tables 44B apart), no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A2727Get(void)
{
	return 0x0048F999;
}

// ?Rva000A272DGet@@YAHXZ @ 0x000A272D (6B): returns 0x0048F9D3.
// Immediately follows Rva000A2727Get (prev is its C3), carried by 1 .rdata
// slot in the parallel vtable, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A272DGet(void)
{
	return 0x0048F9D3;
}

// ?Rva000A2733Get@@YAHXZ @ 0x000A2733 (6B): returns 0x0048FA0D.
// Immediately follows Rva000A272DGet (prev is its C3), carried by 1 .rdata
// slot in the parallel vtable, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A2733Get(void)
{
	return 0x0048FA0D;
}

// ?Rva000A2739Get@@YAHXZ @ 0x000A2739 (6B): returns 0x0048FA47.
// Immediately follows Rva000A2733Get (prev is its C3), carried by 1 .rdata
// slot in the parallel vtable, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A2739Get(void)
{
	return 0x0048FA47;
}

// ?Rva000A3367Get@@YAHXZ @ 0x000A3367 (6B): returns 0x0048F8B1.
// Follows a pop/ret-4 (prev C2-04-00), carried by 1 .rdata slot
// in a vtable family shared with Rva000A336DGet (identical neighbours,
// parallel tables 44B apart), no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A3367Get(void)
{
	return 0x0048F8B1;
}

// ?Rva000A336DGet@@YAHXZ @ 0x000A336D (6B): returns 0x0048F8EB.
// Immediately follows Rva000A3367Get (prev is its C3), carried by 1 .rdata
// slot in the parallel vtable, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A336DGet(void)
{
	return 0x0048F8EB;
}

// ?Rva000A3E43Get@@YAHXZ @ 0x000A3E43 (6B): returns 0x0048F7C9.
// Follows a pop/ret-4 (prev C2-04-00), carried by 1 .rdata slot
// in a vtable family shared with Rva000A3E49Get (identical neighbours,
// parallel tables 44B apart), no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A3E43Get(void)
{
	return 0x0048F7C9;
}

// ?Rva000A3E49Get@@YAHXZ @ 0x000A3E49 (6B): returns 0x0048F803.
// Immediately follows Rva000A3E43Get (prev is its C3), carried by 1 .rdata
// slot in the parallel vtable, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A3E49Get(void)
{
	return 0x0048F803;
}

// ?Rva000A43BCGet@@YAHXZ @ 0x000A43BC (6B): returns 0x0048F83D.
// Follows a pop/ret-4 (prev C2-04-00), carried by 1 .rdata slot
// in a vtable family shared with Rva000A43C2Get (identical neighbours,
// parallel tables 44B apart), no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A43BCGet(void)
{
	return 0x0048F83D;
}

// ?Rva000A43C2Get@@YAHXZ @ 0x000A43C2 (6B): returns 0x0048F877.
// Immediately follows Rva000A43BCGet (prev is its C3), carried by 1 .rdata
// slot in the parallel vtable, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A43C2Get(void)
{
	return 0x0048F877;
}

// ?Rva000A52A2Get@@YAHXZ @ 0x000A52A2 (6B): returns 0x0048F755.
// Follows a leave/ret (prev C9-C3), carried by 1 .rdata slot
// in a vtable family shared with Rva000A52A8Get (identical neighbours,
// parallel tables 44B apart), no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A52A2Get(void)
{
	return 0x0048F755;
}

// ?Rva000A52A8Get@@YAHXZ @ 0x000A52A8 (6B): returns 0x0048F78F.
// Immediately follows Rva000A52A2Get (prev is its C3), carried by 1 .rdata
// slot in the parallel vtable, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000A52A8Get(void)
{
	return 0x0048F78F;
}

// ?Rva002376C6Get@@YAHXZ @ 0x002376C6 (6B): returns 0x00BE8520.
// Follows a leave/ret (prev C9-C3), carried by 1 .rdata slot (0x7ED1DC)
// in the 0x4B3FD0 vtable family, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva002376C6Get(void)
{
	return 0x00BE8520;
}

// ?Rva00285745Get@@YAHXZ @ 0x00285745 (6B): returns 0x00BFB6C8.
// Follows a pop/ret (prev 5E-C3), carried by 1 .rdata slot (0x7FB6F8)
// in the 0x4B3FD0 vtable family, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00285745Get(void)
{
	return 0x00BFB6C8;
}

// ?Rva0039B81DGet@@YAHXZ @ 0x0039B81D (6B): returns 0x00C1AD7C.
// Follows a ret (prev C3), carried by 1 .rdata slot (0x81AD74)
// in the 0x4B3FD0 vtable family, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva0039B81DGet(void)
{
	return 0x00C1AD7C;
}

// ?Rva004B29B8Get@@YAHXZ @ 0x004B29B8 (6B): returns 0x00BF4E80.
// Follows a pop/ret-8 (prev C2-08-00), immediately followed by the claimed
// ??1Rva004B29BE dtor at +6 (perfect boundaries both sides), carried by
// 1 .rdata slot, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva004B29B8Get(void)
{
	return 0x00BF4E80;
}

// ?Rva004C07ABGet@@YAHXZ @ 0x004C07AB (6B): returns 0x00BF4894.
// Follows a pop/ret-8 (prev C2-08-00), immediately followed by the claimed
// ??1Rva004C07B1 dtor at +6 (perfect boundaries both sides), carried by
// 1 .rdata slot, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva004C07ABGet(void)
{
	return 0x00BF4894;
}

// ?Rva0033F3E9Get@@YAHXZ @ 0x0033F3E9 (6B): returns 0x00C1104C.
// Follows a ret-12 (prev C2-0C-00), carried by 1 .rdata slot, no direct
// callers, no branch sources. Opaque address-derived name.
int Rva0033F3E9Get(void)
{
	return 0x00C1104C;
}

// ?Rva0033F414Get@@YAHXZ @ 0x0033F414 (6B): returns 0x00C110AC.
// Follows a pop/ret-4 (prev C2-04-00), carried by 1 .rdata slot, no direct
// callers, no branch sources. Opaque address-derived name.
int Rva0033F414Get(void)
{
	return 0x00C110AC;
}

// ?Rva0033F437Get@@YAHXZ @ 0x0033F437 (6B): returns 0x00C11114.
// Follows a pop/ret-4 (prev C2-04-00), carried by 1 .rdata slot, no direct
// callers, no branch sources. Opaque address-derived name.
int Rva0033F437Get(void)
{
	return 0x00C11114;
}

// ?Rva0033F45AGet@@YAHXZ @ 0x0033F45A (6B): returns 0x00C11164.
// Follows a pop/ret-4 (prev C2-04-00), carried by 1 .rdata slot, no direct
// callers, no branch sources. Opaque address-derived name.
int Rva0033F45AGet(void)
{
	return 0x00C11164;
}

// ?Rva0033F47DGet@@YAHXZ @ 0x0033F47D (6B): returns 0x00C111CC.
// Follows a pop/ret-4 (prev C2-04-00), carried by 1 .rdata slot, no direct
// callers, no branch sources. Opaque address-derived name.
int Rva0033F47DGet(void)
{
	return 0x00C111CC;
}

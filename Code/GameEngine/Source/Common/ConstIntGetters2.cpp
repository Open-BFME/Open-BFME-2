// Cold-slice B8-imm32 const-int returners (twin-free TU).
//
// Same shape as ConstIntGetters.cpp (mov eax,<IMM32> / ret, 6B) but kept in
// a separate TU so this lane does not contend with the hot ConstIntGetters
// appends on origin/master. Rows are opaque address-derived names: each
// body is a CC-island or ret-prev leaf carried by .rdata vtable slots with
// no direct callers and no branch sources, so no class identity is
// witnessed. No // cl: line (defaults match the frameless 6-byte shape).

// ?Rva00742550Get@@YAHXZ @ 0x00742550 (6B): returns 0x1C (28). CC-island
// (16xCC before, 20xCC after), carried by 2 .rdata slots (0x7D3D4C and
// 0x8F1694, same vtable family suffix 4D43D0/4D43D0/46CE6B/87A69C),
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00742550Get(void)
{
	return 0x1C;
}

// ?Rva0018026EGet@@YAHXZ @ 0x0018026E (6B): returns 0x4D455348.
// Follows a leave/ret (prev C9-C3), carried by 1 .rdata slot (0x7D4FC4)
// in a vtable family shared with Rva00180581Get (identical neighbours),
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0018026EGet(void)
{
	return 0x4D455348;
}

// ?Rva00180581Get@@YAHXZ @ 0x00180581 (6B): returns 0x50415254.
// Follows a leave/ret (prev C9-C3), carried by 1 .rdata slot (0x7D5004)
// in the parallel vtable to Rva0018026EGet, no direct callers, no branch
// sources. Opaque address-derived name.
int Rva00180581Get(void)
{
	return 0x50415254;
}

// ?Rva00180AA0Get@@YAHXZ @ 0x00180AA0 (6B): returns 0x41474752.
// Follows a leave/ret (prev C9-C3), carried by 1 .rdata slot (0x7D5084)
// in the 0x180xxx vtable family, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00180AA0Get(void)
{
	return 0x41474752;
}

// ?Rva00180E70Get@@YAHXZ @ 0x00180E70 (6B): returns 0x4E554C4C.
// CC-island (16xCC before and after), carried by 1 .rdata slot (0x7D50C4)
// in the 0x180xxx vtable family, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00180E70Get(void)
{
	return 0x4E554C4C;
}

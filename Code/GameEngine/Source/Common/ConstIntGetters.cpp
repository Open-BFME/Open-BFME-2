// B8-imm32 const-int returners: six-byte free functions with one shape:
//
//     mov eax,<IMM32> / ret
//
// Each stands on a CC-island (int3 before and after) with no Ghidra entry
// (dead emissions) and is carried in several .rdata vtable slots, so the
// address is a genuine shared virtual implementation whose class identity
// is not witnessed anywhere. Rows are named for their own address with the
// proven return value, following Rva0073B660False.cpp and the Disp family
// (address-derived names, identity unrecoverable from 6 bytes).
// No // cl: line (defaults match the frameless 6-byte shape).

extern const int g_emptyFieldParseTable[4];
#pragma comment(linker, "/alternatename:?Rva007E9B70Get@@YAPAURva007E9B70Obj@@XZ=?Rva00656B60Get@@YAHXZ")
#pragma comment(linker, "/alternatename:?Rva007FBC00@@YAIXZ=?Rva00668100Get@@YAHXZ")
#pragma comment(linker, "/alternatename:?Rva007FD060@@YAIXZ=?Rva00669530Get@@YAHXZ")
#pragma comment(linker, "/alternatename:?Rva007F8FB0@@YAIXZ=?Rva006655E0Get@@YAHXZ")
#pragma comment(linker, "/alternatename:?opaqueCall@Rva00507552@@SAPAXXZ=?Rva00507552Get@@YAHXZ")
#pragma comment(linker, "/alternatename:?opaqueCall@Rva005088C8@@SAPAXXZ=?Rva005088C8Get@@YAHXZ")

// ?Rva001820A0Get@@YAHXZ @ 0x001820A0 (6B): returns 8. CC-island
// (4xCC before, 8xCC after), 4 vtable refs in the 0x7D49xx-0x7D55xx mapper
// family, no direct callers, no branch sources.
int Rva001820A0Get(void)
{
	return 8;
}

// ?Rva00182D20Get@@YAHXZ @ 0x00182D20 (6B): returns 12. CC-island,
// 5 vtable refs in the same 0x7D3Fxx-0x7D56xx mapper family (each carrying
// it 13 slots after Rva001820A0Get), no direct callers, no branch sources.
int Rva00182D20Get(void)
{
	return 12;
}

// ?Rva0013C650Get@@YAHXZ @ 0x0013C650 (6B): returns 3. CC-island
// (7xCC before, 10xCC after) between the 0x13C630 environment-mapper ctor
// and 0x13C660, carried by 2 .rdata slots (one Vector3Randomizer vtable).
// The value matches CLASSID_SOLIDCYLINDER but the body also sits in an
// unrelated randomizer vtable slot, so the linker folded several const-3
// returners here and no single class identity is witnessed; the row stays
// address-derived. No direct callers, no branch sources.
int Rva0013C650Get(void)
{
	return 3;
}

// ?Rva00250000Get@@YAHXZ @ 0x00250000 (6B): returns 0x81. Follows a
// leave/ret (prev C3) with a larger B8-imm function immediately after,
// 7 .rdata refs across distant tables, no direct callers, no branch
// sources. Opaque address-derived name; the value is a plain integer
// (below any image base), not an address.
int Rva00250000Get(void)
{
	return 0x81;
}

// ?Rva0000C124CGet@@YAHXZ @ 0x0000C124C (6B): returns 0x000186A0.
// Follows sibling B8-6 0xC1246 (ret 0xBC5C20, itself leave/ret-prev) with
// a B8-imm/call function after. 6 .rdata refs, no direct callers, no
// branch sources. Opaque address-derived name.
int Rva0000C124CGet(void)
{
	return 0x000186A0;
}

// 0x0000C1246 is already claimed by twin (?name@Rva000C1246Named in
// W3DDrawNameGetters.cpp, a real string getter). Always grep the ledger
// in canonical 8-digit form before serving (",0x0*<ADDR>,"); add_match
// refusal is the backstop, never the plan.

// ?Rva0013C6C0Get@@YAHXZ @ 0x0013C6C0 (6B): returns 14. CC-island,
// carried at 0x7D31F0 in the same 0x7D31xx family table as Rva0013C650Get
// (10 slots later). 1 .rdata ref, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva0013C6C0Get(void)
{
	return 14;
}

// ?Rva001820B0Get@@YAHXZ @ 0x001820B0 (6B): returns 9. CC-island
// neighbor 16 bytes after Rva001820A0Get (same mapper TU region), 2
// .rdata refs, no direct callers. Opaque address-derived name.
int Rva001820B0Get(void)
{
	return 9;
}

int Rva0056B767Get(void)
{
	return (int)g_emptyFieldParseTable;
}

// ?Rva004A6563Get@@YAHXZ @ 0x004A6563 (6B): returns 0x3FFFFFFF.
// Follows a ret (0x4A6562) with a B8-imm/call function after. Carried by
// 5 .rdata slots, no direct callers, no branch sources. The value is a
// plain small integer, not an address. Opaque address-derived name.
int Rva004A6563Get(void)
{
	return 0x3FFFFFFF;
}

// ?Rva0013D320Get@@YAHXZ @ 0x0013D320 (6B): returns 16. CC-island,
// carried at 0x7D32B0 and 0x7D720C in the 0x7Dxxxx mapper family tables,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0013D320Get(void)
{
	return 16;
}

// ?Rva001874D0Get@@YAHXZ @ 0x001874D0 (6B): returns 22. CC-island,
// carried at 0x7D50DC and 0x7D58B8 in the 0x7Dxxxx mapper family tables,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva001874D0Get(void)
{
	return 22;
}

// ?Rva001A13F0Get@@YAHXZ @ 0x001A13F0 (6B): returns 15. CC-island,
// carried at 0x7D3240 and 0x7D6A04 in the 0x7Dxxxx mapper family tables,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva001A13F0Get(void)
{
	return 15;
}

// ?Rva0013C770Get@@YAHXZ @ 0x0013C770 (6B): returns 17. CC-island
// (8xCC before and after), carried at 0x7D3268 in the 0x7D32xx mapper
// family tables (sibling of Rva0013C650Get/Rva0013C6C0Get), no direct
// callers, no branch sources. Opaque address-derived name.
int Rva0013C770Get(void)
{
	return 17;
}

// ?Rva0013DA70Get@@YAHXZ @ 0x0013DA70 (6B): returns 4. CC-island
// (8xCC before and after), carried at 0x7D32D8 in the 0x7D32xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva0013DA70Get(void)
{
	return 4;
}

// ?Rva00166C10Get@@YAHXZ @ 0x00166C10 (6B): returns 6. Follows a C2-04-00
// ret with CC padding, 8xCC after, carried at 0x7D3FB4 in the 0x7D3Fxx
// mapper family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00166C10Get(void)
{
	return 6;
}

// ?Rva00175750Get@@YAHXZ @ 0x00175750 (6B): returns 26. CC-island
// (8xCC before and after), carried at 0x7D495C in the 0x7D49xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00175750Get(void)
{
	return 26;
}

// ?Rva001758B0Get@@YAHXZ @ 0x001758B0 (6B): returns 27. Follows a C2-04-00
// ret with CC padding, 8xCC after, carried at 0x7D4B6C in the 0x7D4Bxx
// mapper family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva001758B0Get(void)
{
	return 27;
}

// ?Rva00182A20Get@@YAHXZ @ 0x00182A20 (6B): returns 11. CC-island
// (8xCC before and after), carried at 0x7D5660 in the 0x7D56xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00182A20Get(void)
{
	return 11;
}

// ?Rva001830C0Get@@YAHXZ @ 0x001830C0 (6B): returns 13. CC-island
// (8xCC before and after), carried at 0x7D5700 in the 0x7D57xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva001830C0Get(void)
{
	return 13;
}

// ?Rva00183400Get@@YAHXZ @ 0x00183400 (6B): returns 19. CC-island
// (8xCC before and after), carried at 0x7D5740 in the 0x7D57xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00183400Get(void)
{
	return 19;
}

// ?Rva00186790Get@@YAHXZ @ 0x00186790 (6B): returns 18. CC-island
// (8xCC before and after), carried at 0x7D57FC in the 0x7D57xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00186790Get(void)
{
	return 18;
}

// ?Rva001869A0Get@@YAHXZ @ 0x001869A0 (6B): returns 20. CC-island
// (8xCC before and after), carried at 0x7D5824 in the 0x7D58xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva001869A0Get(void)
{
	return 20;
}

// ?Rva00187400Get@@YAHXZ @ 0x00187400 (6B): returns 21. CC-island
// (8xCC before and after), carried at 0x7D5890 in the 0x7D58xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00187400Get(void)
{
	return 21;
}

// ?Rva0019F020Get@@YAHXZ @ 0x0019F020 (6B): returns 25. CC-island
// (8xCC before and after), carried at 0x7D678C in the 0x7D67xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva0019F020Get(void)
{
	return 25;
}

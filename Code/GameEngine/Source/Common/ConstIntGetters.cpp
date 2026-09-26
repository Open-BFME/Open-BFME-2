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

// ?Rva00656B60Get@@YAHXZ @ 0x00656B60 (6B): returns 0x00E09F9C.
// CC-island after a double-ret (xor-eax/ret then ret), 16 direct E8
// callers, Ghidra-6. The lone byte-scan branch hit (js at 0x656B4E) is a
// false decode: capstone shows 0x656B4C is mov [eax],0xCE1078 and the 78
// is its immediate byte. Opaque address-derived name.
int Rva00656B60Get(void)
{
	return 0x00E09F9C;
}

// ?Rva00309E4BGet@@YAHXZ @ 0x00309E4B (6B): returns 0x00DBD7DC.
// Follows the rep-movsd table copier at 0x309E30 (9 dwords
// 0xDBD7B8->0xDBD7DC, ret at 0x309E4A) and returns the filled table's
// address; a larger push-style function starts at 0x309E51. 28 direct E8
// callers, Ghidra-6, no branch sources. The value is carried as a plain
// integer literal (no relocation slot exists here), so no pin is needed.
// Opaque address-derived name.
int Rva00309E4BGet(void)
{
	return 0x00DBD7DC;
}

// ?Rva00309E65Get@@YAHXZ @ 0x00309E65 (6B): returns 0x00DBD860.
// Same copier/getter pair shape as 0x309E4B (rep movsd into 0xDBD860,
// ret at 0x309E64, larger function follows at 0x309E6B). 13 direct E8
// callers, Ghidra-6, no branch sources. Opaque address-derived name.
int Rva00309E65Get(void)
{
	return 0x00DBD860;
}

// ?Rva00309E7FGet@@YAHXZ @ 0x00309E7F (6B): returns 0x00DBD918.
// Third copier/getter pair in the run (rep movsd into 0xDBD918, ret at
// 0x309E7E). 11 direct E8 callers, Ghidra-6, no branch sources.
// Opaque address-derived name.
int Rva00309E7FGet(void)
{
	return 0x00DBD918;
}

// ?Rva004CE52EGet@@YAHXZ @ 0x004CE52E (6B): returns 0x00C5FFA0.
// Follows a neg/sbb/neg boolize tail (ret at 0x4CE52D) with a
// push-style function after. 20 direct E8 callers, Ghidra-6, no branch
// sources. Opaque address-derived name.
int Rva004CE52EGet(void)
{
	return 0x00C5FFA0;
}

// ?Rva00507552Get@@YAHXZ @ 0x00507552 (6B): returns 0x00C63FD0.
// Follows a mov/mov/ret getter (ret at 0x507551) with a frame-style
// function after. 17 direct E8 callers, Ghidra-6, no branch sources.
// Opaque address-derived name.
int Rva00507552Get(void)
{
	return 0x00C63FD0;
}

// ?Rva00510D87Get@@YAHXZ @ 0x00510D87 (6B): returns 0x006D1E55.
// Follows an SEH leave/ret (0x510D85-86) with a sub/cmp-style function
// after. 7 .rdata refs, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00510D87Get(void)
{
	return 0x006D1E55;
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

// ?Rva00336E72Get@@YAHXZ @ 0x00336E72 (6B): returns 0x00736E78.
// Follows a byte-identical dead twin at 0x336E6C (whole-image refs 0;
// the linker kept both copies, only this one is used). 6 .rdata refs,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00336E72Get(void)
{
	return 0x00736E78;
}

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

// ?Rva0056DD52Get@@YAHXZ @ 0x0056DD52 (6B): returns 0x00DC2884. Opens a
// contiguous triple (52/58/5E, each B8-6 back to back) after an indirect
// call + leave/ret. 2 direct E8 callers, Ghidra-6. Opaque name.
int Rva0056DD52Get(void)
{
	return 0x00DC2884;
}

// ?Rva0056DD58Get@@YAHXZ @ 0x0056DD58 (6B): returns 0x00DC2D10. Middle
// of the triple. 4 direct E8 callers, Ghidra-6. Opaque name.
int Rva0056DD58Get(void)
{
	return 0x00DC2D10;
}

// ?Rva0056DD5EGet@@YAHXZ @ 0x0056DD5E (6B): returns 0x00DC4B60. Closes
// the triple (a mov-style function follows). 4 direct E8 callers,
// Ghidra-6. Opaque name.
int Rva0056DD5EGet(void)
{
	return 0x00DC4B60;
}

// ?Rva00381452Get@@YAHXZ @ 0x00381452 (6B): returns 0x00E02310.
// Prev C3 with a frame-style function after. 4 direct E8 callers, no
// Ghidra entry (dead emission), no branch sources. Opaque name.
int Rva00381452Get(void)
{
	return 0x00E02310;
}

// ?Rva003EFE9AGet@@YAHXZ @ 0x003EFE9A (6B): returns 0x00DC34A4.
// Prev C3 with a movzx-style function after. 4 direct E8 callers,
// Ghidra-6, no branch sources. Opaque name.
int Rva003EFE9AGet(void)
{
	return 0x00DC34A4;
}

// ?Rva0056B767Get@@YAHXZ @ 0x0056B767 (6B): returns 0x00C6BB18.
// Prev leave/ret with a test-and-style function after. 3 direct E8
// callers, no Ghidra entry (dead emission), no branch sources.
// Opaque name.
int Rva0056B767Get(void)
{
	return 0x00C6BB18;
}

// ?Rva000A8F58Get@@YAHXZ @ 0x000A8F58 (6B): returns 0x00DB4CF0. Opens a
// contiguous pair (58/F0 then 5E/F8, 8 apart) after a ret-4. Tail-jumped
// from thunk 0x62972, 1 direct E8 caller, Ghidra-6. Opaque name.
int Rva000A8F58Get(void)
{
	return 0x00DB4CF0;
}

// ?Rva000A8F5EGet@@YAHXZ @ 0x000A8F5E (6B): returns 0x00DB4CF8. Closes
// the pair. Tail-jumped from thunk 0x62977, 2 direct E8 callers,
// Ghidra-6. Opaque name.
int Rva000A8F5EGet(void)
{
	return 0x00DB4CF8;
}

// ?Rva00404715Get@@YAHXZ @ 0x00404715 (6B): returns 0x00C38658.
// Prev leave/ret with a push-style function after. 2 direct E8 callers,
// no Ghidra entry (dead emission), no branch sources. Opaque name.
int Rva00404715Get(void)
{
	return 0x00C38658;
}

// ?Rva005088C8Get@@YAHXZ @ 0x005088C8 (6B): returns 0x00C64180.
// Follows a leave/ret (0x5088C6-87) with a push-style function after.
// 1 direct E8 caller (0x50B11D, anchor-decoded as a real call), Ghidra-6,
// no branch sources. Opaque address-derived name.
int Rva005088C8Get(void)
{
	return 0x00C64180;
}

// ?Rva006655E0Get@@YAHXZ @ 0x006655E0 (6B): returns 0x00DD828C.
// CC-island (prev C3 then 6xCC, 10xCC after) between a C7-imm setter and
// the next setter. 1 direct E8 caller (0x6579D3), Ghidra-6, no branch
// sources. Opaque address-derived name.
int Rva006655E0Get(void)
{
	return 0x00DD828C;
}

// ?Rva00668100Get@@YAHXZ @ 0x00668100 (6B): returns 0x00DD8314.
// CC-island (10xCC after) following a call/leave/ret tail. 1 direct E8
// caller (0x657A78), Ghidra-6, no branch sources. Opaque name.
int Rva00668100Get(void)
{
	return 0x00DD8314;
}

// ?Rva00669530Get@@YAHXZ @ 0x00669530 (6B): returns 0x00DD83B4.
// CC-island (10xCC after) following a call/leave/ret tail. 1 direct E8
// caller (0x657B48), Ghidra-6, no branch sources. Opaque name.
int Rva00669530Get(void)
{
	return 0x00DD83B4;
}

// ?Rva003EE6F7Get@@YAHXZ @ 0x003EE6F7 (6B): returns 0x00C36290.
// Follows a leave/ret (0x3EE6F5-56) with a mov-style function after.
// 1 direct E8 caller (0x20E1B8), no Ghidra entry (dead emission), no
// branch sources. Opaque address-derived name.
int Rva003EE6F7Get(void)
{
	return 0x00C36290;
}

// ?Rva00433B18Get@@YAHXZ @ 0x00433B18 (6B): returns 0x00E032DC.
// Follows a leave/ret (0x433B16-17) with a push-style function after.
// 1 direct E8 caller (0x23B65A), no Ghidra entry (dead emission), no
// branch sources. Opaque address-derived name.
int Rva00433B18Get(void)
{
	return 0x00E032DC;
}

// ?Rva0056A983Get@@YAHXZ @ 0x0056A983 (6B): returns 0x00C6CFD0.
// Follows a leave/ret (0x56A981-82) with a cmp/jcc-style function after.
// 1 direct E8 caller (0x3EE5CE), no Ghidra entry (dead emission), no
// branch sources. Opaque address-derived name.
int Rva0056A983Get(void)
{
	return 0x00C6CFD0;
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

// ?Rva002856F7Get@@YAHXZ @ 0x002856F7 (6B): returns 0x00DFEA50. Opens a
// contiguous pair (F7 then FD) after a ret. Carried at 0x7FB708 and
// 0x7FB70C, no direct callers, no branch sources. Opaque name.
int Rva002856F7Get(void)
{
	return 0x00DFEA50;
}

// ?Rva002856FDGet@@YAHXZ @ 0x002856FD (6B): returns 0x00DFE794. Closes
// the pair (a movzx-style function follows). Carried at 0x7FB710 and
// 0x7FB714, no direct callers, no branch sources. Opaque name.
int Rva002856FDGet(void)
{
	return 0x00DFE794;
}

// ?Rva003ABD55Get@@YAHXZ @ 0x003ABD55 (6B): returns 0x00C1C59C.
// Follows a ret (0x3ABD54) with a sub/cmp-style function after. Carried
// at 0x81CE5C and 0x81D680, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva003ABD55Get(void)
{
	return 0x00C1C59C;
}

// ?Rva003AC9A1Get@@YAHXZ @ 0x003AC9A1 (6B): returns 0x00C1C96C.
// Follows a ret (0x3AC9A0) with a sub/cmp-style function after. Carried
// at 0x81C948 and 0x81D19C, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva003AC9A1Get(void)
{
	return 0x00C1C96C;
}

// ?Rva0008EFCCGet@@YAHXZ @ 0x0008EFCC (6B): returns 0x00BFC338.
// Follows a ret (0x8EFCB) with a B8-imm getter after. Carried at 0x7C7C08
// and 0x7FD590, no direct callers, no branch sources. The value is below
// the image base so it is a plain integer, not a pointer. Opaque name.
int Rva0008EFCCGet(void)
{
	return 0x00BFC338;
}

// ?Rva004CE29DGet@@YAHXZ @ 0x004CE29D (6B): returns 0x00C5FEA0.
// Follows a ret-4 (0x4CE29A-9C) with a mov/mov/ret getter after. 41
// direct E8 callers (anchor-verified), Ghidra-6, no branch sources.
// The value sits 0x100 below landed Rva004CE52EGet's table. Opaque name.
int Rva004CE29DGet(void)
{
	return 0x00C5FEA0;
}

// ?Rva00226140Get@@YAHXZ @ 0x00226140 (6B): returns 0x00DC2274.
// Follows a ret-8 (0x22613D-3F) with a frame-style function after.
// 4 direct E8 callers (0x2264D9/0x2265AE/0x226684/0x226759, all nearby),
// Ghidra-6, no branch sources. Opaque address-derived name.
int Rva00226140Get(void)
{
	return 0x00DC2274;
}

// ?Rva00434091Get@@YAHXZ @ 0x00434091 (6B): returns 0x00DC5170.
// Follows a ret-8 (0x43408E-90) with a mov-style function after.
// 4 direct E8 callers (0x43456E/0x434647/0x434721/0x4347FA, all nearby),
// Ghidra-6, no branch sources. Opaque address-derived name.
int Rva00434091Get(void)
{
	return 0x00DC5170;
}

// ?Rva003B0E57Get@@YAHXZ @ 0x003B0E57 (6B): returns 0x00C1DB18.
// Follows a ret-4 (0x3B0E54-56) with a mov/mov/ret getter after.
// 1 direct E8 caller (0x1FE73D), Ghidra-6, no branch sources.
// Opaque address-derived name.
int Rva003B0E57Get(void)
{
	return 0x00C1DB18;
}

// ?Rva0056B7DEGet@@YAHXZ @ 0x0056B7DE (6B): returns 0x00C6D690.
// Follows a ret-4 (0x56B7DB-DD) with a B8-imm/call function after.
// 3 direct E8 callers (0x56B71B/0x56BEAF/0x56BFD2), no Ghidra entry
// (dead emission), no branch sources. Opaque address-derived name.
int Rva0056B7DEGet(void)
{
	return 0x00C6D690;
}

// ?Rva000EF29AGet@@YAHXZ @ 0x000EF29A (6B): returns 0x00544558.
// Follows a ret-16 (0xEF297-9C) with a push-style function after.
// Carried by 6 .rdata slots, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000EF29AGet(void)
{
	return 0x00544558;
}

// ?Rva00342868Get@@YAHXZ @ 0x00342868 (6B): returns 0x00C12520.
// Follows a ret-4 (0x342865-67) with a push/call-style function after.
// Carried by 4 .rdata slots, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00342868Get(void)
{
	return 0x00C12520;
}

// ?Rva000907A1Get@@YAHXZ @ 0x000907A1 (6B): returns 0x00CE4818.
// Follows a ret-12 (0x9079E-A0) with a push-style function after.
// Carried at 0x7C7F0C and 0x8E497C, no direct callers, no branch
// sources. Opaque address-derived name.
int Rva000907A1Get(void)
{
	return 0x00CE4818;
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

// ?Rva006C7580Get@@YAHXZ @ 0x006C7580 (6B): returns 0x00CE7D14.
// Follows a ret-12 (0x6C757D-7F) with CC padding, 8xCC after, carried
// at 1 .rdata slot, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva006C7580Get(void)
{
	return 0x00CE7D14;
}

// ?Rva006C7590Get@@YAHXZ @ 0x006C7590 (6B): returns 0x00CE7CBC.
// CC-island (8xCC before and after), carried at 1 .rdata slot, no
// direct callers, no branch sources. Opaque address-derived name.
int Rva006C7590Get(void)
{
	return 0x00CE7CBC;
}

// ?Rva003007A2Get@@YAHXZ @ 0x003007A2 (6B): returns 0x00700778.
// Follows a leave/ret (0x30079F-A1) with a frame-style function after
// (0x3007A8: push ebp). Ghidra-6, carried at 1 .rdata slot, no direct
// callers, no branch sources. Opaque address-derived name.
int Rva003007A2Get(void)
{
	return 0x00700778;
}

// ?Rva00200BBAGet@@YAHXZ @ 0x00200BBA (6B): returns 0x00C080B0.
// Follows a leave/ret plus a sibling B8-6 (pair, 6 apart) with a
// frame-style function after. Carried at 0x7E2BA0, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00200BBAGet(void)
{
	return 0x00C080B0;
}

// ?Rva00517F2BGet@@YAHXZ @ 0x00517F2B (6B): returns 0x006D2025.
// Follows a leave/ret (0x517F29-2A) with a B8-imm/call function after
// (0x517F31). Carried at 0x866444, no direct callers, no branch
// sources. Opaque address-derived name.
int Rva00517F2BGet(void)
{
	return 0x006D2025;
}

// ?Rva0051BF27Get@@YAHXZ @ 0x0051BF27 (6B): returns 0x006D2099.
// Follows a pop/ret (0x51BF25-26) with a lea-style function after.
// Carried at 0x866C74, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva0051BF27Get(void)
{
	return 0x006D2099;
}

// ?Rva0051D772Get@@YAHXZ @ 0x0051D772 (6B): returns 0x006D210D.
// Follows an add-esp/ret (0x51D76F-71) with a frame-style function
// after. Carried at 0x866FC8, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva0051D772Get(void)
{
	return 0x006D210D;
}

// ?Rva0056D749Get@@YAHXZ @ 0x0056D749 (6B): returns 0x00810223.
// Follows a leave/ret (0x56D746-48) with a frame-style function after.
// Carried at 0x86DAE0, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva0056D749Get(void)
{
	return 0x00810223;
}

// ?Rva005C9880Get@@YAHXZ @ 0x005C9880 (6B): returns 0x009C9886.
// Follows a pop/ret (0x5C987E-7F) with a B8-imm/call function after
// (0x5C9886). Carried at 0x874B8C, no direct callers, no branch
// sources. Opaque address-derived name.
int Rva005C9880Get(void)
{
	return 0x009C9886;
}

// ?Rva00201095Get@@YAHXZ @ 0x00201095 (6B): returns 0x00BE2C10.
// Follows a tail-jmp/ret (0x20108F-94) with a frame-style function
// after. Carried at 0x7E306C, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00201095Get(void)
{
	return 0x00BE2C10;
}

// ?Rva004EE155Get@@YAHXZ @ 0x004EE155 (6B): returns 0x00C62A38.
// Follows a mov-word/ret (0x4EE14F-54) with a frame-style function
// after. Carried at 0x862A30, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva004EE155Get(void)
{
	return 0x00C62A38;
}

// ?Rva00655114Get@@YAHXZ @ 0x00655114 (6B): returns 1. Follows a
// pop-ebp/ret (0x65510F-13) with a mov-style function after. Carried
// at 0x8E0B54, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00655114Get(void)
{
	return 1;
}

// ?Rva0033A495Get@@YAHXZ @ 0x0033A495 (6B): returns 0x00C100C0.
// A leave/ret-8 pair ends at 0x33A490 with a 4-byte jmp fragment between it
// and this getter; no branch targets this address (phase-scanned
// 0x339000-0x33B000, only 4 direct E8 callers at 0x415231/0x4CB0A1/0x4CB642
// 0x4CBC1B, all pushing an extraOffset then feeding eax to a FieldParse
// add). The value is the VoiceSelect-led response table at 0xC100C0.
// Opaque address-derived name.
int Rva0033A495Get(void)
{
	return 0x00C100C0;
}

// ?Rva0002CF5EGet@@YAHXZ @ 0x0002CF5E (6B): returns 0x0042CF5A.
// Ghidra-6 B8-imm/ret island; unclaimed on master; opaque address-derived
// name following the ConstIntGetters family precedent.
int Rva0002CF5EGet(void)
{
	return 0x0042CF5A;
}

// ?Rva0006182EGet@@YAHXZ @ 0x0006182E (6B): returns 0x00461834.
int Rva0006182EGet(void)
{
	return 0x00461834;
}

// ?Rva00061983Get@@YAHXZ @ 0x00061983 (6B): returns 0x00461989.
int Rva00061983Get(void)
{
	return 0x00461989;
}

// ?Rva0022D537Get@@YAHXZ @ 0x0022D537 (6B): returns 0x0062D53D.
int Rva0022D537Get(void)
{
	return 0x0062D53D;
}

// ?Rva00282C9BGet@@YAHXZ @ 0x00282C9B (6B): returns 0x00682CA1.
int Rva00282C9BGet(void)
{
	return 0x00682CA1;
}

// ?Rva002DF1EBGet@@YAHXZ @ 0x002DF1EB (6B): returns 0x006DF116.
int Rva002DF1EBGet(void)
{
	return 0x006DF116;
}

// ?Rva0030539FGet@@YAHXZ @ 0x0030539F (6B): returns 0x007053A5.
int Rva0030539FGet(void)
{
	return 0x007053A5;
}

// ?Rva00317717Get@@YAHXZ @ 0x00317717 (6B): returns 0x007176F7.
int Rva00317717Get(void)
{
	return 0x007176F7;
}

// ?Rva003341CDGet@@YAHXZ @ 0x003341CD (6B): returns 0x007341D3.
int Rva003341CDGet(void)
{
	return 0x007341D3;
}

// ?Rva00337055Get@@YAHXZ @ 0x00337055 (6B): returns 0x0073705B.
int Rva00337055Get(void)
{
	return 0x0073705B;
}

// ?Rva0033984FGet@@YAHXZ @ 0x0033984F (6B): returns 0x00739855.
int Rva0033984FGet(void)
{
	return 0x00739855;
}

// ?Rva003FA6FFGet@@YAHXZ @ 0x003FA6FF (6B): returns 0x00C378F0.
int Rva003FA6FFGet(void)
{
	return 0x00C378F0;
}

// ?Rva0041A967Get@@YAHXZ @ 0x0041A967 (6B): returns 0x0081A8B1.
int Rva0041A967Get(void)
{
	return 0x0081A8B1;
}

// ?Rva004D02F0Get@@YAHXZ @ 0x004D02F0 (6B): returns 0x008D02D3.
int Rva004D02F0Get(void)
{
	return 0x008D02D3;
}

// ?Rva0055037EGet@@YAHXZ @ 0x0055037E (6B): returns 0x0095026E.
int Rva0055037EGet(void)
{
	return 0x0095026E;
}

// ?Rva00552BD2Get@@YAHXZ @ 0x00552BD2 (6B): returns 0x009521D4.
int Rva00552BD2Get(void)
{
	return 0x009521D4;
}

// ?Rva00558D07Get@@YAHXZ @ 0x00558D07 (6B): returns 0x009588A1.
int Rva00558D07Get(void)
{
	return 0x009588A1;
}

// ?Rva0073F640Get@@YAHXZ @ 0x0073F640 (6B): returns 0x00B3F646.
int Rva0073F640Get(void)
{
	return 0x00B3F646;
}

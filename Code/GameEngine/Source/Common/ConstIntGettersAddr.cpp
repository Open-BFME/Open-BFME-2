// The members of the ConstIntGetters.cpp family whose constant is an image address
// no unit defines yet, split out so the rest of the family links; each moves
// back once its target has a definition to name.
//
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


// ?Rva00336E72Get@@YAHXZ @ 0x00336E72 (6B): returns 0x00736E78.
// Follows a byte-identical dead twin at 0x336E6C (whole-image refs 0;
// the linker kept both copies, only this one is used). 6 .rdata refs,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00336E72Get(void)
{
	return 0x00736E78;
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
	return (int)"DefaultModule<CAT_PHYSICS>";
}

// ?Rva003AC9A1Get@@YAHXZ @ 0x003AC9A1 (6B): returns 0x00C1C96C.
// Follows a ret (0x3AC9A0) with a sub/cmp-style function after. Carried
// at 0x81C948 and 0x81D19C, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva003AC9A1Get(void)
{
	return (int)"DefaultParticleModule<CAT_COLOR>";
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
	return (int)"AIMoveAndTightenState";
}

// ?Rva000907A1Get@@YAHXZ @ 0x000907A1 (6B): returns 0x00CE4818.
// Follows a ret-12 (0x9079E-A0) with a push-style function after.
// Carried at 0x7C7F0C and 0x8E497C, no direct callers, no branch
// sources. Opaque address-derived name.
int Rva000907A1Get(void)
{
	return 0x00CE4818;
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


// ?Rva0051BF27Get@@YAHXZ @ 0x0051BF27 (6B): returns 0x006D2099.
// Follows a pop/ret (0x51BF25-26) with a lea-style function after.
// Carried at 0x866C74, no direct callers, no branch sources.
// Opaque address-derived name.


// ?Rva0051D772Get@@YAHXZ @ 0x0051D772 (6B): returns 0x006D210D.
// Follows an add-esp/ret (0x51D76F-71) with a frame-style function
// after. Carried at 0x866FC8, no direct callers, no branch sources.
// Opaque address-derived name.


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
	return (int)"LivingWorldScoreKeeper::PerTurnStats";
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

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.

// FXParticleSystem default-parser tables, defined here (this unit already
// absorbs image-address debt) so FXParticleSystemDefaultParsers.cpp links.
// Each is the exact retail bytes: 16-byte FieldParse entries plus the zero
// terminator, read from game.dat. Referenced by name from the parser TU.

// Retail VA 0x00C6B988: Alpha1..Alpha8 plus terminator (144B).
extern const int s_fxpsAlphaTable[36] = {
    0x00C6B97C, 0x0095B29C, 0x00000000, 0x0000000C,
    0x00C6B974, 0x0095B29C, 0x00000000, 0x0000001C,
    0x00C6B96C, 0x0095B29C, 0x00000000, 0x0000002C,
    0x00C6B964, 0x0095B29C, 0x00000000, 0x0000003C,
    0x00C6B95C, 0x0095B29C, 0x00000000, 0x0000004C,
    0x00C6B954, 0x0095B29C, 0x00000000, 0x0000005C,
    0x00C6B94C, 0x0095B29C, 0x00000000, 0x0000006C,
    0x00C6B944, 0x0095B29C, 0x00000000, 0x0000007C,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00C6C4A0: SizeRate..AngularDampingXY plus terminator (160B).
extern const int s_fxpsSizeAngleTable[40] = {
    0x00BE189C, 0x00738A9D, 0x00000000, 0x0000000C,
    0x00BE188C, 0x00738A9D, 0x00000000, 0x00000018,
    0x00C6C498, 0x00738A9D, 0x00000000, 0x00000024,
    0x00C6C488, 0x00738A9D, 0x00000000, 0x00000030,
    0x00C6C478, 0x00738A9D, 0x00000000, 0x0000003C,
    0x00C6C46C, 0x0042EC4E, 0x00C1B6D8, 0x00000048,
    0x00C6C464, 0x00738A9D, 0x00000000, 0x0000004C,
    0x00C6C454, 0x00738A9D, 0x00000000, 0x00000058,
    0x00C6C440, 0x00738A9D, 0x00000000, 0x00000064,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00C6C3E0: Gravity..ParticlesAttachToBone plus terminator (96B).
extern const int s_fxpsPhysicsTable[24] = {
    0x00BE1824, 0x0042EFC0, 0x00000000, 0x00000018,
    0x00BE1804, 0x00738A9D, 0x00000000, 0x0000001C,
    0x00BE1814, 0x0042F507, 0x00000000, 0x0000000C,
    0x00C6C3D8, 0x0042E850, 0x00000000, 0x00000028,
    0x00C6C3C0, 0x0042E850, 0x00000000, 0x00000029,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00C6BA58: Color1..Color8 plus ColorScale plus terminator (160B).
extern const int s_fxpsColorTable[40] = {
    0x00C6BA50, 0x0095B913, 0x00000000, 0x0000000C,
    0x00C6BA48, 0x0095B913, 0x00000000, 0x0000001C,
    0x00C6BA40, 0x0095B913, 0x00000000, 0x0000002C,
    0x00C6BA38, 0x0095B913, 0x00000000, 0x0000003C,
    0x00C6BA30, 0x0095B913, 0x00000000, 0x0000004C,
    0x00C6BA28, 0x0095B913, 0x00000000, 0x0000005C,
    0x00C6BA20, 0x0095B913, 0x00000000, 0x0000006C,
    0x00C6BA18, 0x0095B913, 0x00000000, 0x0000007C,
    0x00BE17BC, 0x00738A9D, 0x00000000, 0x0000008C,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// LK2 link batch: FieldParse tables named by the BuildFieldParse TUs that
// reference them (all bytes read from game.dat, terminators per ZH {0,0,0,0}
// convention; two tables carry no terminator and are defined to their last
// valid entry). This unit already absorbs image-address debt; its link state
// is unchanged. The parser TUs link by naming these instead of casting VAs.
// Retail VA 0x00bcb3c8: 57 entries + terminator (928B).
extern const int s_modelDrawFieldTable[232] = {
    0x00BCB3B0, 0x00738BBD, 0x00000000, 0x00000054,
    0x00BCB39C, 0x0042EFC0, 0x00000000, 0x00000058,
    0x00BCB38C, 0x0042EFC0, 0x00000000, 0x0000005C,
    0x00BCB378, 0x00738BBD, 0x00000000, 0x00000060,
    0x00BCB360, 0x0042E850, 0x00000000, 0x00000068,
    0x00BCB348, 0x0042E850, 0x00000000, 0x0000006B,
    0x00BCB338, 0x0042EC4E, 0x00DB960C, 0x00000064,
    0x00BCB314, 0x0042EB38, 0x00DBC284, 0x00000050,
    0x00BCB2F8, 0x004C8914, 0x00000001, 0x00000000,
    0x00BCB2E4, 0x004C8914, 0x00000000, 0x00000000,
    0x00BCB2D0, 0x004C9146, 0x00000001, 0x00000000,
    0x00BCB2C0, 0x004C9146, 0x00000002, 0x00000000,
    0x00BCB2B0, 0x004C9146, 0x00000000, 0x00000000,
    0x00BCB2A4, 0x004B6E5A, 0x00000000, 0x0000003C,
    0x00BCB294, 0x0042E896, 0x00000000, 0x00000030,
    0x00BCB278, 0x004B6E5A, 0x00000000, 0x00000040,
    0x00BCB25C, 0x004B9468, 0x00000000, 0x000000BC,
    0x00BCB248, 0x004C4BAE, 0x00000000, 0x00000000,
    0x00BCB234, 0x0042E850, 0x00000000, 0x000000B8,
    0x00BCB228, 0x0042E850, 0x00000000, 0x00000069,
    0x00BCB210, 0x0042E850, 0x00000000, 0x0000006A,
    0x00BCB200, 0x004C855C, 0x00000000, 0x00000000,
    0x00BCB1E0, 0x0042E850, 0x00000000, 0x00000088,
    0x00BCB1D0, 0x004C3C59, 0x00000000, 0x00000000,
    0x00BCB1C4, 0x004C8748, 0x00000000, 0x00000000,
    0x00BCB1A0, 0x0042E850, 0x00000000, 0x00000108,
    0x00BCB18C, 0x0042F11E, 0x00000000, 0x00000044,
    0x00BCB178, 0x0042F11E, 0x00000000, 0x00000048,
    0x00BCB16C, 0x0042F11E, 0x00000000, 0x00000114,
    0x00BCB160, 0x0042F11E, 0x00000000, 0x00000118,
    0x00BCB154, 0x004C39F5, 0x00000000, 0x0000011C,
    0x00BCB144, 0x0042F11E, 0x00000000, 0x0000010C,
    0x00BCB134, 0x0042F11E, 0x00000000, 0x00000110,
    0x00BCB128, 0x0042E850, 0x00000000, 0x00000128,
    0x00BCB118, 0x0042E850, 0x00000000, 0x00000129,
    0x00BCB0FC, 0x0042E850, 0x00000000, 0x0000012A,
    0x00BCB0E8, 0x0042E850, 0x00000000, 0x0000012B,
    0x00BCB0D0, 0x0042EFC0, 0x00000000, 0x0000012C,
    0x00BCB0B8, 0x0042EFC0, 0x00000000, 0x00000130,
    0x00BCB0A4, 0x0042E850, 0x00000000, 0x00000134,
    0x00BCB090, 0x0042E850, 0x00000000, 0x00000135,
    0x00BCB074, 0x0042E850, 0x00000000, 0x00000136,
    0x00BCB05C, 0x0042E850, 0x00000000, 0x00000137,
    0x00BCB048, 0x0042E850, 0x00000000, 0x00000138,
    0x00BCB034, 0x0042E850, 0x00000000, 0x00000139,
    0x00BCB024, 0x0042F5BA, 0x00000000, 0x0000013C,
    0x00BCB010, 0x0042F11E, 0x00000000, 0x00000014,
    0x00BCAFF4, 0x0042EFDC, 0x00000000, 0x00000144,
    0x00BCAFD8, 0x0042EFDC, 0x00000000, 0x00000148,
    0x00BCAFBC, 0x0042F1BA, 0x00000000, 0x0000014C,
    0x00BCAFA0, 0x0042EF56, 0x00000000, 0x00000158,
    0x00BCAF90, 0x00738B30, 0x00000000, 0x00000150,
    0x00BCAF7C, 0x0042E850, 0x00000000, 0x00000154,
    0x00BCAF64, 0x0042E850, 0x00000000, 0x0000015C,
    0x00BCAF54, 0x0042E850, 0x00000000, 0x0000015D,
    0x00BCAF40, 0x0042E850, 0x00000000, 0x0000015E,
    0x00BCAF30, 0x0042E850, 0x00000000, 0x0000015F,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00bcb840: 16 entries + terminator (272B).
extern const int s_laserDrawFieldTable[68] = {
    0x00BCB834, 0x0042EF72, 0x00000000, 0x00000020,
    0x00BCB824, 0x0042EFC0, 0x00000000, 0x00000010,
    0x00BCB814, 0x0042EFC0, 0x00000000, 0x00000014,
    0x00BCB808, 0x0042F3FE, 0x00000000, 0x00000008,
    0x00BCB7FC, 0x0042F3FE, 0x00000000, 0x0000000C,
    0x00BCB7E4, 0x00738B30, 0x00000000, 0x00000024,
    0x00BCB7D4, 0x00738B30, 0x00000000, 0x00000028,
    0x00BCA9B0, 0x0042E896, 0x00000000, 0x0000002C,
    0x00BCB7C8, 0x0042EFC0, 0x00000000, 0x00000018,
    0x00BCB7C0, 0x0042E850, 0x00000000, 0x0000001C,
    0x00BCB7B4, 0x0042EF72, 0x00000000, 0x00000038,
    0x00BCB7A8, 0x0042EFC0, 0x00000000, 0x0000003C,
    0x00BCB794, 0x0042EFC0, 0x00000000, 0x00000040,
    0x00BCB784, 0x0042EFC0, 0x00000000, 0x00000044,
    0x00BCB778, 0x0042EFC0, 0x00000000, 0x00000048,
    0x00BCB76C, 0x00738E52, 0x00000000, 0x0000004C,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00bcd918: 10 entries (no terminator) (160B).
extern const int s_lightDrawFieldTable[40] = {
    0x00BCD90C, 0x0042F259, 0x00000000, 0x00000008,
    0x00BCD904, 0x0042F259, 0x00000000, 0x00000014,
    0x00BCD8F8, 0x0042F259, 0x00000000, 0x00000020,
    0x00BCD8F0, 0x0042EFC0, 0x00000000, 0x0000002C,
    0x00BCD8E4, 0x0042EFC0, 0x00000000, 0x00000030,
    0x00BCD8D0, 0x0042EFC0, 0x00000000, 0x00000034,
    0x00BCD8BC, 0x0042EFC0, 0x00000000, 0x00000038,
    0x00BCD8AC, 0x0042EFC0, 0x00000000, 0x0000003C,
    0x00BCD89C, 0x0042EFC0, 0x00000000, 0x00000040,
    0x00BCB278, 0x0042F11E, 0x00000000, 0x00000044,
};

// Retail VA 0x00c5f064: 2 entries + terminator (48B).
extern const int s_animSoundFieldTable[12] = {
    0x00C5F054, 0x008CA798, 0x00000000, 0x00000000,
    0x00C5F040, 0x0042EFDC, 0x00000000, 0x00000014,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c5a7a8: 11 entries + terminator (192B).
extern const int CrateCollideTable[48] = {
    0x00C5A794, 0x006567EA, 0x00000000, 0x00000008,
    0x00C5A784, 0x006567EA, 0x00000000, 0x00000024,
    0x00C5A770, 0x0042E850, 0x00000000, 0x00000040,
    0x00C5A760, 0x0042E850, 0x00000000, 0x00000041,
    0x00C5A754, 0x0042E850, 0x00000000, 0x00000042,
    0x00C5A744, 0x007396D3, 0x00000000, 0x00000044,
    0x00C5A738, 0x00738A09, 0x00000000, 0x00000048,
    0x00C5A724, 0x0042F11E, 0x00000000, 0x0000004C,
    0x00C5A70C, 0x0042EFC0, 0x00000000, 0x00000050,
    0x00C5A6F4, 0x0042EFC0, 0x00000000, 0x00000054,
    0x00C5A6DC, 0x0042E850, 0x00000000, 0x00000058,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c5a4a8: 16 entries + terminator (272B).
extern const int AODCrushCollideTable[68] = {
    0x00C5A498, 0x00738A09, 0x00000000, 0x00000008,
    0x00C5A480, 0x00738A6F, 0x00000000, 0x0000000C,
    0x00C5A470, 0x00738A09, 0x00000000, 0x00000010,
    0x00C5A454, 0x00738A6F, 0x00000000, 0x00000014,
    0x00C5A448, 0x00738A09, 0x00000000, 0x00000018,
    0x00C5A430, 0x00738A6F, 0x00000000, 0x0000001C,
    0x00C03E1C, 0x0042EFC0, 0x00000000, 0x00000028,
    0x00C015C8, 0x0042EC4E, 0x00DCD4D0, 0x00000020,
    0x00C015BC, 0x0042EC4E, 0x00DCD550, 0x00000024,
    0x00C5A420, 0x0042EFC0, 0x00000000, 0x00000038,
    0x00C5A40C, 0x0042EC4E, 0x00DCD4D0, 0x00000030,
    0x00C5A3F8, 0x0042EC4E, 0x00DCD550, 0x00000034,
    0x00C5A3EC, 0x0042EFC0, 0x00000000, 0x00000044,
    0x00C5A3DC, 0x0042EC4E, 0x00DCD4D0, 0x0000003C,
    0x00C5A3CC, 0x0042EC4E, 0x00DCD550, 0x00000040,
    0x00C3F700, 0x00761CA5, 0x00000000, 0x0000002C,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00befabc: 1 entries + terminator (32B).
extern const int s_moneyCrateFieldTable[8] = {
    0x00BEFAAC, 0x0042EF72, 0x00000000, 0x0000005C,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00befb60: 4 entries + terminator (80B).
extern const int s_veterancyCrateFieldTable[20] = {
    0x00BEFB54, 0x0042EF72, 0x00000000, 0x0000005C,
    0x00BEFB40, 0x0042E850, 0x00000000, 0x00000060,
    0x00BEFB38, 0x0042E850, 0x00000000, 0x00000061,
    0x00BEFB24, 0x0042EF56, 0x00000000, 0x00000064,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00bf9378: 19 entries + terminator (320B).
extern const int s_transportAiFieldTable[80] = {
    0x00BCA7FC, 0x006623C1, 0x00000000, 0x00000014,
    0x00BF9368, 0x0042F11E, 0x00000000, 0x00000044,
    0x00BF934C, 0x0042EB38, 0x00DBB4C4, 0x0000001C,
    0x00BF9338, 0x0042EFC0, 0x00000000, 0x00000020,
    0x00BF932C, 0x0042E850, 0x00000000, 0x00000024,
    0x00BF9318, 0x00738B30, 0x00000000, 0x00000018,
    0x00BF9300, 0x0042E850, 0x00000000, 0x00000025,
    0x00BF92E0, 0x0042EFC0, 0x00000000, 0x00000028,
    0x00BF92D0, 0x0042F11E, 0x00000000, 0x0000002C,
    0x00BF92C0, 0x00738B30, 0x00000000, 0x00000034,
    0x00BF92B0, 0x00738B30, 0x00000000, 0x00000030,
    0x00BF92A4, 0x00738B30, 0x00000000, 0x00000038,
    0x00BF928C, 0x0042E850, 0x00000000, 0x0000003C,
    0x00BF9278, 0x00738B30, 0x00000000, 0x00000040,
    0x00BF9258, 0x00738B30, 0x00000000, 0x00000048,
    0x00BF9244, 0x0042EC4E, 0x00DBB4F0, 0x00000050,
    0x00BF922C, 0x0042EFC0, 0x00000000, 0x0000004C,
    0x00BF9214, 0x0042E896, 0x00000000, 0x00000058,
    0x00BF9204, 0x0042E850, 0x00000000, 0x00000054,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00bef4b0: 8 entries + terminator (144B).
extern const int s_supplyTruckAiFieldTable[36] = {
    0x00BEF4A0, 0x0042EF56, 0x00000000, 0x00000064,
    0x00BEF488, 0x00738B30, 0x00000000, 0x00000068,
    0x00BEF46C, 0x00738B30, 0x00000000, 0x0000006C,
    0x00BEF450, 0x0042EFC0, 0x00000000, 0x00000070,
    0x00BEF440, 0x0042E850, 0x00000000, 0x00000074,
    0x00BEF428, 0x0042EFC0, 0x00000000, 0x00000078,
    0x00BEF410, 0x00738B30, 0x00000000, 0x0000007C,
    0x00BEF3FC, 0x00738B30, 0x00000000, 0x00000080,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00beecb0: 7 entries + terminator (128B).
extern const int s_deployStyleFieldTable[32] = {
    0x00BEECA0, 0x00738B30, 0x00000000, 0x00000064,
    0x00BEEC94, 0x00738B30, 0x00000000, 0x00000068,
    0x00BEEC78, 0x0042E850, 0x00000000, 0x0000006C,
    0x00BEEC58, 0x0042E850, 0x00000000, 0x0000006D,
    0x00BEEC38, 0x0042E850, 0x00000000, 0x0000006E,
    0x00BEEC24, 0x0042E850, 0x00000000, 0x0000006F,
    0x00BEEC08, 0x0042F11E, 0x00000000, 0x00000070,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00beed74: 2 entries + terminator (48B).
extern const int s_assaultTransportFieldTable[12] = {
    0x00BEED58, 0x0042EFC0, 0x00000000, 0x00000064,
    0x00BEED30, 0x0042EFC0, 0x00000000, 0x00000068,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00beeb88: 7 entries + terminator (128B).
extern const int s_animalAiFieldTable[32] = {
    0x00BEEB7C, 0x0042EF56, 0x00000000, 0x00000064,
    0x00BEEB6C, 0x0042EF56, 0x00000000, 0x00000068,
    0x00BEEB58, 0x0042EF56, 0x00000000, 0x0000006C,
    0x00BEEB44, 0x0042EF56, 0x00000000, 0x00000070,
    0x00BEEB34, 0x0042EF56, 0x00000000, 0x00000074,
    0x00BEEB28, 0x0042EF56, 0x00000000, 0x00000078,
    0x00BEEB18, 0x0042E850, 0x00000000, 0x0000007C,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00bef580: 4 entries + terminator (80B).
extern const int s_wanderAiFieldTable[20] = {
    0x00BEF570, 0x0042E850, 0x00000000, 0x00000064,
    0x00BEF55C, 0x008B6481, 0x00000000, 0x00000068,
    0x00BEF550, 0x0042E850, 0x00000000, 0x0000006C,
    0x00BEF540, 0x0042EF72, 0x00000000, 0x00000070,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c561d0: 14 entries + terminator (240B).
extern const int s_respawnFieldTable[60] = {
    0x00C561C0, 0x004B9468, 0x00000000, 0x0000000C,
    0x00BF08D8, 0x00738A09, 0x00000000, 0x000000F0,
    0x00C561AC, 0x00738B30, 0x00000000, 0x000000FC,
    0x00C56198, 0x004B9468, 0x00000000, 0x000000A4,
    0x00C56188, 0x00738A09, 0x00000000, 0x000000F8,
    0x00C5616C, 0x00738B30, 0x00000000, 0x00000104,
    0x00C56160, 0x004B9468, 0x00000000, 0x00000058,
    0x00C56154, 0x00738A09, 0x00000000, 0x000000F4,
    0x00C5613C, 0x00738B30, 0x00000000, 0x00000100,
    0x00C56120, 0x00761CA5, 0x00000000, 0x00000008,
    0x00C56110, 0x008AFC5F, 0x00000000, 0x0000010C,
    0x00C56100, 0x008AFE6C, 0x00000000, 0x0000010C,
    0x00BE636C, 0x0042F11E, 0x00000000, 0x00000118,
    0x00C560EC, 0x0042F11E, 0x00000000, 0x0000011C,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00bf00a0: 2 entries + terminator (48B).
extern const int s_castleFieldTable1[12] = {
    0x00BEF600, 0x0042F1BA, 0x00000000, 0x00000008,
    0x00BF0090, 0x0042EF56, 0x00000000, 0x0000000C,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c1aba0: 23 entries + terminator (384B).
extern const int s_castleFieldTable2[96] = {
    0x00C1AB80, 0x0079981E, 0x00000000, 0x00000068,
    0x00C1AB68, 0x00761CA5, 0x00000000, 0x00000030,
    0x00C1AB5C, 0x00761CA5, 0x00000000, 0x00000034,
    0x00C1AB4C, 0x0079A565, 0x00000000, 0x0000005C,
    0x00C1AB3C, 0x0079A4FC, 0x00000000, 0x00000050,
    0x00C1AB2C, 0x0042F11E, 0x00000000, 0x00000010,
    0x00BDCCE0, 0x0042F11E, 0x00000000, 0x00000014,
    0x00C1AB20, 0x0042EFC0, 0x00000000, 0x00000018,
    0x00BE0B5C, 0x0042EFC0, 0x00000000, 0x0000001C,
    0x00C1AB10, 0x0042EFC0, 0x00000000, 0x00000020,
    0x00BFAA6C, 0x0042EFC0, 0x00000000, 0x00000024,
    0x00C1AB00, 0x0042EFC0, 0x00000000, 0x00000028,
    0x00BEA24C, 0x0042EFC0, 0x00000000, 0x0000002C,
    0x00C1AAF0, 0x00738B30, 0x00000000, 0x00000038,
    0x00C1AAE0, 0x0042E850, 0x00000000, 0x0000003C,
    0x00C1AAC4, 0x0042E850, 0x00000000, 0x0000003D,
    0x00C1AAB4, 0x00738A09, 0x00000000, 0x00000048,
    0x00C1AAA4, 0x00738A09, 0x00000000, 0x00000044,
    0x00C1AA90, 0x00738B30, 0x00000000, 0x00000040,
    0x00C1AA74, 0x0042E850, 0x00000000, 0x00000074,
    0x00C1AA58, 0x005DEE74, 0x00000000, 0x0000004C,
    0x00C1AA4C, 0x0042E850, 0x00000000, 0x0000003E,
    0x00C1AA20, 0x0042E850, 0x00000000, 0x00000075,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c42a38: 12 entries + terminator (208B).
extern const int s_dynamicPortalFieldTable[52] = {
    0x00C42A2C, 0x0042F11E, 0x00000000, 0x0000011C,
    0x00C42A1C, 0x0042EF56, 0x00000000, 0x00000118,
    0x00C42A10, 0x0086133B, 0x00000000, 0x00000120,
    0x00C42A08, 0x008616B1, 0x00000000, 0x0000012C,
    0x00BCB144, 0x0042F11E, 0x00000000, 0x00000138,
    0x00C429FC, 0x0042E850, 0x00000000, 0x0000013C,
    0x00C429F0, 0x0042EF72, 0x00000000, 0x00000140,
    0x00C429E0, 0x0042F507, 0x00000000, 0x00000144,
    0x00C429D0, 0x0042EFC0, 0x00000000, 0x00000150,
    0x00C17D8C, 0x0042E850, 0x00000000, 0x0000013D,
    0x00C429B8, 0x0042EFC0, 0x00000000, 0x00000154,
    0x00BDCA04, 0x00761CA5, 0x00000000, 0x00000158,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c52790: 11 entries + terminator (192B).
extern const int s_structureCollapseFieldTable[48] = {
    0x00C52778, 0x00738B30, 0x00000000, 0x00000038,
    0x00C52764, 0x00738B30, 0x00000000, 0x0000003C,
    0x00C52754, 0x00738B30, 0x00000000, 0x00000040,
    0x00C52744, 0x00738B30, 0x00000000, 0x00000044,
    0x00C52734, 0x0042EFC0, 0x00000000, 0x0000004C,
    0x00C52728, 0x0042EFC0, 0x00000000, 0x00000050,
    0x00C52714, 0x0042EF56, 0x00000000, 0x00000048,
    0x00C03DFC, 0x008A4B94, 0x00000000, 0x00000000,
    0x00BDD9D8, 0x008A4B31, 0x00000000, 0x00000000,
    0x00C526FC, 0x0042E850, 0x00000000, 0x000000F4,
    0x00C526EC, 0x0042EFC0, 0x00000000, 0x000000F8,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c44648: 33 entries + terminator (544B).
extern const int s_transportContainFieldTable[136] = {
    0x00C44640, 0x0042EF56, 0x00000000, 0x00000098,
    0x00C4462C, 0x0042E850, 0x00000000, 0x0000013E,
    0x00C44610, 0x0042E850, 0x00000000, 0x0000013F,
    0x00C445FC, 0x0042E850, 0x00000000, 0x00000140,
    0x00C445E0, 0x0042E850, 0x00000000, 0x00000141,
    0x00C445BC, 0x0042E850, 0x00000000, 0x00000142,
    0x00C445B0, 0x0042F11E, 0x00000000, 0x000000A0,
    0x00C445A0, 0x007389DD, 0x00000000, 0x0000009C,
    0x00C44590, 0x00867DE6, 0x00000000, 0x00000000,
    0x00C4457C, 0x0042EFC0, 0x00000000, 0x000000A8,
    0x00BF1E24, 0x00738B30, 0x00000000, 0x000000AC,
    0x00C44568, 0x006567EA, 0x00000000, 0x000000B0,
    0x00C44554, 0x006567EA, 0x00000000, 0x000000CC,
    0x00C4453C, 0x006567EA, 0x00000000, 0x000000E8,
    0x00C44524, 0x006567EA, 0x00000000, 0x00000104,
    0x00C4450C, 0x006567EA, 0x00000000, 0x00000120,
    0x00C444F0, 0x0042E850, 0x00000000, 0x0000013C,
    0x00C444DC, 0x0042E850, 0x00000000, 0x0000013D,
    0x00C444D0, 0x00739569, 0x00000000, 0x00000144,
    0x00C444B8, 0x0042E850, 0x00000000, 0x00000148,
    0x00BEF55C, 0x008B6481, 0x00000000, 0x0000014C,
    0x00C4449C, 0x0042E850, 0x00000000, 0x00000150,
    0x00C44484, 0x00738B30, 0x00000000, 0x00000154,
    0x00C44468, 0x0042F507, 0x00000000, 0x00000158,
    0x00C44444, 0x00739569, 0x00000000, 0x00000164,
    0x00C44438, 0x00761CA5, 0x00000000, 0x00000168,
    0x00C44420, 0x0042E850, 0x00000000, 0x0000016C,
    0x00C4440C, 0x0042E850, 0x00000000, 0x0000016D,
    0x00C443FC, 0x0042EFC0, 0x00000000, 0x00000170,
    0x00C443EC, 0x0042EFC0, 0x00000000, 0x00000174,
    0x00C443E0, 0x0042E850, 0x00000000, 0x00000178,
    0x00C443CC, 0x0042EFC0, 0x00000000, 0x0000017C,
    0x00C443B4, 0x00868908, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c487f8: 3 entries + terminator (64B).
extern const int s_slaughterHordeFieldTable[16] = {
    0x00C487E8, 0x0042F1BA, 0x00000000, 0x000000D4,
    0x00C487D8, 0x00761CA5, 0x00000000, 0x000000D8,
    0x00C487B8, 0x007B1327, 0x00000000, 0x000000DC,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c45530: 39 entries + terminator (640B).
extern const int s_hordeContainFieldTable[160] = {
    0x00C45510, 0x0042E850, 0x00000000, 0x000001D8,
    0x00C45504, 0x0087414D, 0x00000000, 0x0000018C,
    0x00C454EC, 0x0086AD52, 0x00000000, 0x000001B4,
    0x00C454D0, 0x0086AD18, 0x00000000, 0x000001B8,
    0x00C454B0, 0x0086AD18, 0x00000000, 0x000001C4,
    0x00C454A4, 0x0086F39E, 0x00000000, 0x00000198,
    0x00C45490, 0x0042F11E, 0x00000000, 0x000001B0,
    0x00C45480, 0x0042F558, 0x00000000, 0x000001D0,
    0x00C45470, 0x0042F507, 0x00000000, 0x00000200,
    0x00C45460, 0x0042F196, 0x00000000, 0x000001F4,
    0x00C45448, 0x0086F179, 0x00000000, 0x0000020C,
    0x00C45430, 0x0042F196, 0x00000000, 0x00000218,
    0x00C45424, 0x0042EF56, 0x00000000, 0x00000208,
    0x00C45410, 0x00738B30, 0x00000000, 0x000001DC,
    0x00C453FC, 0x00738B30, 0x00000000, 0x000001E0,
    0x00C453E8, 0x0042EFC0, 0x00000000, 0x000001E4,
    0x00C453D4, 0x0042EFC0, 0x00000000, 0x000001E8,
    0x00C453C0, 0x0042F1BA, 0x00000000, 0x000001EC,
    0x00C453B4, 0x0042EFC0, 0x00000000, 0x000001F0,
    0x00BFBA5C, 0x0042F196, 0x00000000, 0x00000224,
    0x00C4539C, 0x0042E850, 0x00000000, 0x00000230,
    0x00C45388, 0x0042EC4E, 0x00DBB4F0, 0x00000234,
    0x00C45378, 0x0042E850, 0x00000000, 0x00000238,
    0x00C4536C, 0x0042F11E, 0x00000000, 0x0000023C,
    0x00C45354, 0x0042E850, 0x00000000, 0x00000240,
    0x00C45348, 0x0086F288, 0x00000000, 0x000001A4,
    0x00C4532C, 0x0042EFC0, 0x00000000, 0x00000244,
    0x00C45314, 0x005DEE74, 0x00000000, 0x00000248,
    0x00C45308, 0x0042E850, 0x00000000, 0x0000024C,
    0x00C452F4, 0x0042EF56, 0x00000000, 0x00000250,
    0x00C452E0, 0x0042E850, 0x00000000, 0x00000254,
    0x00C452CC, 0x0042E850, 0x00000000, 0x00000255,
    0x00C452C0, 0x0042EFC0, 0x00000000, 0x0000025C,
    0x00C452B0, 0x00738B30, 0x00000000, 0x00000260,
    0x00C452A0, 0x00738B30, 0x00000000, 0x00000264,
    0x00C3C270, 0x008691B7, 0x00000000, 0x00000258,
    0x00C4528C, 0x0042EF72, 0x00000000, 0x00000268,
    0x00C45278, 0x0042F1BA, 0x00000000, 0x0000026C,
    0x00C45264, 0x0042F1BA, 0x00000000, 0x00000270,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00bef620: 12 entries + terminator (208B).
extern const int s_workerAiFieldTable[52] = {
    0x00BEF4A0, 0x0042EF56, 0x00000000, 0x00000064,
    0x00BEF600, 0x0042F1BA, 0x00000000, 0x00000068,
    0x00BEF5F4, 0x00738B0A, 0x00000000, 0x0000006C,
    0x00BEF5E8, 0x0042EFC0, 0x00000000, 0x00000070,
    0x00BEF488, 0x00738B30, 0x00000000, 0x00000074,
    0x00BEF46C, 0x00738B30, 0x00000000, 0x00000078,
    0x00BEF450, 0x0042EFC0, 0x00000000, 0x0000007C,
    0x00BEF440, 0x0042E850, 0x00000000, 0x00000080,
    0x00BEF5D0, 0x00739900, 0x00000000, 0x00000090,
    0x00BEF428, 0x0042EFC0, 0x00000000, 0x00000084,
    0x00BEF410, 0x00738B30, 0x00000000, 0x00000088,
    0x00BEF3FC, 0x00738B30, 0x00000000, 0x0000008C,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c46ec8: 7 entries + terminator (128B).
extern const int s_siegeEngineFieldTable[32] = {
    0x00C46EB8, 0x00761CA5, 0x00000000, 0x0000018C,
    0x00C46EB0, 0x0042EF56, 0x00000000, 0x00000190,
    0x00C46EA4, 0x0087B9AD, 0x00000000, 0x00000000,
    0x00C46E90, 0x0042F1BA, 0x00000000, 0x0000019C,
    0x00C46E7C, 0x0042E850, 0x00000000, 0x000001A0,
    0x00C46E68, 0x00864081, 0x00000000, 0x000001A4,
    0x00C46E54, 0x0042E850, 0x00000000, 0x000001B4,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c48890: 4 entries + terminator (80B).
extern const int s_citadelSlaughterFieldTable[20] = {
    0x00C48878, 0x007B1327, 0x00000000, 0x000000EC,
    0x00C48864, 0x0042F196, 0x00000000, 0x00000100,
    0x00C48848, 0x00761CA5, 0x00000000, 0x000000FC,
    0x00C48838, 0x00738A09, 0x00000000, 0x0000010C,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c4e8b0: 4 entries + terminator (80B).
extern const int s_weaponModeFieldTable[20] = {
    0x00C0D77C, 0x00738B30, 0x00000000, 0x0000001C,
    0x00C3C280, 0x0042F11E, 0x00000000, 0x00000018,
    0x00C4E8A0, 0x0042ECAF, 0x00C00698, 0x00000020,
    0x00C4D9BC, 0x006C8C06, 0x00000000, 0x00000024,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c47208: 6 entries (no terminator) (96B).
extern const int s_hordeSiegeEngineFieldTable[24] = {
    0x00C46EB8, 0x00761CA5, 0x00000000, 0x0000018C,
    0x00C46EB0, 0x0042EF56, 0x00000000, 0x00000190,
    0x00C46EA4, 0x0087B9AD, 0x00000000, 0x00000000,
    0x00C46E90, 0x0042F1BA, 0x00000000, 0x0000019C,
    0x00C46E7C, 0x0042E850, 0x00000000, 0x000001A0,
    0x00C46E68, 0x00864081, 0x00000000, 0x000001A4,
};

// Retail VA 0x00bc6b80: 1 entries + terminator (32B).
extern const int s_hordeModelDrawFieldTable[8] = {
    0x00BC6B74, 0x00479305, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c3a304: 2 entries + terminator (48B).
extern const int s_crowdResponseFieldTable[12] = {
    0x00C3A2FC, 0x0042EF56, 0x00000000, 0x00000004,
    0x00C390D4, 0x00815B91, 0x00000000, 0x00000008,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c0dc20: 13 entries + terminator (224B).
extern const int s_radiusDecalFieldTable[56] = {
    0x00BCA9B0, 0x0042F11E, 0x00000000, 0x00000000,
    0x00C0DC14, 0x0042F11E, 0x00000000, 0x00000004,
    0x00C0DC0C, 0x0042EB38, 0x00DBE6F0, 0x00000008,
    0x00C0DC00, 0x0042F1BA, 0x00000000, 0x0000000C,
    0x00C0DBF4, 0x0042F1BA, 0x00000000, 0x00000010,
    0x00C0DBE0, 0x0042EFC0, 0x00000000, 0x00000014,
    0x00C0DBCC, 0x0042EFC0, 0x00000000, 0x0000002C,
    0x00BCDB38, 0x0042F3FE, 0x00000000, 0x00000018,
    0x00C0DBB0, 0x0042E850, 0x00000000, 0x0000001C,
    0x00C0DBA4, 0x0042EFC0, 0x00000000, 0x00000024,
    0x00C0DB98, 0x0042EFC0, 0x00000000, 0x00000020,
    0x00C0DB84, 0x0042EF72, 0x00000000, 0x00000028,
    0x00C0DB70, 0x0042EFC0, 0x00000000, 0x00000030,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c100c0: 56 entries + terminator (912B).
extern const int s_rva0033A8FCFieldTableB[228] = {
    0x00C100B0, 0x007393DF, 0x00000000, 0x00000000,
    0x00C10090, 0x007393DF, 0x00000000, 0x00000008,
    0x00C1007C, 0x007393DF, 0x00000000, 0x00000010,
    0x00C10070, 0x007393DF, 0x00000000, 0x00000018,
    0x00C10058, 0x007393DF, 0x00000000, 0x00000020,
    0x00C10044, 0x007393DF, 0x00000000, 0x00000028,
    0x00C10038, 0x007393DF, 0x00000000, 0x00000030,
    0x00C10024, 0x007393DF, 0x00000000, 0x00000038,
    0x00C10018, 0x007393DF, 0x00000000, 0x00000040,
    0x00C10008, 0x007393DF, 0x00000000, 0x00000048,
    0x00C0FFF4, 0x007393DF, 0x00000000, 0x00000050,
    0x00C0FFE8, 0x007393DF, 0x00000000, 0x00000058,
    0x00C0FFD8, 0x007393DF, 0x00000000, 0x00000060,
    0x00C0FFCC, 0x007393DF, 0x00000000, 0x00000068,
    0x00C0FFC0, 0x007393DF, 0x00000000, 0x00000070,
    0x00C0FFAC, 0x007393DF, 0x00000000, 0x00000078,
    0x00C0FF94, 0x007393DF, 0x00000000, 0x00000080,
    0x00C0FF84, 0x007393DF, 0x00000000, 0x00000088,
    0x00C0FF6C, 0x007393DF, 0x00000000, 0x00000090,
    0x00C0FF58, 0x007393DF, 0x00000000, 0x00000098,
    0x00C0FF40, 0x007393DF, 0x00000000, 0x000000A0,
    0x00C0FF28, 0x007393DF, 0x00000000, 0x000000A8,
    0x00C0FF10, 0x007393DF, 0x00000000, 0x000000B0,
    0x00C0FEF4, 0x007393DF, 0x00000000, 0x000000B8,
    0x00C0FED8, 0x007393DF, 0x00000000, 0x000000C0,
    0x00C0FEB8, 0x007393DF, 0x00000000, 0x000000C8,
    0x00C0FE98, 0x007393DF, 0x00000000, 0x000000D0,
    0x00C0FE84, 0x007393DF, 0x00000000, 0x000000D8,
    0x00C0FE60, 0x007393DF, 0x00000000, 0x000000E0,
    0x00C0FE40, 0x007393DF, 0x00000000, 0x000000E8,
    0x00C0FE20, 0x007393DF, 0x00000000, 0x000000F0,
    0x00C0FE04, 0x007393DF, 0x00000000, 0x000000F8,
    0x00C0FDE0, 0x007393DF, 0x00000000, 0x00000100,
    0x00C0FDD0, 0x007393F7, 0x00000000, 0x00000108,
    0x00C0FDB8, 0x007393F7, 0x00000000, 0x00000110,
    0x00C0FDA8, 0x007393F7, 0x00000000, 0x00000118,
    0x00C0FD90, 0x007393F7, 0x00000000, 0x00000120,
    0x00C0FD80, 0x007393F7, 0x00000000, 0x00000128,
    0x00C0FD6C, 0x007393F7, 0x00000000, 0x00000130,
    0x00C0FD50, 0x007393F7, 0x00000000, 0x00000138,
    0x00C0FD3C, 0x007393F7, 0x00000000, 0x00000140,
    0x00C0FD28, 0x007393F7, 0x00000000, 0x00000148,
    0x00C0FD18, 0x007393F7, 0x00000000, 0x00000150,
    0x00C0FD08, 0x007393F7, 0x00000000, 0x00000158,
    0x00C0FCF8, 0x007393F7, 0x00000000, 0x00000160,
    0x00C0FCE8, 0x007393F7, 0x00000000, 0x00000168,
    0x00C0FCD0, 0x007393F7, 0x00000000, 0x00000170,
    0x00C0FCC4, 0x007393F7, 0x00000000, 0x00000178,
    0x00C0FCB8, 0x007393F7, 0x00000000, 0x00000180,
    0x00C0FCA0, 0x007393F7, 0x00000000, 0x00000188,
    0x00C0FC8C, 0x007393F7, 0x00000000, 0x00000190,
    0x00C0FC78, 0x007393F7, 0x00000000, 0x00000198,
    0x00C0FC60, 0x007393F7, 0x00000000, 0x000001A0,
    0x00C0FC54, 0x007393F7, 0x00000000, 0x000001A8,
    0x00C0FC40, 0x007393F7, 0x00000000, 0x000001B0,
    0x00C0FC30, 0x007393F7, 0x00000000, 0x000001B8,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c4c0c0: 4 entries + terminator (80B).
extern const int s_fireWeaponNuggetFieldTableA[20] = {
    0x00C1B1E8, 0x0042F11E, 0x00000000, 0x00000000,
    0x00C4C0B4, 0x00738B30, 0x00000000, 0x00000004,
    0x00BF01D8, 0x0042E850, 0x00000000, 0x00000008,
    0x00BCA628, 0x0042F507, 0x00000000, 0x0000000C,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c51380: 6 entries + terminator (112B).
extern const int s_fireWeaponNuggetFieldTableB[28] = {
    0x00C40DDC, 0x0042F11E, 0x00000000, 0x00000000,
    0x00C51370, 0x00761CA5, 0x00000000, 0x00000004,
    0x00C51360, 0x0042EFC0, 0x00000000, 0x00000008,
    0x00C51350, 0x0042EFC0, 0x00000000, 0x0000000C,
    0x00C51340, 0x0042E850, 0x00000000, 0x00000010,
    0x00C51334, 0x0042E850, 0x00000000, 0x00000011,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00bcd6b0: 6 entries + terminator (112B).
extern const int s_floorDrawFieldTable[28] = {
    0x00BCB090, 0x0042E850, 0x00000000, 0x0000001C,
    0x00BCD6A4, 0x0042E850, 0x00000000, 0x0000001D,
    0x00BCD698, 0x0042E850, 0x00000000, 0x0000001E,
    0x00BCD67C, 0x0042EFC0, 0x00000000, 0x00000020,
    0x00BCD66C, 0x004CF873, 0x00000000, 0x00000010,
    0x00BCD654, 0x004CF713, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail string at VA 0x00CE7AA8 ("GeometryType"): referenced by
// Rva006BD490RawDispatch as a const-void pointer argument.
extern const char s_geometryTypeString[] = "GeometryType";

// LK2 round 2: FieldParse tables already named by their user TUs (kept here
// in the debt absorber so the users link). Exact retail bytes.
struct FieldParse { unsigned d[4]; };

// Retail VA 0x00bc16e8: 74 entries (1200B).
extern const FieldParse g_00BC16E8[75] = {
    {0x00BC2414, 0x0042E850, 0x00000000, 0x00000054},
    {0x00BC240C, 0x0042E850, 0x00000000, 0x00000055},
    {0x00BC2400, 0x0042EF56, 0x00000000, 0x00000058},
    {0x00BC23F4, 0x0042EF56, 0x00000000, 0x0000005C},
    {0x00BC23E4, 0x0042EF56, 0x00000000, 0x00000060},
    {0x00BC23D4, 0x0042EF56, 0x00000000, 0x00000064},
    {0x00BC23C4, 0x0042EF56, 0x00000000, 0x00000068},
    {0x00BC23B8, 0x0042EF56, 0x00000000, 0x0000006C},
    {0x00BC23A8, 0x0042EF72, 0x00000000, 0x00000084},
    {0x00BC238C, 0x0042EF72, 0x00000000, 0x00000088},
    {0x00BC2378, 0x0042EF72, 0x00000000, 0x0000008C},
    {0x00BC2350, 0x0042EF72, 0x00000000, 0x00000090},
    {0x00BC2334, 0x0042EF56, 0x00000000, 0x00000094},
    {0x00BC2314, 0x0042EF56, 0x00000000, 0x00000098},
    {0x00BC22FC, 0x0042EF56, 0x00000000, 0x0000009C},
    {0x00BC22DC, 0x0042F3FE, 0x00000000, 0x000000A0},
    {0x00BC22C0, 0x0042F3FE, 0x00000000, 0x000000A4},
    {0x00BC22A8, 0x0042EF56, 0x00000000, 0x000000A8},
    {0x00BC228C, 0x0042EF56, 0x00000000, 0x000000AC},
    {0x00BC2278, 0x0042E850, 0x00000000, 0x000000BC},
    {0x00BC2268, 0x0042F1BA, 0x00000000, 0x000000C0},
    {0x00BC223C, 0x0042EF56, 0x00000000, 0x000000B4},
    {0x00BC222C, 0x0042F1BA, 0x00000000, 0x000000B8},
    {0x00BC220C, 0x0042EFC0, 0x00000000, 0x000000B0},
    {0x00BC21FC, 0x0042EF56, 0x00000000, 0x00000070},
    {0x00BC21EC, 0x0042EF56, 0x00000000, 0x00000074},
    {0x00BC21DC, 0x0042EF56, 0x00000000, 0x00000078},
    {0x00BC21BC, 0x0042EF56, 0x00000000, 0x0000007C},
    {0x00BC21A4, 0x0042EF72, 0x00000000, 0x00000080},
    {0x00BC2180, 0x0042F1BA, 0x00000000, 0x000000C8},
    {0x00BC2164, 0x0042F1BA, 0x00000000, 0x000000CC},
    {0x00BC2144, 0x0042F1BA, 0x00000000, 0x000000D0},
    {0x00BC2120, 0x0042F1BA, 0x00000000, 0x000000D4},
    {0x00BC2100, 0x0042F1BA, 0x00000000, 0x000000D8},
    {0x00BC20DC, 0x0042F1BA, 0x00000000, 0x000000DC},
    {0x00BC20B8, 0x0042F1BA, 0x00000000, 0x000000E0},
    {0x00BC209C, 0x0042F1BA, 0x00000000, 0x000000E4},
    {0x00BC2080, 0x0042F1BA, 0x00000000, 0x000000E8},
    {0x00BC2060, 0x0042F1BA, 0x00000000, 0x000000EC},
    {0x00BC2038, 0x0042F1BA, 0x00000000, 0x000000F0},
    {0x00BC2018, 0x0042F1BA, 0x00000000, 0x000000F4},
    {0x00BC1FF4, 0x0042F1BA, 0x00000000, 0x000000F8},
    {0x00BC1FD8, 0x0042F1BA, 0x00000000, 0x000000FC},
    {0x00BC1FB8, 0x0042F1BA, 0x00000000, 0x00000100},
    {0x00BC1F9C, 0x0042F1BA, 0x00000000, 0x00000104},
    {0x00BC1F7C, 0x0042F1BA, 0x00000000, 0x00000108},
    {0x00BC1F5C, 0x0042F1BA, 0x00000000, 0x0000010C},
    {0x00BC1F40, 0x0042F1BA, 0x00000000, 0x00000110},
    {0x00BC1F1C, 0x0042F1BA, 0x00000000, 0x00000114},
    {0x00BC1EFC, 0x0042F1BA, 0x00000000, 0x00000118},
    {0x00BC1ED8, 0x0042F1BA, 0x00000000, 0x0000011C},
    {0x00BC1EB8, 0x0042F1BA, 0x00000000, 0x00000120},
    {0x00BC1E9C, 0x0042F1BA, 0x00000000, 0x00000124},
    {0x00BC1E7C, 0x0042F1BA, 0x00000000, 0x00000128},
    {0x00BC1E50, 0x0042F1BA, 0x00000000, 0x0000012C},
    {0x00BC1E20, 0x0042F1BA, 0x00000000, 0x00000144},
    {0x00BC1E00, 0x0042EFC0, 0x00000000, 0x00000134},
    {0x00BC1DE0, 0x0042EFC0, 0x00000000, 0x0000013C},
    {0x00BC1DD0, 0x0042EFC0, 0x00000000, 0x00000148},
    {0x00BC1DC0, 0x0042EFC0, 0x00000000, 0x00000150},
    {0x00BC1DA0, 0x0042F1BA, 0x00000000, 0x00000158},
    {0x00BC1D80, 0x0042EFC0, 0x00000000, 0x0000015C},
    {0x00BC1D60, 0x0042EFC0, 0x00000000, 0x00000164},
    {0x00BC1D40, 0x0042EFC0, 0x00000000, 0x0000016C},
    {0x00BC1D08, 0x0042F1BA, 0x00000000, 0x00000174},
    {0x00BC1CDC, 0x0042EFC0, 0x00000000, 0x0000017C},
    {0x00BC1CB0, 0x0042EFC0, 0x00000000, 0x00000184},
    {0x00BC1C94, 0x0042EFC0, 0x00000000, 0x00000190},
    {0x00BC1C78, 0x0042EFC0, 0x00000000, 0x00000198},
    {0x00BC1C3C, 0x0042F1BA, 0x00000000, 0x0000018C},
    {0x00BC1C10, 0x0042F1BA, 0x00000000, 0x000001A0},
    {0x00BC1BE8, 0x0042EFC0, 0x00000000, 0x000001A4},
    {0x00BC1BC0, 0x0042EFC0, 0x00000000, 0x000001AC},
    {0x00BC1B98, 0x0042EFC0, 0x00000000, 0x000001B4},
    {0x00000000, 0x00000000, 0x00000000, 0x00000000},
};

// Retail VA 0x00c61c68: 3 entries (64B).
extern const FieldParse g_00C61C68[4] = {
    {0x00C618F8, 0x0042F0F7, 0x00000000, 0x00000004},
    {0x00BDC1C0, 0x00739900, 0x00000000, 0x00000008},
    {0x00C618D0, 0x0042E850, 0x00000000, 0x0000000C},
    {0x00000000, 0x00000000, 0x00000000, 0x00000000},
};

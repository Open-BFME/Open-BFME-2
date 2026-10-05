// cl: /O2 /Ob0
//
// Ported from Open-BFME-1's game/GameEngine/Source/Common/Rva0090C280Ctor.cpp
// (donor revision: reference/open-bfme-1 @ a38d345e) by tools/bfme1_sweep.py,
// which found this body byte-identical between lotrbfme.exe and game.dat once
// relocation slots are set aside: 0x0090C2D0 (20B) -> 0x001310CF (20B), tier T1
// "clean transfer", cl: /O2 /Ob0.
//
// The donor file is served whole-file by bfme1_sweep, and it was held at
// copy-tier S because it also defines Rva0090C280::Rva0090C280(), which the
// sweep did NOT place. The commit hook's find_declared_unmatched gate refuses a
// source that defines any function the ledger lacks, so one unplaceable body
// was blocking the whole file. This TU therefore carries ONLY the placed body.
// The class still declares the same members, because the member offsets are
// what the body's byte shape depends on, but the ctor is deliberately not
// defined here -- adding it would re-trip the same gate.
//
// AGENTS.md sanctions this: "Port supported bodies into an allowed Code/ TU,
// preserve the donor revision, flags and dependencies."
//
// ONE body needed repair, and it is the reason the sweep's masked comparison
// called this a clean transfer. The donor writes its vtable as a hardcoded
// literal -- `m_vptr = (void *)0x0113A56C`, BFME 1's vtable -- and a literal
// compiles to an inline immediate, NOT a relocation slot. The sweep blanks
// relocation slots before comparing, so that 4-byte difference was invisible to
// it, and the build's DIR32 copy-from-retail cannot fix it either. The
// disassembly of 0x001310CF gives the value this game uses: 0x00BD25C8.
// Changing just that constant takes the body from "instruction/register
// encoding mismatch at +0x2" to an exact match, with the remaining 16 bytes
// identical throughout.

extern "C" const void *const vtbl_00BD25C8[];  // ??_7Rva0013107A@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BD25C8=??_7Rva0013107A@@6B@")

class Rva0090C280
{
	void *m_vptr;
	char m_04;
	void *m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;

public:
	void releaseResource0090C2D0();
};

void Rva0090C280::releaseResource0090C2D0()
{
	m_vptr = (void *)((unsigned int)vtbl_00BD25C8);
	void *resource = m_08;
	if (resource) {
		void (__stdcall *destroy)(void *) = ((void (__stdcall **)(void *))*(void **)resource)[2];
		destroy(resource);
	}
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:??1Rva0013107A@@UAE@XZ=?releaseResource0090C2D0@Rva0090C280@@QAEXXZ")

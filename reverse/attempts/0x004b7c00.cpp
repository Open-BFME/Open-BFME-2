// ??0AudioLoopUpgradeModuleData@@QAE@XZ
// partial score=0.7 date=2026-09-21
// ??0AudioLoopUpgradeModuleData@@QAE@XZ
// partial score=0.7 date=2026-09-21
// cl: /O1 /MD /GX /DNDEBUG
//
// ??0AudioLoopUpgradeModuleData@@QAE@XZ, retail 0x004B7C00, 76 bytes. EH
// ctor, standalone (no base call): xor-zero, vtable literal 0x00C58CF8,
// single state-0 store, two compact mov-zero stores at +0x08/+0x0C, lea of
// the +0x14 member, single state-1 store, zero/false at +0x0C/+0x10,
// construction of the +0x14 member through the rowed
// ?construct@Rva0025342CMember call at 0x25342C, lea of the +0x124 member,
// init through ?init@DieMuxData at 0x4CE534 (pinned with this bank:
// 11 member-position callers, +8-first-member pattern, SlowDeath-first
// BFME1 donor, ZH OpenContain.h first-member, frameless-0x30 bitset/float
// shape). Size 0x154 matches the rowed factory at 0x250798 (sole caller).
// Class identity is the table behind the rowed 45B proc (SoundToPlay at
// +0x08, KillAfterMS at +0x0C, KillOnDeath at +0x10) beside the rowed
// AudioLoopUpgrade pool key.
//
// Best shape (nofilterdtor: DieMuxData-dtor only, 72/76): xor, lea14,
// state0, vtable, mov8, movC, mov10, construct, lea124, init. Walls: (1)
// lea hoists above vtable in every variant (needs vtable-above-lea lever);
// (2) single state0 only (2-member-dtor variants collapse to a single
// state1 with and-zeros; empty-base 3-dtor variant gives state2-only);
// (3) mov-vs-and zeros flip with the state configuration (single-dtor
// gives movs, multi-dtor gives ands). Refuted: int/ptr/chain zero
// spellings (identical ands), init-list vtable+zeros (same), cast
// address-takes (same), /G6 /G7 /O2 /Ot /Og- /Ob0 /Oi- flags, empty base,
// initvtable-cast. Retail wants single-dtor FORM (movs+xor) with
// two-dtor STATES (0+1) plus vtable-above-lea: contradictory under all
// probed configurations. Needs a new EH-state/scheduling lever.
// Do NOT retry blind; try an empty-base-with-call variant or a fresh
// counting theory first.

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();
	~Rva0025342CMember();

	unsigned char m_data[0x110];
};

class DieMuxData
{
public:
	void init();
	~DieMuxData();

	unsigned char m_data[0x30];
};

class AudioLoopUpgradeModuleData
{
public:
	AudioLoopUpgradeModuleData();

private:
	void *m_vtable; // +0
	unsigned char m_pad04[4]; // +4
	int m_soundToPlay; // +0x08
	int m_killAfterMS; // +0x0C
	bool m_killOnDeath; // +0x10
	unsigned char m_pad11[3]; // +0x11..0x13 (align member to 0x14)
	Rva0025342CMember m_filter; // +0x14
	DieMuxData m_dieMux; // +0x124
};

// ??0AudioLoopUpgradeModuleData@@QAE@XZ @0x4B7C00
AudioLoopUpgradeModuleData::AudioLoopUpgradeModuleData()
{
	m_vtable = reinterpret_cast<void *>(0x00C58CF8);
	m_soundToPlay = 0;
	m_killAfterMS = 0;
	m_killOnDeath = true;
	m_filter.construct();
	m_dieMux.init();
}

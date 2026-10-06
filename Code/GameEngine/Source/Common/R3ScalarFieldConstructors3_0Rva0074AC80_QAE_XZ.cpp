// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Dedicated TU for Rva0074AC80::Rva0074AC80 from the BFME1 donor
// game/GameEngine/Source/Common/R3ScalarFieldConstructors3.cpp
// (reference/open-bfme-1). Only this one placed body is defined here; the
// donor's fifteen other definitions are omitted.
//
// Donor preamble follows.
//
// Sixteen more bodies from the same shape as R3ScalarFieldConstructors.cpp --
// fifteen constant-field constructors plus one setter that writes through a
// global pointer.  Two mnemonic families land here: the ten-store group
// anchored at 0x0013A8B0 and the eleven-store group anchored at 0x00299DE0.
//
// THE TWO ODD BODIES, AND WHAT THEY COST.
//
// Rva0023E250 stores +0x14 and +0x18, then +0 and a byte at +0x1C, then
// stores +0x14 and +0x18 AGAIN.  Rva00299DE0 zeroes +0..+0x10 and then RELOADS
// +0xC into edx to store it at +0x18.  Written as plain members, MSVC deletes
// the first pair and forwards the zero -- the shorter body is what a plain
// spelling produces, and it is not what retail has.  Marking only the fields
// involved `volatile` keeps the accesses but HOISTS them out of source order,
// which is also wrong.  Declaring EVERY field of those two classes volatile is
// the one spelling found that reproduces the retail byte string exactly.
//
// That is a byte-level fact, not an identity claim: this file does NOT assert
// that retail wrote `volatile`.  What the bytes establish is only that in those
// two bodies the stores were neither eliminable nor reorderable.  A different
// cause -- a differently configured translation unit, an intervening construct
// this reconstruction has not found -- would be equally consistent.  Every
// other body here compiles from plain members.
//
// Rva006E1B30 is not a constructor.  It never touches `this` until the last
// instruction, reads a global pointer FOUR SEPARATE TIMES, and writes five
// fields of the pointee.  The reloads are the evidence: a store through the
// pointer may alias the pointer variable itself, so the compiler cannot keep it
// in a register across them.  ecx survives untouched to the final
// `mov [ecx+0xA8],3`, which makes this a __thiscall member returning void.
// `mov al,1` serves both byte stores, and eax is reloaded afterwards because
// that write destroyed the cached pointer.
//
// The FIRST TWO writes share one load and the last three do not, so they are
// not spelled the same way in source.  Five plain `g->field = ...` statements
// reload before every store (63 bytes).  Binding a reference to the pointee
// once and using it for the first two, then naming the global directly for the
// rest, is what produces retail's four loads in 56 bytes.  Which of the two
// halves the original author wrote "differently" is decided by the bytes; what
// the construct meant to them is not.
//
// IDENTITY IS NOT RECOVERED: names are addresses and offsets, relocated
// immediates are the addresses of externs named for those addresses, and
// build.py fills those four bytes from retail, so they carry no evidence.

class Rva0074AC80
{
public:
	Rva0074AC80();
	int m_00, m_04, m_08, m_0C, m_10;
	int m_14, m_18, m_1C, m_20, m_24;
};
Rva0074AC80::Rva0074AC80()
{
	m_00 = -1;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
}

// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// One of the BFME 1 zeroing-constructor family:
//
//     mov eax,ecx / xor ecx,ecx / <four or five member stores> / ret
//
// WHAT THE BYTES SHOW. `mov eax,ecx` defines eax, is never read again inside
// the body, and the function ends in a bare `ret`: that is the __thiscall
// CONSTRUCTOR TAIL returning `this`, and it is why this is written as a
// constructor rather than a void member.
//
// THE STORE ORDER IS SOURCE ORDER. MSVC 7.1 emits member initialisation in
// the order it is written, so this body is transcribed as retail emits it:
// +4, +8, +0xC, and only then the +0 pointer LAST.
//
// THE LEADING +0 STORE IS NOT PROVEN A VPTR, AND THIS BODY PROVES IT. MSVC
// always writes the vptr before any member initialiser, so a body whose +0
// store comes last structurally cannot be one -- and since this class plainly
// holds an ordinary pointer-valued member at +0, the identical leading store in
// the family's other bodies is written the same way rather than asserting a
// polymorphic class. The bytes do not distinguish the two for the leading case.
//
// The address that store holds is a DIR32 site the patcher fills from retail.
// R2Data01088838 is an address-derived placeholder and carries no type
// information, per the donor's own note. Nothing in the image names the object
// at that address, so the row claims the bytes without asserting an identity.
//
// IDENTITY IS NOT RECOVERED. The class and member names are derived from an
// address.

extern int R2Data01088838;
// R2Data01088838: retail stores 0x00C035D0 (12585936) at this DIR32 site. That
// VA lies past the last loaded section of the image, so it is recorded as the
// literal retail carries rather than as a resolvable pin.
int R2Data01088838 = 12585936;

// ??0Rva00106B40@@QAE@XZ
// retail 0x002D7667, 21 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/R2ZeroingConstructors.cpp
// (reference/open-bfme-1 @ 6d943426). Byte-identical to retail once
// relocations are masked (unique hit on unclaimed .text). Only the placed body
// is defined here; the donor's other 33 constructors are omitted.

class Rva00106B40
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	Rva00106B40();
};
Rva00106B40::Rva00106B40()
{
	m_at00 = &R2Data01088838;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = -1;
}
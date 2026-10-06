// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// One of the BFME 1 zeroing-constructor family:
//
//     mov eax,ecx / xor ecx,ecx / <four or five member stores> / ret
//
// `mov eax,ecx` defines eax and is never read again, and the body ends in a
// bare `ret`: that is the __thiscall CONSTRUCTOR TAIL returning `this`, which
// is why this is spelled as a constructor and not a void member. `xor ecx,ecx`
// materialises the zero once and each zero store then spells it `mov [eax+K],
// ecx`, so the compiler saw two or more zero initialisers.
//
// THE STORE ORDER IS SOURCE ORDER. MSVC 7.1 emits member initialisation in the
// order it is written, and this body is one of the four that prove it by NOT
// being in ascending offset order: it stores +8, then +4, then +0, then +0xC,
// then +0x10. Transcribed here in the order retail emits.
//
// No member here is a vptr. MSVC always writes a vptr before any member
// initialiser, and this body has no leading absolute store at all -- every
// store is a register write -- so the class cannot be polymorphic.
//
// IDENTITY IS NOT RECOVERED. The class and member names are derived from an
// address.

// ??0Rva00670130@@QAE@XZ
// retail 0x005DA4C8, 20 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/R2ZeroingConstructors.cpp
// (reference/open-bfme-1 @ 6d943426). Byte-identical to retail once
// relocations are masked (unique hit on unclaimed .text). Only the placed body
// is defined here; the donor's other 33 constructors are omitted.

class Rva00670130
{
public:
	int m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	int m_at10;
	Rva00670130();
};
Rva00670130::Rva00670130()
{
	m_at08 = 0;
	m_at04 = 0;
	m_at00 = -1;
	m_at0C = 0;
	m_at10 = 0;
}
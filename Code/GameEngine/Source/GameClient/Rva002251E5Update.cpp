// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// platformsdk
// ?rva002251E5@Rva00222A8BTarget@@QAEXXZ @0x002251E5 (180B): frameless
// window-manager frame update on the Rva00222A8BTarget layout proven by the
// rowed 0x00224818 in Rva00224818.cpp (14 stride-0x28 entries at +0xF0,
// refresh flag at +0x308, same union idiom extended here to the +0x30C
// tick and +0x310/+0x311/+0x312/+0x328/+0x329 bytes this body touches).
// IME/slot flags, per-slot refresh through the rowed AptPlayer::LoadLevel 0x00222E29,
// Eva walk through the rowed static 0x004114EF, self update
// through rowed 0x00224818, throttle math off timeGetTime, notify through
// pinned cdecl 0x006CF1B0, presence through rowed 0x006CD100, then a tail
// thiscall to AptPlayer::HandleOverButtons 0x00224F6C. Address-derived method name; the class
// attribution rests on the shared layout plus the self-call. No virtuals:
// retail installs no vtable here.
#include <windows.h>
#include <mmsystem.h>

#include "../../Include/GameClient/Shell.h"
extern Shell *TheShell;

typedef bool Bool;

struct RvaFlags
{
	Bool m_bit0 : 1;
	Bool m_bit1 : 1;
	Bool m_bit2 : 1;
	Bool m_hasFocus : 1;
};

struct RvaEntry
{
	RvaFlags m_flags;
	char m_pad[0x28 - 1];
};

// The rowed static 0x004114EF Eva walk.
class Rva004114EF
{
public:
	static void rva004114EF();
};
void Rva006CF1B0(int delay);
bool Rva006CD100Get();

// The tail call reaches AptPlayer::HandleOverButtons (0x00224F6C, rowed in
// AptPlayer.cpp; WB B905A0): this layout is the same player object.
#include "../../../Libraries/Source/Apt/AptPlayerClass.h"

class Rva00222A8BTarget
{
public:
	void rva00224818();
	void rva002251E5();
private:
	char m_pad0[0xF0];
	union
	{
		RvaEntry m_entries[14];
		struct
		{
			char m_pad1[0x218]; // +0xF0..+0x308
			bool m_b308; // +0x308 refresh flag
			unsigned char m_b309; // +0x309 untouched
			unsigned char m_b30A; // +0x30A untouched
			unsigned char m_b30B; // +0x30B untouched
			unsigned long m_tickLast; // +0x30C last tick
			bool m_b310; // +0x310 IME flag
			bool m_b311; // +0x311 slot flag
			bool m_b312; // +0x312 notify flag
			char m_pad2[0x15]; // +0x313..+0x327 untouched
			bool m_b328; // +0x328 throttle flag
			bool m_b329; // +0x329 presence result
		};
	};
};

void Rva00222A8BTarget::rva002251E5()
{
	// Bool flag phrasing mirrors the rowed 0x00224818 in Rva00224818.cpp
	// (if (!m_needsRefresh) / = false): plain bool member access lets the
	// compiler keep the address and materialize the zero in bl; explicit
	// pointer locals compared against imm0 instead.
	if (m_b310)
	{
		TheShell->pop();
		m_b310 = false;
	}
	if (m_b311)
	{
		m_b311 = false;
		int i = 0;
		RvaEntry *entry = m_entries;
		for (; i < 14; i++, entry++)
		{
			if (entry->m_flags.m_bit0)
				reinterpret_cast<AptPlayer *>(this)->LoadLevel(i);
		}
		m_b308 = true;
	}
	Rva004114EF::rva004114EF();
	rva00224818();
	unsigned long now = timeGetTime();
	unsigned long elapsed = now - m_tickLast;
	if (elapsed > 0x3C)
		elapsed = 0x3C;
	if (m_b328 && elapsed < 0x22)
		elapsed = 0x22;
	m_b328 = false;
	m_b312 = true;
	Rva006CF1B0(elapsed);
	m_b312 = false;
	m_tickLast = now;
	m_b329 = Rva006CD100Get();
	reinterpret_cast<AptPlayer *>(this)->HandleOverButtons();
}

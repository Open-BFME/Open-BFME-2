// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?rva002251E5@Rva00222A8BTarget@@QAEXXZ @0x002251E5 (180B): frameless
// window-manager frame update on the Rva00222A8BTarget layout proven by the
// rowed 0x00224818 in Rva00224818.cpp (14 stride-0x28 entries at +0xF0,
// refresh flag at +0x308, same union idiom extended here to the +0x30C
// tick and +0x310/+0x311/+0x312/+0x328/+0x329 bytes this body touches).
// IME/slot flags, per-slot refresh through the pinned thiscall 0x00222E29,
// Eva walk through the pinned static alias of rowed 0x004114EF, self update
// through rowed 0x00224818, throttle math off timeGetTime, notify through
// pinned cdecl 0x006CF1B0, presence through rowed 0x006CD100, then a tail
// thiscall to pinned 0x00224F6C. Address-derived method name; the class
// attribution rests on the shared layout plus the self-call. No virtuals:
// retail installs no vtable here.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class Shell
{
public:
	void rva0035BEC7();
};
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

void Rva004114EFStatic();
void Rva006CF1B0(int delay);
bool Rva006CD100Get();

class Rva00222A8BTarget
{
public:
	void rva00224818();
	void rva00222E29(int index);
	void rva00224F6C();
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
		TheShell->rva0035BEC7();
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
				rva00222E29(i);
		}
		m_b308 = true;
	}
	Rva004114EFStatic();
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
	rva00224F6C();
}

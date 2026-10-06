// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Retail 0x00445172, 159 bytes: slot 3 of the input-route vftable at
// 0x00C3DFA8 (slots 1/2 are the rowed Rva0031455E link/unlink), placed right
// after the jump table of Rva00445086ClientStateName. It filters
// GWM_IME_CHAR for a LAN text entry: ',' ':' ';' are swallowed, and once the
// entry text reaches its length limit alphanumerics are swallowed too;
// everything else forwards to the base route at 0x00314596 (the base
// vftable 0x00C0BBF8 holds it in the same slot).
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameClient/GUI/Gadget/
// Rva00517870TextEntryInput.cpp (f57439f7f4), the BFME1 neighbour of the
// ClientStateName donor. Target deltas: the cursor test is the rowed
// predicate Rva00516660 0x00444016 instead of the inlined user-data compare,
// and the limit is 10 characters instead of 12. The fallback uses the
// existing j_00003df0 pin at 0x00314596, as the sibling
// Rva004BE120TextEntryInput.cpp does.

// Retail calls the CRT iswalnum import, not wchar.h's inline iswctype wrapper.
#define _WCTYPE_INLINE_DEFINED
#include <wchar.h>
#include "unicode_string.h"

class GameWindow;

extern UnicodeString GadgetTextEntryGetText(GameWindow *window);
extern bool Rva00516660(GameWindow *window);
extern void j_00003df0();

struct Rva00445172StringData
{
	int m_refs;
	unsigned short m_length;
	unsigned short m_capacity;
};

class Rva00445172Owner
{
public:
	int rva00445172(unsigned int message, unsigned int data1,
		unsigned int data2);

private:
	char m_pad00[8];
	GameWindow *m_entry;
};

int Rva00445172Owner::rva00445172(unsigned int message, unsigned int data1,
	unsigned int data2)
{
	// Retail's /O1 block order (shared epilogue before the fallback) needs the
	// switch form; the equivalent if-chain places the fallback first.
	switch (message)
	{
	case 0x19: // GWM_IME_CHAR
	{
		unsigned short ch = (unsigned short)data1;
		if (ch == ',' || ch == ':' || ch == ';')
			return 1;
		if (!Rva00516660(m_entry))
		{
			UnicodeString text = GadgetTextEntryGetText(m_entry);
			Rva00445172StringData *str = *(Rva00445172StringData **)&text;
			int length = str ? (int)str->m_length : 0;
			if (length >= 10 && iswalnum(ch))
				return 1;
		}
		break;
	}
	}
	typedef int (Rva00445172Owner::*Fallback)(
		unsigned int, unsigned int, unsigned int);
	union { void (*raw)(); Fallback member; } route;
	route.raw = ::j_00003df0;
	return (this->*route.member)(message, data1, data2);
}

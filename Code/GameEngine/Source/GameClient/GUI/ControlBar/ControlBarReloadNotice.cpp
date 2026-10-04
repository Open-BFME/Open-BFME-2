// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// The "needs restart" byte at VA 0x00E01D0C and the two bodies that touch it:
//
//   0x0031AB77  sets it (8 bytes).
//   0x0031E7F0  slot 4 of vftable 0x00C0CC88 (the class whose deleting
//               destructor is 0x0031EB7A), the INI reload notice: clear the
//               byte, and when the class's own slot 2 reports a reload put
//               "RIF: ControlBar ... reloaded" on screen through TheInGameUI (its
//               slot 16, cdecl), call 0x00409FCC on every value of the
//               AsciiString-keyed hash map at +0x30, walk the +0x2C
//               list (0x0031AC39), latch +0x28 and answer true; a byte set
//               meanwhile is passed out through the argument and cleared.
//
// Target evidence: the reload notice's codegen loads the vptr before it
// stores the byte, which MSVC 7.1 only does when the byte is a file-static
// it can prove `this` does not alias (an extern byte keeps the store first),
// so the byte is file-static here and its setter, which sits beside
// 0x0031AC39 in the same address range, lives in this unit too. The classes
// keep their address-derived names; the message and map meanings are
// inferred from the callees.

#include "ascii_string.h"
#include "unicode_string.h"
#include <hash_map>

// g_Va00E01D0C: VA 0x00E01D0C (.bss); retail initial byte 00.
static bool g_Va00E01D0C;

void Rva0031AB77SetFlag(void)
{
	g_Va00E01D0C = 1;
}

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void __cdecl message(UnicodeString format, ...);
};
extern InGameUI *TheInGameUI;	// VA 0x00DFEDF0

namespace rts
{
template <class T> struct hash
{
	unsigned int operator()(T value) const;
};
}

// The map's values: each gets 0x00409FCC (rowed under this address name).
class Rva00409FFA
{
public:
	void rva00409FCC();
};

// AsciiString-keyed: retail advances it with the iterator increment 0x00411084
// that the rts::hash<AsciiString> maps share (ICF); begin is the shared
// 0x00427195. The pointer value sits at node +8. The equality functor is not
// evidenced by these bytes.
typedef _STL::hash_map<AsciiString, Rva00409FFA *, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > Rva0031E7F0Map;

// View of the object 0x0031AC39 walks; polymorphic here so the derived
// class below shares its address.
class Rva0031AC39
{
public:
	virtual void v00();
	virtual void v01();
	virtual bool v02();	// 0x0031B53D in vftable 0x00C0CC88
	void rva0031AC39();
};

class Rva0031DCF0 : public Rva0031AC39
{
public:
	bool rva0031E7F0(bool *needsRestart);
private:
	char m_unmodelled04[0x28 - 0x04];
	bool m_reloaded28;
	void *m_list2C;
	Rva0031E7F0Map m_map30;
};

bool Rva0031DCF0::rva0031E7F0(bool *needsRestart)
{
	bool result = false;
	g_Va00E01D0C = result;
	if (v02())
	{
		TheInGameUI->message(UnicodeString(L"RIF: ControlBar (CommandSet/CommandButton) reloaded. Changes effective immediately."));
		for (Rva0031E7F0Map::iterator it = m_map30.begin(); it != m_map30.end(); ++it)
		{
			(*it).second->rva00409FCC();
		}
		rva0031AC39();
		m_reloaded28 = true;
		result = true;
	}
	if (g_Va00E01D0C)
	{
		*needsRestart = true;
		g_Va00E01D0C = false;
	}
	return result;
}

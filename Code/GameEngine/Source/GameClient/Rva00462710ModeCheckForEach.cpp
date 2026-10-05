// cl: /O1 /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stringinline
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameClient/Rva00462710ModeCheckForEach.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// ??$for_each@U?$_Ht_iterator@URva0045F0A0 0x004113F4 (95B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.

// Retail 0x00462710 is the STLport for_each instantiation called by the two
// mode-check setup routines at 0x00462CB0 and 0x00462D40. The table value keeps
// its hash key at offset zero, while process reads the record name at offset 0x10.

#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
#include <hash_map>

#include "StringInline.h"

struct Rva0045F0A0Input
{
	AsciiString m_key;
	unsigned char m_padding00[0x0c];
	AsciiString m_name;
	void *m_unit;
};

class Rva0045F0A0
{
public:
	Rva0045F0A0(bool enabled, const char *name);
	Rva0045F0A0(const Rva0045F0A0 &other)
		: m_enabled(other.m_enabled), m_name(other.m_name) {}
	~Rva0045F0A0() {}

	void process(Rva0045F0A0Input *input);
	void operator()(Rva0045F0A0Input &input)
	{
		process(&input);
	}

private:
	char m_enabled;
	unsigned char m_padding01[3];
	AsciiString m_name;
};

namespace rts
{
	template <class T> struct hash
	{
		unsigned int operator()(T value) const
		{
			const char *text = value.str();
			int result = 0;
			while (*text != 0)
			{
				result = result * 5 + *text;
				++text;
			}
			return result;
		}
	};
}

struct Rva0045F0A0ExtractKey
{
	const AsciiString &operator()(const Rva0045F0A0Input &value) const
	{
		return value.m_key;
	}
};

typedef _STL::hashtable<Rva0045F0A0Input, AsciiString, rts::hash<AsciiString>,
	Rva0045F0A0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0045F0A0Input> > Rva0045F0A0Table;

template Rva0045F0A0 _STL::for_each<Rva0045F0A0Table::iterator,
	Rva0045F0A0>(Rva0045F0A0Table::iterator, Rva0045F0A0Table::iterator,
	Rva0045F0A0);

// The global Apt callbacks bound as "EnableComponents" and "DisableComponents"
// through the 0x0023E8D8 holder by the global registration (sites 0x00412531
// and 0x004124ED); the bindings are their only references. With a non-empty
// name each runs the functor above (its constructor is rowed at 0x004104AB as
// Rva004104AB) over the component table 0x00E02FE4, whose STLport begin is
// retail's shared 0x00427195; with none it clears or sets bit 0 of
// 0x00E02FC0 (Bfme5SmallTests.cpp's g_rva00E02FC0Bits), and the disable path
// also drops TheWindowManager's focus (slot 0xC4, winSetFocus).
extern Rva0045F0A0Table g_Va00E02FE4ComponentTable;
#pragma comment(linker, "/alternatename:?g_Va00E02FE4ComponentTable@@3V?$hashtable@URva0045F0A0Input@@VAsciiString@@U?$hash@VAsciiString@@@rts@@URva0045F0A0ExtractKey@@U?$equal_to@VAsciiString@@@_STL@@V?$allocator@URva0045F0A0Input@@@7@@_STL@@A=?g_Va00E02FE4@@3URva004114EFGlobalTable@@A")
extern unsigned int g_rva00E02FC0Bits;

class GameWindow;

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48)
#undef V
	virtual int winSetFocus(GameWindow *window) = 0;
};

extern GameWindowManager *TheWindowManager;

void EnableComponents(const char *name)
{
	if (name != 0 && *name != 0)
	{
		Rva0045F0A0Table &table = g_Va00E02FE4ComponentTable;
		_STL::for_each(table.begin(), table.end(), Rva0045F0A0(true, name));
	}
	else
	{
		g_rva00E02FC0Bits &= ~1;
	}
}

void DisableComponents(const char *name)
{
	if (name != 0 && *name != 0)
	{
		Rva0045F0A0Table &table = g_Va00E02FE4ComponentTable;
		_STL::for_each(table.begin(), table.end(), Rva0045F0A0(false, name));
	}
	else
	{
		g_rva00E02FC0Bits |= 1;
		TheWindowManager->winSetFocus(0);
	}
}

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stringinline
// stlport
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv1292.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: bfmeLoadSJA 0x00411B07 (75B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Open-BFME5 conversions.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "StringInline.h"

class Rva00460A70Mapped
{
public:
	virtual void release( int deleting ) = 0;

	void *m_owner;
};

namespace rts
{
	template <class T> struct hash;
	template <class T> struct equal_to;

	template <> struct hash<AsciiString>
	{
		unsigned int operator()( AsciiString value ) const;
	};

	template <> struct equal_to<AsciiString>
	{
		int operator()( const AsciiString &left, const AsciiString &right ) const;
	};
}

typedef _STL::hash_map<AsciiString, Rva00460A70Mapped *, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > BfmeSJAHash;

extern char g_bfmeOneSJA[];
extern char g_bfmeTwoSJA[];
extern char g_bfmeDoneSJA;


// The second table's mapped value is the 44-byte record the matched erase at
// 0x004609B0 instantiates; its owner is the word at +4.
struct Rva004609B0Mapped
{
	char m_body[44];
};

typedef _STL::hash_map<AsciiString, Rva004609B0Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > BfmeSJAValueHash;

void bfmeLoadSJA(void *slot, void *p, char *out)
{
	BfmeSJAValueHash *table = (BfmeSJAValueHash *)slot;
	BfmeSJAValueHash::iterator eraseIt;
	BfmeSJAValueHash::iterator it = table->begin();
	while (it != table->end())
	{
		if (*(void **)(it->second.m_body + 4) == p)
		{
			eraseIt = it++;
			table->erase( eraseIt );
		}
		else
		{
			++it;
		}
	}
}

class Rva00410C42 { public: ~Rva00410C42(); };
class Rva0041090E { public: ~Rva0041090E(); };
void __cdecl dup_00410c7b();

class Rva004110B4Tree { public: ~Rva004110B4Tree(); };
Rva004110B4Tree::~Rva004110B4Tree() { ((Rva00410C42 *)this)->~Rva00410C42(); }

class Rva004110B9Tree { public: ~Rva004110B9Tree(); };
Rva004110B9Tree::~Rva004110B9Tree() { dup_00410c7b(); }

class Rva004110BETree { public: ~Rva004110BETree(); };
Rva004110BETree::~Rva004110BETree() { ((Rva0041090E *)this)->~Rva0041090E(); }


struct Rva00411112GlobalTable;
struct Rva004110DCGlobalTable;
struct Rva004114EFGlobalTable;
extern Rva00411112GlobalTable g_Va00E0300C;
extern Rva004110DCGlobalTable g_Va00E02FF8;
extern Rva004114EFGlobalTable g_Va00E02FE4;
extern unsigned int g_rva00E02FC0Bits;
void Rva00411336(void *slot, void *owner, char *out);

// Native Ghidra 0x00411E80..0x00411EC3; 67 bytes; cdecl one stack word.
// Caller 0x00222481 supplies a level index. BFME1 1399ad37 BfmeConv1292's
// bfmeGoSJA supplies the owner-removal sequence, but target calls the pointer
// walker for two tables and the value walker for a third, then clears bit 0.
// The three global declarations use their existing providers' exact spellings.
// The byte at &v is the empty callback object's storage; no call reads its value.
// Keep the established opaque caller name rather than promoting the donor label.
void Rva00411E80(int value)
{
    char v;
    void *owner = reinterpret_cast<void *>(value);
    Rva00411336(&g_Va00E0300C, owner, &v);
    Rva00411336(&g_Va00E02FF8, owner, &v);
    bfmeLoadSJA(&g_Va00E02FE4, owner, &v);
    g_rva00E02FC0Bits &= ~1;
}

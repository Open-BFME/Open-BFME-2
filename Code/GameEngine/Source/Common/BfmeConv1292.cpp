// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/stringinline
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
#include <map>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}

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

// The following native providers have the same thiscall argument/return ABI
// as these specializations: bucket-index 0x223149 (31B), node release 0x1FD9EF
// (28B), and iterator bucket advance 0x3F7925 (47B). Retail's key at node+4,
// bucket vector at table+4, and two-word iterator establish the layout.
// Declare them externally: the donor header's 22/32/50B definitions differ.
// The emitted 68B begin, 22B ++, 30B erase wrapper and 80B erase worker are
// independently exact twins including the native REL32 dependency graph.
typedef BfmeSJAHash::value_type PointerSJAValue;
typedef _STL::hashtable<PointerSJAValue, AsciiString, rts::hash<AsciiString>,
    _STL::_Select1st<PointerSJAValue>, _STL::equal_to<AsciiString>,
    _STL::allocator<PointerSJAValue> > PointerSJATable;
typedef _STL::_Hashtable_iterator<PointerSJAValue, AsciiString, rts::hash<AsciiString>,
    _STL::_Select1st<PointerSJAValue>, _STL::equal_to<AsciiString>,
    _STL::allocator<PointerSJAValue> > PointerSJAIteratorCore;
namespace _STL
{
    template <> unsigned int PointerSJATable::_M_bkt_num_key(const AsciiString &key) const;
    template <> void PointerSJATable::_M_delete_node(_Hashtable_node<PointerSJAValue> *node);
    template <> _Hashtable_node<PointerSJAValue> *PointerSJAIteratorCore::_M_skip_to_next();
}

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
class Rva0041090E { public: ~Rva0041090E(); void rva00410A14(); };
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

class Rva004FC957Delete
{
public:
    void rva004FC957(Rva00460A70Mapped *value) const;
};

// Native Ghidra 0x00411336..0x00411395; 95 bytes; cdecl three words.
// BFME1 1399ad37 game/GameEngine/Source/Common/BfmeConv1292.cpp bfmeReadSJA
// supplies the owner-filtered erase loop. Retail proves mapped pointer at
// node+8 and its owner at +4; the original mapped class identity stays opaque.
// The target delegates deletion to 0x4FC957, which ignores its receiver,
// invokes a non-deleting virtual destructor and frees the returned pointer.
void Rva00411336(void *slot, void *owner, char *out)
{
    BfmeSJAHash *table = static_cast<BfmeSJAHash *>(slot);
    BfmeSJAHash::iterator eraseIt;
    BfmeSJAHash::iterator it = table->begin();
    while (it != table->end())
    {
        if (it->second->m_owner == owner)
        {
            eraseIt = it++;
            BfmeSJAHash::value_type *entry = &*eraseIt;
            Rva00460A70Mapped *mapped = entry->second;
            reinterpret_cast<Rva004FC957Delete *>(out)->rva004FC957(mapped);
            table->erase(eraseIt);
        }
        else
            ++it;
    }
}

class GameWindow;
class GameWindowManager {
public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void destroyWindow(GameWindow*);
};
extern GameWindowManager *TheWindowManager;
extern unsigned g_Va00E03020;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva002246B1 {public:int rva002246B1(const AsciiString*);};
class Rva00224455 {public:int rva00224455(const AsciiString*);};
void _bfme_closeAptScreen(const AsciiString&);
// Structural RE label for the pointer released during Apt shutdown; original
// global/type names remain unknown. Native stores and initial data establish
// a single pointer at RVA00A02FC8, not a function pin or a fixed-address read.
class AptShutdownReceiverView {public:virtual void *slot00(int);};
AptShutdownReceiverView *AptShutdownReceiverInstance=0;

// Complete native00411B52..00411E80 and WB01092E70 establish this shutdown.
// The owned E03020 map header and clear provider's StringBase<char> key
// destruction establish a string-keyed map; node+14 and WindowManager
// slot35 establish window values. The folded empty constructor alone does
// not establish its key type.
// Twelve custom renders and two commands are removed in native literal order.
void Rva00411B52() {
 typedef _STL::map<AsciiString,GameWindow*> Windows;
 Windows *windows=(Windows*)&g_Va00E03020;
 for(Windows::iterator it=windows->begin();it!=windows->end();++it)
  TheWindowManager->destroyWindow(it->second);
 ((Rva0041090E*)windows)->rva00410A14();
 ::operator delete(AptShutdownReceiverInstance?AptShutdownReceiverInstance->slot00(0):0);
 AptShutdownReceiverInstance=0;
 if(g_bfmeAptWindowManager) {
  {AsciiString name("GameWindow");((Rva002246B1*)g_bfmeAptWindowManager)->rva002246B1(&name);}
  {AsciiString name("HorzSlider");((Rva002246B1*)g_bfmeAptWindowManager)->rva002246B1(&name);}
  {AsciiString name("ComboBox");((Rva002246B1*)g_bfmeAptWindowManager)->rva002246B1(&name);}
  {AsciiString name("ImageComboBox");((Rva002246B1*)g_bfmeAptWindowManager)->rva002246B1(&name);}
  {AsciiString name("CheckBox");((Rva002246B1*)g_bfmeAptWindowManager)->rva002246B1(&name);}
  {AsciiString name("TextEntry");((Rva002246B1*)g_bfmeAptWindowManager)->rva002246B1(&name);}
  {AsciiString name("ListBox");((Rva002246B1*)g_bfmeAptWindowManager)->rva002246B1(&name);}
  {AsciiString name("PushButton");((Rva002246B1*)g_bfmeAptWindowManager)->rva002246B1(&name);}
  {AsciiString name("BinkMovie");((Rva002246B1*)g_bfmeAptWindowManager)->rva002246B1(&name);}
  {AsciiString name("LivingWorldMap");((Rva002246B1*)g_bfmeAptWindowManager)->rva002246B1(&name);}
  {AsciiString name("View3D");((Rva002246B1*)g_bfmeAptWindowManager)->rva002246B1(&name);}
  {AsciiString name("ColorPicker");((Rva002246B1*)g_bfmeAptWindowManager)->rva002246B1(&name);}
  {AsciiString name("DisableComponents");((Rva00224455*)g_bfmeAptWindowManager)->rva00224455(&name);}
  {AsciiString name("EnableComponents");((Rva00224455*)g_bfmeAptWindowManager)->rva00224455(&name);}
 }
 {AsciiString name("BinkMovieInit");_bfme_closeAptScreen(name);}
}

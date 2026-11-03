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
// Unchanged walker bodies isolated from the independent Apt shutdown.
// Native hash providers and the duplicate teardown identity remain unresolved.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <map>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

#include <cstddef>

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
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}

#include "StringInline.h"
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Hashtable_node@U?$pair@$$CBVAsciiString@@URva004609B0Mapped@@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString; struct Rva004609B0Mapped;
namespace _STL { template <> void allocator<_Hashtable_node<pair<AsciiString const ,Rva004609B0Mapped> > >::deallocate(_Hashtable_node<pair<AsciiString const ,Rva004609B0Mapped> > *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

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

void bfmeLoadSJA(void *tableStorage, void *owner, char *unusedOutput)
{
	BfmeSJAValueHash *valueTable = (BfmeSJAValueHash *)tableStorage;
	BfmeSJAValueHash::iterator entryToErase;
	BfmeSJAValueHash::iterator entryIterator = valueTable->begin();
	while (entryIterator != valueTable->end())
	{
		if (*(void **)(entryIterator->second.m_body + 4) == owner)
		{
			entryToErase = entryIterator++;
			valueTable->erase( entryToErase );
		}
		else
		{
			++entryIterator;
		}
	}
}

class Rva00410C42 { public: ~Rva00410C42(); };
class Rva0041090E { public: ~Rva0041090E(); void rva00410A14(); };
class Rva00410C7B { public: ~Rva00410C7B(); };

class Rva004110B4Tree { public: ~Rva004110B4Tree(); };


class Rva004110B9Tree { public: ~Rva004110B9Tree(); };
Rva004110B9Tree::~Rva004110B9Tree()
{
    reinterpret_cast<Rva00410C7B *>(this)->~Rva00410C7B();
}

class Rva004110BETree { public: ~Rva004110BETree(); };



struct Rva00411112GlobalTable;
struct Rva004114EFGlobalTable;
extern Rva00411112GlobalTable g_Va00E0300C;
extern unsigned g_Va00E02FF8;	// VA 0x00E02FF8, defined by Rva004121B2HashMapInits.cpp
// VA 0x00E02FE4: the component-window table AptComponentWindowLookup.cpp owns.
extern unsigned int AptComponentWindowDataTableStorage[5];
extern unsigned int g_rva00E02FC0Bits;
void Rva00411336(void *slot, void *owner, char *out);

// Native Ghidra 0x00411E80..0x00411EC3; 67 bytes; cdecl one stack word.
// Caller 0x00222481 supplies a level index. BFME1 1399ad37 BfmeConv1292's
// bfmeGoSJA supplies the owner-removal sequence, but target calls the pointer
// walker for two tables and the value walker for a third, then clears bit 0.
// The three global declarations use their existing providers' exact spellings.
// The byte at &v is the empty callback object's storage; no call reads its value.
// Keep the established opaque caller name rather than promoting the donor label.
void Rva00411E80(int ownerAddress)
{
    char cleanupContext;
    void *owner = reinterpret_cast<void *>(ownerAddress);
    Rva00411336(&g_Va00E0300C, owner, &cleanupContext);
    Rva00411336(&g_Va00E02FF8, owner, &cleanupContext);
    bfmeLoadSJA(AptComponentWindowDataTableStorage, owner, &cleanupContext);
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
void Rva00411336(void *tableStorage, void *owner, char *deletionContext)
{
    BfmeSJAHash *ownerTable = static_cast<BfmeSJAHash *>(tableStorage);
    BfmeSJAHash::iterator entryToErase;
    BfmeSJAHash::iterator entryIterator = ownerTable->begin();
    while (entryIterator != ownerTable->end())
    {
        if (entryIterator->second->m_owner == owner)
        {
            entryToErase = entryIterator++;
            BfmeSJAHash::value_type *erasedEntry = &*entryToErase;
            Rva00460A70Mapped *mappedObject = erasedEntry->second;
            reinterpret_cast<Rva004FC957Delete *>(deletionContext)->rva004FC957(mappedObject);
            ownerTable->erase(entryToErase);
        }
        else
            ++entryIterator;
    }
}


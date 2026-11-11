// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /D_CRTIMP=
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameClient/GUI/AptScreenClose.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// ??$for_each@U?$_Ht_iterator@U?$pair@$$CB 0x00411395 (95B),
// _bfme_closeAptScreen 0x0041149A (85B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
//
// Retail 0x004629A0, 97 bytes: _bfme_closeAptScreen.  Named APT screen
// destructors reach it through ILT 0x00036485.  It walks the window table at
// 0x012F19A4 with for_each (0x00462540 through ILT 0x00042591), clearing the
// name of every record that carries this screen name, then erases the name
// from the screen-reference table at 0x012F1990 (hashtable::erase 0x00461040
// through ILT 0x0000F547).  Both tables use the types their matched siblings
// witness: WindowTable in Rva00462B40WindowTable.cpp (begin 0x0045FA00) and
// the Rva00461A00 hash in AsciiStringHashErase00461040.cpp.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <algorithm>
#include "ascii_string.h"

#include <cstddef>
// Node storage uses the game's direct C free wrapper at RVA 0x00030830.
// /D_CRTIMP= keeps the CRT header declaration from selecting its IAT entry.
#include <stdlib.h>
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

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

// Shared AsciiString hashing takes the key by reference.
unsigned int __stdcall Rva00055041AsciiHash(const AsciiString *name);

namespace rts {
template <class T> struct hash {
    unsigned int operator()(T value) const;
};
template <> struct hash<AsciiString> {
    __declspec(dllimport) __forceinline
    unsigned int operator()(const AsciiString &value) const
    { return Rva00055041AsciiHash(&value); }
};
template <class T> struct equal_to {
    bool operator()(const T &, const T &) const;
};
}

struct WindowRecord {
    unsigned char m_pad00[0x28];
    AsciiString m_name;
};

typedef _STL::hash_map<AsciiString, WindowRecord, rts::hash<AsciiString>,
    rts::equal_to<AsciiString> > WindowTable;

typedef _STL::hashtable<_STL::pair<const AsciiString, WindowRecord>,
    AsciiString, rts::hash<AsciiString>,
    _STL::_Select1st<_STL::pair<const AsciiString, WindowRecord> >,
    rts::equal_to<AsciiString>,
    _STL::allocator<_STL::pair<const AsciiString, WindowRecord> > > WindowHash;
typedef _STL::_Hashtable_iterator<_STL::pair<const AsciiString, WindowRecord>,
    AsciiString, rts::hash<AsciiString>,
    _STL::_Select1st<_STL::pair<const AsciiString, WindowRecord> >,
    rts::equal_to<AsciiString>,
    _STL::allocator<_STL::pair<const AsciiString, WindowRecord> > > WindowIteratorCore;

// for_each's increment is the shared 0x00411084: its skip 0x003F7925 reads the
// table pointer once, and the bucket index 0x00223149 hashes before it reads
// the bucket count.
namespace _STL {
template <> inline unsigned int WindowHash::_M_bkt_num_key(const AsciiString &key) const
{
    unsigned int hash = _M_hash(key);
    return hash % _M_buckets.size();
}
template <> _Hashtable_node<pair<const AsciiString, WindowRecord> > *WindowIteratorCore::_M_skip_to_next()
{
    const WindowHash *table = _M_ht;
    size_t bucket = table->_M_bkt_num(_M_cur->_M_val);
    size_t count = table->bucket_count();
    _Node *node = 0;
    while (node == 0 && ++bucket < count)
        node = (_Node *)table->_M_buckets[bucket];
    return node;
}
}

#include "../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

struct Rva00461A00Mapped {
    Rva00461A00Mapped() : m_counted(0) {}
    Rva00461A00Mapped(const Rva00461A00Mapped &other) : m_counted(other.m_counted)
    {
        if (m_counted)
            ++m_counted->references;
    }
    ~Rva00461A00Mapped()
    {
        if (m_counted)
            ReleaseTreeHintRef00217D4C(m_counted);
    }

    TargetRef00217D4C *m_counted;
};

typedef _STL::hash_map<AsciiString, Rva00461A00Mapped, rts::hash<AsciiString>,
    _STL::equal_to<AsciiString> > AptScreenRefTable;

typedef _STL::hashtable<_STL::pair<const AsciiString, Rva00461A00Mapped>,
    AsciiString, rts::hash<AsciiString>,
    _STL::_Select1st<_STL::pair<const AsciiString, Rva00461A00Mapped> >,
    _STL::equal_to<AsciiString>,
    _STL::allocator<_STL::pair<const AsciiString, Rva00461A00Mapped> > > AptScreenRefHash;

// Hashing precedes bucket-count access; node storage uses the native free path.
namespace _STL {
template <> inline unsigned int AptScreenRefHash::_M_bkt_num_key(const AsciiString &key) const
{
    unsigned int hash = _M_hash(key);
    return hash % _M_buckets.size();
}
template <> __declspec(dllimport) __forceinline
void allocator<_Hashtable_node<pair<const AsciiString, Rva00461A00Mapped> > >::deallocate(
    pointer node, size_type) const
{
    if (node)
        free(node);
}
}

// The for_each functor at 0x00462540: clears the name of each record whose
// name equals the closed screen's.
struct NameClearFunctor00462540 {
    NameClearFunctor00462540(const AsciiString &name) : m_name(name) {}
    void operator()(_STL::pair<const AsciiString, WindowRecord> &record)
    {
        if (record.second.m_name == m_name)
            record.second.m_name.clear();
    }
    AsciiString m_name;
};

struct BfmeAptScreenRefStorage;
extern unsigned int AptComponentWindowDataTableStorage[5];
extern BfmeAptScreenRefStorage g_aptScreenReferences;

WindowTable *const g_windowTable = (WindowTable *)AptComponentWindowDataTableStorage;
AptScreenRefTable *const g_theAptScreenRefMap = (AptScreenRefTable *)&g_aptScreenReferences;

void _bfme_closeAptScreen(const AsciiString &name)
{
    _STL::for_each(g_windowTable->begin(), g_windowTable->end(), NameClearFunctor00462540(name));
    g_theAptScreenRefMap->erase(name);
}

#include "../../../Include/Common/Rva00053DC5.h"

class Rva000559CB
{
public:
	void rva000559CB();
};

void Rva000559CB::rva000559CB()
{
	((Rva00053DC5 *)this)->~Rva00053DC5();
}


class Rva004111CC
{
public:
	~Rva004111CC();
};

class Rva00411453Tree
{
public:
	~Rva00411453Tree();
};

Rva00411453Tree::~Rva00411453Tree()
{
	((Rva004111CC *)this)->~Rva004111CC();
}

// Native411458..41149A: register a by-value counted screen callback by name.
// The now-verified screen subscript41112B and assignment2174A4 retain their
// existing owners. Native startup7AFF1A and teardown7B8247 establish the
// existing global's20-byte table storage, not a single unsigned word.
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class AptScreenInitGadgets;
template<class T>class AptRef {
public:
 ~AptRef(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
 TargetRef00217D4C *m_ptr;
};
#include "../../../Include/GameLogic/Rva000427195.h"
void _bfme_setAptScreenRef(const AsciiString &name,AptRef<AptScreenInitGadgets> incoming) {
 TreeHintRef00217D4C *slot=(TreeHintRef00217D4C *)
  ((Rva000427195 *)&g_aptScreenReferences)->rva0041112B(&name);
 *slot=*(const TreeHintRef00217D4C *)&incoming;
}

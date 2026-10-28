// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00598CBC@Rva00598CBC@@QAEXXZ @0x00598CBC 65B via vector-assign plus slot-gated push_back
// Evidence: chain from 0x00598007; caller 0x004EBFC2; vector at +0x4C like Rva00598B2A; m_30 at +0x30 like AIUnitBuilder; rowed vector assign 0x000BDB46 and push_back 0x0002DBE6 and Find 0x00506C82; global g_00E063D4
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include "ascii_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> COMDAT copies, so the calls bind the kept rowed copies.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> void vector<AsciiString, allocator<AsciiString> >::push_back(const AsciiString&);
template <> vector<AsciiString, allocator<AsciiString> > &vector<AsciiString, allocator<AsciiString> >::operator=(const vector<AsciiString, allocator<AsciiString> >&);
template <> void vector<AsciiString, allocator<AsciiString> >::_M_insert_overflow(AsciiString*, const AsciiString&, const __false_type&, size_t, bool);
}

struct MidVecHolder
{
	char _pad[0x8c];
	_STL::vector<AsciiString> m_vec;
};

struct Rva002A8AB1Record
{
public:
	char m_pad00[0x160];
	MidVecHolder *m_160; // +0x160
	char m_pad164[0x8];
	void *m_16c; // +0x16C
};

class AIUnitBuilder
{
public:
	Rva002A8AB1Record *getAI();
};

struct Rva00506C82Arg
{
	char _pad[0x50];
	int m_50;
};

class GameSlot
{
public:
	char _pad[0x50];
	int m_50;
};

GameSlot *__cdecl Rva00506C82Find(const Rva00506C82Arg *arg);

// Owned here (its only reader); retail .data zero-initializes it (VA 0x00E063D4, BSS tail).
AsciiString g_00E063D4;

class Rva00598CBC
{
public:
	void rva00598CBC();
private:
	char _pad0[0x30];
	void *m_30;
	char _pad1[0x4c - 0x34];
	_STL::vector<AsciiString> m_vec;
};

void Rva00598CBC::rva00598CBC()
{
	Rva002A8AB1Record *rec = ((AIUnitBuilder *)this)->getAI();
	_STL::vector<AsciiString> &src = rec->m_160->m_vec;
	m_vec = src;
	GameSlot *slot = Rva00506C82Find((const Rva00506C82Arg *)m_30);
	if (slot && slot->m_50 != 0) {
		m_vec.push_back(g_00E063D4);
	}
}

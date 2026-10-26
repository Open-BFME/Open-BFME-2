// ?rva002862C9@Rva002862C9@@QAEPAVLargeGroupAudioKeyMap@@XZ
// partial score=0.98 date=2026-10-14
// ?rva002862C9@Rva002862C9@@QAEPAVLargeGroupAudioKeyMap@@XZ
// partial score=0.98 date=2026-10-14
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/asciistring_downloadmanager /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// ?bfmeAddKey@LargeGroupAudioKeyMap@@QAEXABVAsciiString@@@Z retail 0x003EDA43, 168 bytes.
// Ported from the Open-BFME-1 donor game/GameEngine/Source/GameLogic/LargeGroupAudio/
// LargeGroupAudioKeyMapBfmeAddKey.cpp (reference/open-bfme-1 @ 6583b3c1), body and
// declarations verbatim. Compiled at /O1 it places uniquely on unclaimed .text.
// Callees are the pinned pair constructor 0x003ED3F0, the no-case tree insert_unique
// 0x003ED8B1 and vector<void*>::resize 0x000E6D39. The global key tree and counter are
// DIR32 and carried under the donor's names. The donor's method name is its own label;
// the original identity is not recovered.

// Open-BFME5: behavior-derived LargeGroupAudioKeyMap key registration,
// retail 0x003D46A0, 205 bytes. Two callers feed it AsciiString tokens; the
// method interns the token in the global no-case tree, retains its record and
// sets the record's numbered bit in this map.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
// Pull the real STLport tree/iterator implementation (its operator-> inlining
// is byte-significant), while leaving vector available for the retail by-value
// resize declaration below. STLport's stock vector declares the fill by const
// reference and would create a four-byte temporary that retail does not have.
#define _STLP_INTERNAL_VECTOR_H
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include <stl/_tree.h>
#include "LargeGroupAudioKeyTreeStorage.h"
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

namespace _STL
{

template <class Type, class Allocator>
class vector
{
public:
	Type *begin() { return m_wordsBegin; }
	unsigned int size() const { return m_wordsEnd - m_wordsBegin; }
	void resize(unsigned int count, Type value);

protected:
	Type *m_wordsBegin;
	Type *m_wordsEnd;
	Type *m_wordsCapacity;
};

// These accesses inline into the matched callers. Keep their rowed STLport
// providers instead of emitting competing copies from this private view.
template <> __declspec(dllimport) __forceinline
void **vector<void *, allocator<void *> >::begin() { return m_wordsBegin; }
template <> __declspec(dllimport) __forceinline
unsigned int vector<void *, allocator<void *> >::size() const
{
	return m_wordsEnd - m_wordsBegin;
}

}

struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &left, const AsciiString &right) const;
};

struct Rva003D3F90Value
{
	unsigned int m_key;
	unsigned int m_useCount;
};

typedef _STL::pair<const AsciiString, Rva003D3F90Value> Rva003D3F90Pair;
typedef _STL::_Rb_tree<AsciiString, Rva003D3F90Pair,
	_STL::_Select1st<Rva003D3F90Pair>, BfmeStringNoCaseLess,
	_STL::allocator<Rva003D3F90Pair> > Rva003D3F90Tree;

typedef char KeyRecordTreeStorageSize[
	sizeof(Rva003D3F90Tree) == sizeof(g_lgaKeyRecords) ? 1 : -1];
// Next key handed out by bfmeAddKey (retail RVA 0x00A02E4C, zero at load, just
// below g_lgaKeyRecords); bfmeClearMembers (LargeGroupAudioKeyList.cpp) resets it.
unsigned int g_lgaNextKey = 0;

class Drawable;

class LargeGroupAudioKeyMap :
	public _STL::vector<void *, _STL::allocator<void *> >
{
public:
	void bfmeAddKey(const AsciiString &name);
};

// ?bfmeAddKey@LargeGroupAudioKeyMap@@QAEXABVAsciiString@@@Z
void LargeGroupAudioKeyMap::bfmeAddKey(const AsciiString &name)
{
	Rva003D3F90Value empty = { 0, 0 };
	Rva003D3F90Pair value(name, empty);
	_STL::pair<Rva003D3F90Tree::iterator, bool> inserted =
		reinterpret_cast<Rva003D3F90Tree *>(g_lgaKeyRecords)->insert_unique(value);

	++inserted.first->second.m_useCount;
	if (inserted.second)
		inserted.first->second.m_key = g_lgaNextKey++;

	unsigned int key = inserted.first->second.m_key;
	unsigned int word = key >> 5;
	unsigned int mask = 1 << (key & 0x1F);
	if (word >= size())
		// Native 0x000E6D39 owns this by-value four-byte-element resize.
		// The call view does not identify the bitmap words as Drawable pointers.
		reinterpret_cast<_STL::vector<Drawable *, _STL::allocator<Drawable *> > *>(this)->resize(word + 1, 0);
	((unsigned int *)begin())[word] |= mask;
}

// ?rva002862C9@Rva002862C9@@QAEPAVLargeGroupAudioKeyMap@@XZ
// Retail 0x002862C9 (136B), WB 0x00C36490. Function-local static 12-byte
// LargeGroupAudioKeyMap (vector holder at 0x00DFEC74, guard bit 0x00DFEC80)
// built through the 0x001F81BF vector-base fold; its destructor is the
// compiler-local atexit callback 0x007B7810 (tail-jmp to the rowed 0x003ED94F
// dtor). A separate byte flag at 0x00DFEC70 guards one bfmeAddKey(
// "BurningCell"). Retail ends with eax = &static, so the address pin is
// renamed void -> LargeGroupAudioKeyMap*. The class name is the existing
// 0x003ED94F dtor owner; its nonthrowing default ctor is the 0x001F81BF fold
// proved by the gap-filler pattern, using the rowed _Vector_base ctor pin.
namespace _STL
{
template <class T, class Alloc>
class _Vector_base
{
public:
	_Vector_base(const Alloc &alloc);
};
}

class Rva003ED94FDtor : private _STL::_Vector_base<int, _STL::allocator<int> >
{
public:
	__declspec(noinline) Rva003ED94FDtor();
	~Rva003ED94FDtor();
};

Rva003ED94FDtor::Rva003ED94FDtor()
	: _STL::_Vector_base<int, _STL::allocator<int> >(_STL::allocator<int>())
{
}

extern unsigned int g_Va00DFEC74;

class Rva002862C9
{
public:
	LargeGroupAudioKeyMap *rva002862C9();
};

LargeGroupAudioKeyMap *Rva002862C9::rva002862C9()
{
	static Rva003ED94FDtor map;
	static bool keysAdded;
	if (!keysAdded)
	{
		{
			AsciiString name("BurningCell");
			LargeGroupAudioKeyMap *keyMap = (LargeGroupAudioKeyMap *)&map;
			keyMap->bfmeAddKey(name);
		}
		keysAdded = true;
	}
	return (LargeGroupAudioKeyMap *)&g_Va00DFEC74;
}

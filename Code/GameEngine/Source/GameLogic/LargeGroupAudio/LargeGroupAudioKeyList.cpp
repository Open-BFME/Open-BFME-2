// cl: /O1 /Oy- /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/asciistring_downloadmanager /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// ?bfmeClearMembers@@YAXPAVLGA_MemberObj@@@Z retail 0x003ED7A2, 191 bytes.
// Ported from the Open-BFME-1 donor game/GameEngine/Source/GameLogic/LargeGroupAudio/
// LargeGroupAudioKeyList.cpp (reference/open-bfme-1 @ d6db6bfa), declarations
// verbatim. Two repairs, both from retail bytes: an ebp frame (/Oy-, added to
// the matched sibling LargeGroupAudioKeyMapBfmeAddKey.cpp's /O1 line), and the
// word index held in a local (retail keeps begin in edx, the index in eax).
// Target evidence: the three matched callers (LargeGroupAudioKeyMap::operator=
// 0x003ED989, 0x003ED861, the 0x003ED94F dtor) pass the key-bit vector by
// pointer, and the body walks the global key tree 0x00A02E50 and next-key
// counter 0x00A02E4C, both already carried in the data ledger under the
// donor's names. The donor's function name is its own label; the original
// identity is not recovered.

// Open-BFME5: LGA_MemberObj's member release helper, retail 0x003D4080,
// 264 bytes. The destructor at 0x003D4490 calls its ILT at 0x00034DC9 before
// releasing the bitmap vector at offset zero.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "Common/AsciiString.h"
#include <stl/_tree.h>
#include "LargeGroupAudioKeyTreeStorage.h"
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@URva003D3F90Value@@@_ST:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString; struct Rva003D3F90Value;
namespace _STL { template <> void allocator<_Rb_tree_node<pair<AsciiString const ,Rva003D3F90Value> > >::deallocate(_Rb_tree_node<pair<AsciiString const ,Rva003D3F90Value> > *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
// TRANSITIVE anchor (no <map>/<set> include in this TU).
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

namespace _STL
{

template <class Type, class Allocator>
class vector
{
protected:
	Type *m_wordsBegin;
	Type *m_wordsEnd;
	Type *m_wordsCapacity;
};

}

struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &left, const AsciiString &right) const;
};

struct Rva003D3F90Value
{
	unsigned int m_key;
	int m_useCount;
};

typedef _STL::pair<const AsciiString, Rva003D3F90Value> Rva003D3F90Pair;
typedef _STL::_Rb_tree<AsciiString, Rva003D3F90Pair,
	_STL::_Select1st<Rva003D3F90Pair>, BfmeStringNoCaseLess,
	_STL::allocator<Rva003D3F90Pair> > Rva003D3F90Tree;

// Retail's call at 0x003ED80E uses the rowed 59-byte erase at 0x00056BC3.
// Its receiver/node prefix and AsciiString destruction agree with this tree;
// this call-only view does not identify the complete record as an AsciiString.
typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>,
	_STL::less<AsciiString>, _STL::allocator<AsciiString> > AsciiStringEraseTree;
namespace _STL {
template <> void _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>,
	less<AsciiString>, allocator<AsciiString> >::erase(iterator);
}

unsigned int g_lgaKeyRecords[3] = { 0, 0, 0 };
typedef char KeyRecordTreeStorageSize[
	sizeof(Rva003D3F90Tree) == sizeof(g_lgaKeyRecords) ? 1 : -1];
extern unsigned int g_lgaNextKey;

class LGA_MemberObj
{
public:
	unsigned int *m_wordsBegin;
	unsigned int *m_wordsEnd;
	unsigned int *m_wordsCapacity;
};

// ?bfmeClearMembers@@YAXPAVLGA_MemberObj@@@Z
void bfmeClearMembers(LGA_MemberObj *self)
{
	Rva003D3F90Tree *records = reinterpret_cast<Rva003D3F90Tree *>(g_lgaKeyRecords);
	Rva003D3F90Tree::iterator record = records->begin();
	bool rebuildNextKey = false;

	while (record != records->end())
	{
		unsigned int key = record->second.m_key;

		unsigned int word = key >> 5;
		if (self->m_wordsEnd - self->m_wordsBegin > word)
		{
			unsigned int mask = 1 << (key & 0x1F);
			if (self->m_wordsBegin[word] & mask)
			{
				--record->second.m_useCount;
				if (record->second.m_useCount > 0)
				{
					++record;
					continue;
				}
				else
				{
					if (key == g_lgaNextKey)
						rebuildNextKey = true;

					Rva003D3F90Tree::iterator next = record;
					++record;
					reinterpret_cast<AsciiStringEraseTree *>(g_lgaKeyRecords)->erase(
						AsciiStringEraseTree::iterator(
							reinterpret_cast<_STL::_Rb_tree_node<AsciiString> *>(next._M_node)));
					continue;
				}
			}
		}

		++record;
	}

	if (rebuildNextKey)
	{
		g_lgaNextKey = 0;
		record = records->begin();
		while (record != records->end())
		{
			if ((int)record->second.m_key >= (int)g_lgaNextKey)
				g_lgaNextKey = record->second.m_key + 1;
			++record;
		}
	}
}

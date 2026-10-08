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

extern Rva003D3F90Tree g_lgaKeyRecords;
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
	Rva003D3F90Tree::iterator record = g_lgaKeyRecords.begin();
	bool rebuildNextKey = false;

	while (record != g_lgaKeyRecords.end())
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
					g_lgaKeyRecords.erase(next);
					continue;
				}
			}
		}

		++record;
	}

	if (rebuildNextKey)
	{
		g_lgaNextKey = 0;
		record = g_lgaKeyRecords.begin();
		while (record != g_lgaKeyRecords.end())
		{
			if ((int)record->second.m_key >= (int)g_lgaNextKey)
				g_lgaNextKey = record->second.m_key + 1;
			++record;
		}
	}
}

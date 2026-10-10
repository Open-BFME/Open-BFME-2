// ??MS4SortElem8@@QBE_NABU0@@Z
// partial score=0.8 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Two STLport 4.5.3 sort(first, last) instantiations over 8-byte records
// ordered by a member operator< (0x005EC52E), built from the score-row family
// of the Open-BFME-1 donors (game/GameEngine/Source/GameClient/GUI/
// ScoreRowIntrosort.cpp and game/Libraries/Source/WWVegas/WWLib/
// stlport_{adjust,push}_heap_s4sortelem8_score.cpp at 1281192f68; donor
// /DNDEBUG /MD /EHsc plus BFME 2's /O1 /G7). The donor sweep placed
// __adjust_heap (0x0051D178) and __push_heap (0x005EC5F5) uniquely; the rest
// of the family follows from their callers and callees.
//
// Target evidence for the shape:
//   * both sorts (0x0051D9E1, called from 0x0051DB60, and 0x005ECD49, called
//     from 0x005ECDA8) take two arguments and pass an uninitialised stack word
//     as the comparator: sort(first, last) with the empty less<T>;
//   * every comparison is a call to 0x005EC52E, the element's operator<;
//   * the heap, insertion and partition leaves exist once and serve both
//     sorts, while sort, __introsort_loop, partial_sort, __partial_sort,
//     sort_heap, pop_heap and __final_insertion_sort exist twice with
//     identical code: the linker folded the identical leaves of two
//     instantiations but not the parents that named them.
// The records are stand-ins (S4SortElem8, S4SortElem8B): the image fixes
// only their size, bitwise copy and shared operator<.
#include <algorithm>

struct S4SortElem8
{
	int m_bfmeFirst;
	int m_bfmeSecond;

	bool operator<(const S4SortElem8 &other) const;
};

struct S4SortElem8B
{
	int m_bfmeFirst;
	int m_bfmeSecond;

	bool operator<(const S4SortElem8B &other) const;
};

template void _STL::sort<S4SortElem8 *>(S4SortElem8 *, S4SortElem8 *);
template void _STL::sort<S4SortElem8B *>(S4SortElem8B *, S4SortElem8B *);

#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>

// Record views for the two element comparators below. Each 8-byte element
// pairs a row object (name at +0x04, score at +0x9C — the same offsets the
// Rva0037DCA5 army view below establishes) with a flags object carrying the
// reconquered bit at +0x110. The element structs above stay int-typed
// stand-ins so the placed sort helpers keep their bytes; the casts here
// compile to nothing.
struct ScoreRowData
{
	char m_pad00[4];
	AsciiString m_name04;
	char m_pad08[0x9C - 8];
	int m_score9C;
};

struct ScoreRowFlags
{
	char m_pad00[0x110];
	unsigned int m_flags110;
};

// Both element comparators share the folded retail body at 0x005EC52E:
// flag bit 26 first (this side tested, other side shifted), then the +0x9C
// score with signed greater, then the +0x04 name via the rowed free
// AsciiString operator< at 0x0005598C. inline_depth(0) keeps that name
// call out of line instead of expanding the header inline.
#pragma inline_depth(0)
bool S4SortElem8::operator<(const S4SortElem8 &other) const
{
	const ScoreRowFlags *af = reinterpret_cast<const ScoreRowFlags *>(m_bfmeSecond);
	const ScoreRowFlags *bf = reinterpret_cast<const ScoreRowFlags *>(other.m_bfmeSecond);
	const ScoreRowData *thisRow = reinterpret_cast<const ScoreRowData *>(m_bfmeFirst);
	const ScoreRowData *otherRow = reinterpret_cast<const ScoreRowData *>(other.m_bfmeFirst);
	if (((af->m_flags110 & 0x4000000) != 0) != ((bf->m_flags110 >> 26) & 1))
		return ((af->m_flags110 & 0x4000000) != 0);
	if (thisRow->m_score9C != otherRow->m_score9C)
		return thisRow->m_score9C > otherRow->m_score9C;
	return thisRow->m_name04 < otherRow->m_name04;
}

bool S4SortElem8B::operator<(const S4SortElem8B &other) const
{
	const ScoreRowFlags *af = reinterpret_cast<const ScoreRowFlags *>(m_bfmeSecond);
	const ScoreRowFlags *bf = reinterpret_cast<const ScoreRowFlags *>(other.m_bfmeSecond);
	const ScoreRowData *thisRow = reinterpret_cast<const ScoreRowData *>(m_bfmeFirst);
	const ScoreRowData *otherRow = reinterpret_cast<const ScoreRowData *>(other.m_bfmeFirst);
	if (((af->m_flags110 & 0x4000000) != 0) != ((bf->m_flags110 >> 26) & 1))
		return ((af->m_flags110 & 0x4000000) != 0);
	if (thisRow->m_score9C != otherRow->m_score9C)
		return thisRow->m_score9C > otherRow->m_score9C;
	return thisRow->m_name04 < otherRow->m_name04;
}
#pragma inline_depth()
class Image;
struct StrategicButtonImageView;
namespace StrategicInGameUI { const Image *GetButtonImage(const StrategicButtonImageView *, int); }
class Rva0037DCA5 {
public:
 unsigned char pad00[4];AsciiString name04;
 unsigned char pad08[4];int value0C;
 unsigned char pad10[0x94-0x10];int value94,value98,value9C;
 UnicodeString titleA0;
 void *rva0040C65D(int);
};
// Existing 24B push_back footprint, now viewed through target5ECD8C stores.
struct BfmeStringRecord005EC43C {
 UnicodeString title;int value04,value08,value0C,value10;const Image *image14;
 BfmeStringRecord005EC43C():value04(-1),value08(-1),value0C(-1),value10(-1),image14(0){}
 BfmeStringRecord005EC43C(const BfmeStringRecord005EC43C&);
};
namespace _STL {
template<> void vector<BfmeStringRecord005EC43C>::push_back(const BfmeStringRecord005EC43C&);
}
class Rva005ECD8C {
public:
 void *vptr0;
 _STL::vector<BfmeStringRecord005EC43C> rows4;
 void rva005ECD8C(_STL::vector<S4SortElem8B> *input,int player);
};
// Native245B: sort opaque8B army entries, collect title/icon/four counters.
void Rva005ECD8C::rva005ECD8C(_STL::vector<S4SortElem8B> *input,int player) {
 _STL::sort(input->begin(),input->end());
 AsciiString nativeTemporary;
 for(_STL::vector<S4SortElem8B>::iterator it=input->begin();it!=input->end();++it) {
  Rva0037DCA5 *army=reinterpret_cast<Rva0037DCA5 *>(it->m_bfmeFirst);
  BfmeStringRecord005EC43C row;
  if(!army->titleA0.isEmpty())row.title=army->titleA0;
  else row.title=*reinterpret_cast<UnicodeString *>(army->rva0040C65D(player));
  row.image14=StrategicInGameUI::GetButtonImage(reinterpret_cast<const StrategicButtonImageView *>(army),player);
  row.value04=army->value0C;row.value08=army->value94;row.value0C=army->value98;row.value10=army->value9C;
  rows4.push_back(row);
 }
}

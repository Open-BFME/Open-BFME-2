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

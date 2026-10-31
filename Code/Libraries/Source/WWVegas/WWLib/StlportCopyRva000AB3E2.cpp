// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /I. /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/shims/bfmealloc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// stlport46
//
// ??$__uninitialized_copy@PAURva000AB3E2Element@@PAU1@@_STL@@YAPAURva000AB3E2Element@@PAU1@00ABU__false_type@0@@Z @0x000A9E1C (38B).
// _STL::__uninitialized_copy<Rva000AB3E2Element> retail 38 bytes: STLport's loop
// over the out-of-line nothrow Rva000AB3E2Element _Construct. Evidence: loop calls pinned
// _Construct 0x000A9DF8 stride 0x18 callers 0x000AAF4A/0x000AAF95 same shape as rowed
// 38B copies 0x000ADE67 and 0x004C3121; neighbours 0x000A9DF3/0x000A9E42.
#include <vector>

struct Rva000AB3E2Element
{
public:
	Rva000AB3E2Element(const Rva000AB3E2Element &other) throw();
	int a[6]; // +0x00
};

namespace _STL
{

template <>
void _Construct<Rva000AB3E2Element, Rva000AB3E2Element>(Rva000AB3E2Element *__p, const Rva000AB3E2Element &__value) throw();

}

template Rva000AB3E2Element *_STL::__uninitialized_copy(Rva000AB3E2Element *,
	Rva000AB3E2Element *, Rva000AB3E2Element *, const _STL::__false_type &);

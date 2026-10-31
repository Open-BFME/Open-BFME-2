// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /I. /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/shims/bfmealloc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// stlport46
//
// ??$__uninitialized_fill_n@PAURva000AB419Element@@IU1@@_STL@@YAPAURva000AB419Element@@PAU1@IABU1@ABU__false_type@0@@Z @0x000A9E8D (37B).
// _STL::__uninitialized_fill_n<Rva000AB419Element> retail 37 bytes: STLport's loop
// over the out-of-line nothrow Rva000AB419Element _Construct. Evidence: loop calls pinned
// _Construct 0x000A9E0A stride 0x10 caller 0x000AAFC6 same shape as rowed
// fill_n 0x00565770 and sibling 0x000A9E42; neighbours 0x000A9E42/0x000A9EB2.
#include <vector>

struct Rva000AB419Element
{
public:
	Rva000AB419Element(const Rva000AB419Element &other) throw();
	int a[4]; // +0x00
};

namespace _STL
{

template <>
void _Construct<Rva000AB419Element, Rva000AB419Element>(Rva000AB419Element *__p, const Rva000AB419Element &__value) throw();

}

template Rva000AB419Element *_STL::__uninitialized_fill_n(Rva000AB419Element *, unsigned int, const Rva000AB419Element &, const _STL::__false_type &);

// ?_M_fill_insert@?$vector@URva0007BB16Record@@V?$allocator@URva0007BB16Record@@@_STL@@@_STL@@QAEXPAURva0007BB16Record@@IABU3@@Z
// partial score=0.3666666667 date=2026-10-04
// cl: /G7 /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Destroy@PAURva0007BB16Record@@@_STL@@YAXPAURva0007BB16Record@@0@Z @0x0007C2D7 25B:
// ?_M_clear@?$vector@URva0007BB16Record@@V?$allocator@URva0007BB16Record@@@_STL@@@_STL@@IAEXXZ @0x0007C614 30B:
// STLport 4.5.3 range destroy over the 0x24-byte two-string record whose dtor
// is rowed at 0x0007BB16 (strings at +0x00/+0x08, tail past +0x0C unrecovered,
// same definition as Code/GameEngine/Source/Common/StringRecordDtors.cpp).
// Retail steps esi by 0x24 and calls the rowed dtor; callers at 0x0007C5D5,
// 0x0007C614, 0x0015229C and 0x001522CF prove the 0x24 stride and the two
// vector lifetimes. Landing this unblocks those four callers.
#include <vector>

#include "ascii_string.h"

struct Rva0007BB16Record
{
	~Rva0007BB16Record();
	AsciiString m_00;
	int m_04;
	AsciiString m_08;
	int m_tail0C[6];
};

namespace _STL
{

template <>
inline void _Destroy<Rva0007BB16Record *>(Rva0007BB16Record *__first, Rva0007BB16Record *__last)
{
	for (; __first != __last; ++__first)
		_Destroy(&*__first);
}

}

template void _STL::vector<Rva0007BB16Record>::_M_clear();

// Whole-class instantiation: its members that are rowed were placed at retail
// by masked search of this TU's emitted bodies plus REL32 callee agreement.
template class _STL::vector<Rva0007BB16Record,_STL::allocator<Rva0007BB16Record> >;

// ??$_Destroy over Rva0007BB16Record* is a header inline in STLport: other
// units emit select-any copies of it, so a strong definition here was a
// duplicate symbol in the linked build. This anchor only makes this unit emit
// its copy for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitstlport_vector_rva0007bb16_destroy@@YAXPAURva0007BB16Record@@@Z present-unmatched
void bfmeEmitstlport_vector_rva0007bb16_destroy(Rva0007BB16Record *p)
{
	_STL::_Destroy(p, p + 1);
}
#pragma inline_depth()

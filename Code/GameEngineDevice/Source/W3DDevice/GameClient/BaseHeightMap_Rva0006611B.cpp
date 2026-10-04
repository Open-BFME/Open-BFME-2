// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/bfmeheightmap -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient
// stlport
//
// ?_M_subtract@_Bit_iterator_base@_STL@@QBEHABU12@@Z
// retail 0x0006611B, 23 bytes.
//
// This is NOT a body the donor TU can be copied from. The BFME 1 donor sweep
// credits the symbol to a HEADER the translation unit includes
// (game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp at
// reference/open-bfme-1 @ 6d943426), not to the TU, so land.py refuses to
// prepare one.
//
//   0006611B  8b 54 24 04        mov edx, [esp+4]      ; __x
//   0006611F  8b 01              mov eax, [ecx]        ; this->_M_p
//   00066121  2b 02              sub eax, [edx]        ; - __x._M_p
//   00066123  c1 f8 02           sar eax, 2            ; / sizeof(unsigned)
//   00066126  c1 e0 05           shl eax, 5            ; * 32 == __WORD_BIT
//   00066129  2b 42 04           sub eax, [edx+4]      ; - __x._M_offset
//   0006612C  03 41 04           add eax, [ecx+4]      ; + _M_offset
//   0006612F  c2 04 00           ret 4
//
// with 0x0006611A (`00`) immediately before it, so the boundary is proven.
//
// WHAT IT IS. stl/_bvector.h:112 is
//   `difference_type _M_subtract(const _Bit_iterator_base& __x) const {
//      return __WORD_BIT * (_M_p - __x._M_p) + _M_offset - __x._M_offset; }`
// so the body is that word-count-to-bit-count conversion: the pointer difference
// is divided by sizeof(unsigned) (the sar 2), scaled by the 32-bit word width
// (the shl 5), and corrected by the two bit offsets. The `shl eax, 5` rather than
// an immediate multiply is MSVC 7.1 strength-reducing __WORD_BIT, a 32-bit dword
// on this target.

#include <vector>

// The one use that odr-uses the member: _Bit_iter::operator- (the const _Self&
// overload) forwards straight to _M_subtract (stl/_bvector.h:195), and a used
// member function is emitted even though the header declares it without
// `inline`. It is the iterator-distance form, not the operator-(difference_type)
// form at line 191, which is a different body and would not reach it. Going
// through the public _Bit_iter is also the only legal route, _Bit_iterator_base
// being the base of a base with the member protected from outside.
//
// The element is `bool`, i.e. std::_Bit_type, so vector<bool>'s iterator is
// _Bit_iter<_Bit_reference, bool*> exactly as the retail name spells it.
typedef _STL::_Bit_iter<_STL::_Bit_reference, bool *> W3DBitIterator;

int bfmeHeightMapBitVectorDiffUsesSubtract(const W3DBitIterator &first,
	const W3DBitIterator &last)
{
	return last - first;
}
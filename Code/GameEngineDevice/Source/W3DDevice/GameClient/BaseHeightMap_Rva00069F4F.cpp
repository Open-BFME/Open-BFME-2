// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/bfmeheightmap -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient
// stlport
//
// ?begin@?$vector@_NV?$allocator@_N@_STL@@@_STL@@QAE?AU?$_Bit_iter@U_Bit_reference@_STL@@PAU12@@2@XZ
// retail 0x00069F4F, 17 bytes.
//
// This is NOT a body the donor TU can be copied from. The BFME 1 donor sweep
// credits the symbol to a HEADER the translation unit includes
// (game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp at
// reference/open-bfme-1 @ 6d943426), not to the TU, so land.py refuses to
// prepare one. Retail does carry begin() out of line, and the landed sibling
// WWLib/stlport_deque_e16_o1.cpp is the proven way to make this compiler emit a
// container's out-of-line members: an explicit instantiation of the container.
//
//   00069F4F  8b 11              mov edx, [ecx]        ; this->_M_start._M_p
//   00069F51  8b 44 24 04        mov eax, [esp+4]      ; the hidden return slot
//   00069F55  89 10              mov [eax], edx        ; ._M_p
//   00069F57  8b 49 04           mov ecx, [ecx+4]      ; this->_M_start._M_offset
//   00069F5A  89 48 04           mov [eax+4], ecx      ; ._M_offset
//   00069F5D  c2 04 00           ret 4
//
// with 0x00069F4E (`00`) immediately before it, so the boundary is proven.
//
// WHAT IT IS. stl/_vector.h:172 is `iterator begin() { return this->_M_start; }`,
// so the body is a by-value copy of the start iterator -- for vector<bool> that
// is _Bit_iter<_Bit_reference, bool*>, and a _Bit_iter is just the
// _Bit_iterator_base pair of _M_p and _M_offset -- so the body is those two dwords.
// The two separate stores rather than a block move are because _Bit_iter's copy
// constructor (stl/_bvector.h:153) casts through _Bit_iterator_base instead of
// being a compiler-generated POD copy, which is what defeats the 8-byte block
// recognition.
//
// The `QAE?AU...2@XZ` mangling is the by-value hidden-return convention: [esp+4]
// is the caller's return slot and `ret 4` pops no argument, begin() taking none.
//
// The element is `bool`, i.e. std::_Bit_type, and the allocator the
// `_N?$allocator@_N@_STL@@@` the name carries, so this instantiation is
// vector<bool> exactly rather than an approximation of it.

#include <vector>

typedef _STL::vector<bool, _STL::allocator<bool> > W3DBoolVector;

// The one use that odr-uses begin(): taking a vector<bool>'s first bit is
// exactly begin(), and a used member function is emitted even though the header
// declares it without `inline`.
bool bfmeHeightMapBoolVectorBeginProbe(W3DBoolVector *flags)
{
	return *flags->begin();
}

template class _STL::vector<bool, _STL::allocator<bool> >;
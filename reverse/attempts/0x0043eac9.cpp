// ??$equal@U?$_Bit_iter@_NPB_N@_STL@@U12@@_STL@@YA_NU?$_Bit_iter@_NPB_N@0@00@Z
// partial score=1.0 date=2026-10-04
// stlport
// cl: /O1 /EHs-c-
// STLport 4.5.3; pristine definitions are in vendor/stlport.
// Donor lead: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/BitIteratorEqual.cpp, recompiled /O1.
// Target Ghidra entry43EAC9/84B compares three packed-bit iterator values.
// Caller43F14D/87B checks vector lengths and passes begin/end/other begin;
// workers660C9 and66132 independently establish iterator bump and comparison.
// Const-iterator specialization supplies the observed third-bit-first order;
// the template spelling is a donor/header inference, not a target export.

#include <vector>
#include <algorithm>

template bool _STL::equal<_STL::_Bit_const_iterator, _STL::_Bit_const_iterator>(
    _STL::_Bit_const_iterator,
    _STL::_Bit_const_iterator,
    _STL::_Bit_const_iterator);

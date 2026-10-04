// stlport
// cl: /O1 /EHs-c-
// STLport 4.5.3 equal<_Bit_const_iterator, _Bit_const_iterator> (retail
// 0x0043EAC9, 84 bytes); pristine definitions are in vendor/stlport.
// Target facts: Ghidra entry 0x0043EAC9/84 compares three packed-bit iterator
// values; its caller 0x0043F14D checks the two vector lengths and passes
// begin/end/other begin. Callees _M_bump_up (0x000660C9) and the bit-iterator
// operator!= (0x00066132) are existing rows.
// Donor lead: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/BitIteratorEqual.cpp, recompiled /O1. The
// const-iterator specialization supplies retail's third-bit-first compare
// order; the template spelling is a donor/header inference, not a target
// export.

#include <vector>
#include <algorithm>

template bool _STL::equal<_STL::_Bit_const_iterator, _STL::_Bit_const_iterator>(
    _STL::_Bit_const_iterator,
    _STL::_Bit_const_iterator,
    _STL::_Bit_const_iterator);

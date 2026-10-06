// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ?_M_do_or@?$_Base_bitset@$0CA@@_STL@@QAEXABU12@@Z @0x0028C557 25B
// STLport _Base_bitset<32>::_M_do_or: loops 0x20 words ORing [ecx] with [eax+ecx],
// same shape as rowed $03 sibling at 0x0028C53E (4 words). 23 callers, landing unblocks 15.
// Explicit instantiation of the one member only.
#include <bitset>

template void _STL::_Base_bitset<32>::_M_do_or(const _STL::_Base_bitset<32>&);

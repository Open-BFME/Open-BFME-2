// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ?_M_is_any@?$_Base_bitset@$0CA@@_STL@@QBE_NXZ @0x000454A6 20B
// STLport _Base_bitset<32>::_M_is_any: loops 0x20 words at [ecx+eax*4],
// returns 1 on first non-zero else 0. Same shape as the rowed $03 sibling at
// 0x000454BA (4 words); 32 words = 128B = BfmeFixedStorage128 size. Six
// callers (0x3283D1 0x4E7875 0x507587 0x59B720 0x5F45C7 0x5F4929). Explicit
// instantiation of the one member only.
#include <bitset>

template bool _STL::_Base_bitset<32>::_M_is_any() const;

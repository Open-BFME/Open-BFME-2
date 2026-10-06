// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 bit-vector empty (retail 0x0060BDD5, 46 bytes) and
// _Bit_iterator_base operator== (retail 0x0060B869, 29 bytes).
// _bvector.h: empty is "return begin() == end()" (line 442), inlined as two
// 8-byte copies (_M_start at +0, _M_finish at +8) plus a call; operator==
// compares _M_p then _M_offset (lines 117-119). Same 29B shape as the rowed
// operator!= at 0x00066132. Caller of empty is the vector Xfer at 0x0060C310
// ("Vector must be empty on load"); sole caller of operator== is empty.
#include <vector>
template bool _STL::vector<bool, _STL::allocator<bool> >::empty() const;

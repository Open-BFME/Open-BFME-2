// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
// STLport 4.5.3: retain the narrow traits conversion from char_traits.h.
// Target 0x00017B70 is the complete CC-delimited 8-byte body between the
// narrow basic_ios helpers. The unsigned conversion distinguishes it from
// __char_traits_base<char, int>; the wide counterpart owns 0x00017FC0.
#include <string>

int (__cdecl *BfmeNarrowTraitsToIntType)(const char &) =
    &_STL::char_traits<char>::to_int_type;

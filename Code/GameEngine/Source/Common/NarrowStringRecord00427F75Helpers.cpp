// cl: /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport46
//
// _STL::__uninitialized_copy PBUBfmeNarrowRecord00427F75 PAU, retail 0x00428123 38B,
// and _STL::__uninitialized_fill_n PAUBfmeNarrowRecord00427F75, retail 0x00428149 37B.
// The declared specialization keeps _Construct at 0x004280F6 an out-of-line call. Element stride
// is 0x18 (two STLport basic_string<char>). Callers at 0x0042847F 0x004284CA
// (copy) and 0x004284AC (fill) inside FUN_0082843e.
// Retail's loops carry no try blocks: STLport's no-exceptions configuration.
#define _STLP_NO_EXCEPTIONS
#include <string>
#include <memory>

// Dedicated TU so _Construct at 0x004280F6 stays an out-of-line call. Element stride
struct BfmeNarrowRecord00427F75
{
	_STL::basic_string<char> m_key;
	_STL::basic_string<char> m_value;
	BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &);
	~BfmeNarrowRecord00427F75();
};

namespace _STL { template <> void _Construct<BfmeNarrowRecord00427F75,BfmeNarrowRecord00427F75>(BfmeNarrowRecord00427F75 *,BfmeNarrowRecord00427F75 const &); }

template BfmeNarrowRecord00427F75 *_STL::__uninitialized_copy<const BfmeNarrowRecord00427F75 *, BfmeNarrowRecord00427F75 *>(const BfmeNarrowRecord00427F75 *, const BfmeNarrowRecord00427F75 *, BfmeNarrowRecord00427F75 *, const _STL::__false_type &);

template BfmeNarrowRecord00427F75 *_STL::__uninitialized_fill_n<BfmeNarrowRecord00427F75 *, unsigned int, BfmeNarrowRecord00427F75>(BfmeNarrowRecord00427F75 *, unsigned int, const BfmeNarrowRecord00427F75 &, const _STL::__false_type &);

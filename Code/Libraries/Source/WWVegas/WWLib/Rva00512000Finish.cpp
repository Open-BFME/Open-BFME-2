// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0?$vector@URva00511E48@@V?$allocator@URva00511E48@@@_STL@@@_STL@@QAE@I@Z @ 0x00512000, 105B.
// _STL::vector<Rva00511E48>::vector(size_type) -- the single-argument fill
// constructor.  Rva00511E48 is the 8-byte AsciiString+char element implied by
// the mangling and by the 8-byte-stride fill; its real identity is unknown, so
// the address-derived name is used.
//
// Retail calls the out-of-line 3-argument __uninitialized_fill_n wrapper at
// 0x00511F58 (row in Rva00511E48FillN.cpp) after constructing one value_type
// temporary; the vendored STLport header instead defines only the inline
// single-underscore uninitialized_fill_n, whose body is inlined straight to the
// false_type overload.  Specializing _STL::vector for this element and calling
// a declared (undefined) 3-argument __uninitialized_fill_n reproduces retail's
// call exactly.  The base ctor call resolves to the ICF-folded 8-byte
// _Vector_base<Rva00511E48> ctor at 0x000B6378 (pinned in symbols.csv from this
// very REL32 site).  Reached from AptMessenger Init at 0x0051215B.

#include "ascii_string.h"
#include <vector>

struct Rva00511E48
{
	AsciiString m_str;
	char m_c;
	char m_pad[3];
	Rva00511E48() : m_str(AsciiString::TheEmptyString), m_c(0) {}
	Rva00511E48(const Rva00511E48 &o) : m_str(o.m_str), m_c(o.m_c) {}
	~Rva00511E48() {}
};

namespace _STL
{

// Declared, not defined: the body is the led row at 0x00511F58.
template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x);

template <>
class vector<Rva00511E48, allocator<Rva00511E48> > : public _Vector_base<Rva00511E48, allocator<Rva00511E48> >
{
public:
	explicit vector(unsigned int n);
};

vector<Rva00511E48, allocator<Rva00511E48> >::vector(unsigned int n)
	: _Vector_base<Rva00511E48, allocator<Rva00511E48> >(n, allocator<Rva00511E48>())
{
	this->_M_finish = __uninitialized_fill_n(this->_M_start, n, Rva00511E48());
}

}

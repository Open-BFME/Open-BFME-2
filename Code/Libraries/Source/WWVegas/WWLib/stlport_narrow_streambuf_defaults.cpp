// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// Two of the narrow basic_streambuf base defaults, written out rather than
// instantiated. basic_streambuf<char> is an explicit specialisation in the
// vendored headers, so `template class` on it is C2950 and no user TU emits
// its members - the wide facet has no such problem, which is why
// stlport_wide_streambuf.cpp covers the wide side of this vtable.
//
// Both bodies are the upstream defaults from vendor/stlport/stl/_streambuf.h:
// underflow and pbackfail each return eof, which for char_traits<char> is the
// int -1, so each is an or eax, -1 and a return. The narrow streambuf vtable
// holds 0x0001CA70 in both slot 9 and slot 12, so overflow folded onto
// pbackfail; it is rowed below as that body's ICF twin.

#include "../../../../GameEngine/Source/Common/StdioStreambufBaseView.h"

namespace _STL
{

int basic_streambuf<char, char_traits<char> >::underflow() { return char_traits<char>::eof(); }
int basic_streambuf<char, char_traits<char> >::pbackfail(int_type c) { return char_traits<char>::eof(); }
void basic_streambuf<char, char_traits<char> >::imbue(const locale &) {}
int basic_streambuf<char, char_traits<char> >::showmanyc() { return 0; }
int basic_streambuf<char, char_traits<char> >::sync() { return 0; }
basic_streambuf<char, char_traits<char> > *basic_streambuf<char, char_traits<char> >::setbuf(char *, int) { return this; }
int basic_streambuf<char, char_traits<char> >::overflow(int_type c) { return char_traits<char>::eof(); }
fpos<int> basic_streambuf<char, char_traits<char> >::seekoff(long, int, int) { return fpos<int>(-1); }
fpos<int> basic_streambuf<char, char_traits<char> >::seekpos(fpos<int>, int) { return fpos<int>(-1); }

}

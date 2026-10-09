// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME 1 repair 4d8b11e1bf at donor f98983a7d3.
// BFME 2 descriptor constructor 0x0001EDE0 retains its verified 255-byte body.
#define _STLP_LINK_TIME_INSTANTIATION 1
#include <stl/_fstream.h>

namespace _STL {
template <> inline basic_ios<char, char_traits<char> >::basic_ios()
    : ios_base(), _M_fill(0), _M_streambuf(0), _M_tied_ostream(0) {}

template <> inline basic_ostream<char, char_traits<char> >::basic_ostream(
    basic_streambuf<char, char_traits<char> > *buf)
    : basic_ios<char, char_traits<char> >()
{
    this->init(buf);
}

template <> inline basic_ostream<char, char_traits<char> >::~basic_ostream() {}
template <> inline basic_ofstream<char, char_traits<char> >::~basic_ofstream() {}

template basic_ofstream<char, char_traits<char> >::basic_ofstream(int, ios_base::openmode);
}

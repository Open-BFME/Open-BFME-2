// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME 1 donor 3d1b1f6431 at reference revision f98983a7d3.
// BFME 2 retains the established address-qualified constructor identity;
// its complete 263-byte body at 0x0001F650 verifies the native STLport bases.
// The internal declaration header avoids the wrapper's per-TU locale initializer.
#define _STLP_LINK_TIME_INSTANTIATION 1
// The internal declaration header avoids the wrapper's per-TU locale initializer.
#include <stl/_fstream.h>

namespace _STL {
template <>
inline basic_ios<char, char_traits<char> >::basic_ios()
	: ios_base(), _M_fill(0), _M_streambuf(0), _M_tied_ostream(0)
{}

template <class CharT, class Traits>
class basic_ifstream_lib0084C300 : public basic_istream<CharT, Traits> {
public:
	basic_ifstream_lib0084C300(const char *name, ios_base::openmode mode)
		: basic_ios<CharT, Traits>(), basic_istream<CharT, Traits>(0), buf_()
	{
		this->init(&buf_);
		// The witnessed library open call takes explicit protection 0x80.
		if (!buf_.open(name, mode | ios_base::in, 0x80))
			this->setstate(ios_base::failbit);
	}
private:
	basic_filebuf<CharT, Traits> buf_;
};

template basic_ifstream_lib0084C300<char, char_traits<char> >::basic_ifstream_lib0084C300(
	const char *, ios_base::openmode);
}

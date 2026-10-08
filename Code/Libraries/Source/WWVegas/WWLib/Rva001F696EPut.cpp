// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva001F696EPut@@YAAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@AAV12@ABVAsciiString@@@Z @0x001F696E 35B
// Evidence: retail ternary m_text ? m_text+8 : g_Rva0107301CEmptyString plus rowed _M_put_nowiden at 0x001F5F65; caller 0x001F831D passes ostream plus 4th arg and uses result for _M_put_char; pattern from Rva001F8810Put plus Rva005B0E60.
#include "ascii_string.h"

namespace _STL
{
template <class C> class char_traits
{
};

template <class C, class T> class basic_ostream
{
public:
	void _M_put_nowiden(char const *s);
	basic_ostream &operator<<(float f);
	void _M_put_char(char c);
};
}


_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F696EPut(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	const char *p = t ? t + 8 : "";
	os._M_put_nowiden(p);
	return os;
}

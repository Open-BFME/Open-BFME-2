// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva001F82EEWrite@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDABVAsciiString@@@Z @0x001F82EE 66B: free ostream INI key-value line with pad via rowed Pad/Put.
// Evidence: calls rowed Pad 0x001F6951 then rowed _M_put_nowiden 0x001F5F65 twice (key then " = ") then rowed Put 0x001F696E then rowed _M_put_char 0x001F5E51 newline; callers are writeINI bodies.
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
	void _M_put_char(char c);
};
}

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F6951Pad(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int n);
_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F696EPut(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	const AsciiString &s);

void Rva001F82EEWrite(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const AsciiString &value)
{
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(os, pad);
	r._M_put_nowiden(key);
	r._M_put_nowiden(" = ");
	_STL::basic_ostream<char, _STL::char_traits<char> > &r2 = Rva001F696EPut(os, value);
	r2._M_put_char('\n');
}

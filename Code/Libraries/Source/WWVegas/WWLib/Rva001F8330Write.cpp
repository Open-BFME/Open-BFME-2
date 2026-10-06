// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva001F8330Write@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDABVAsciiString@@@Z @0x001F8330 23B: free ostream INI key-value line skipping empty via rowed Write.
// Evidence: calls rowed StringBase isEmpty 0x00001E2F on value then tail-jmps to rowed Write 0x001F82EE; pattern from Rva001F82EEWrite; StringBase cast calls the rowed out-of-line isEmpty not the header inline AsciiString one.
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

void Rva001F82EEWrite(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const AsciiString &value);

void Rva001F8330Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const AsciiString &value)
{
	if (((const StringBase<char> &)value).isEmpty())
		return;
	return Rva001F82EEWrite(os, pad, key, value);
}

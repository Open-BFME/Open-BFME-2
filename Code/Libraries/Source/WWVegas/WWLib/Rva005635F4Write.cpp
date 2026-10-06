// cl: /DNDEBUG /MD
//
// ?Rva005635F4Write@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDABURva005635DEPayload@@@Z @0x005635F4 66B: free ostream INI key-long line with pad via rowed Pad/Put.
// Evidence: calls rowed Pad 0x001F6951 then rowed _M_put_nowiden 0x001F5F65 twice (key then " = ") then rowed Rva005635DEPut 0x005635DE then rowed _M_put_char 0x001F5E51 newline; caller at 0x0056364C in 0x00563636/31; pattern from Rva001F8BA1Write 0x001F8BA1.
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

struct Rva005635DEPayload
{
	long value;
};

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F6951Pad(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int n);
_STL::basic_ostream<char, _STL::char_traits<char> > &Rva005635DEPut(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	const Rva005635DEPayload &payload);

void Rva005635F4Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const Rva005635DEPayload &value)
{
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(os, pad);
	r._M_put_nowiden(key);
	r._M_put_nowiden(" = ");
	_STL::basic_ostream<char, _STL::char_traits<char> > &r2 = Rva005635DEPut(os, value);
	r2._M_put_char('\n');
}
//
// ?Rva00563636Write@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDABURva005635DEPayload@@@Z @0x00563636 31B
// chain from 0x005635F4: skips zero payload.value else forwards os/pad/key/value to Rva005635F4Write; callers writeINI 0x00563655/675 0x00563D3F/288.
void Rva00563636Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const Rva005635DEPayload &value)
{
	if (value.value == 0)
		return;
	Rva005635F4Write(os, pad, key, value);
}

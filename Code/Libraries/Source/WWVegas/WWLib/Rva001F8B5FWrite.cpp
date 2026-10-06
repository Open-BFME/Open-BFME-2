// cl: /DNDEBUG /MD
// ?Rva001F8B5FWrite@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDABUS001F87D5@@@Z @0x001F8B5F 66B: free ostream INI key-floatpair line with pad via rowed Pad/Put.
// Evidence: calls rowed Pad 0x001F6951 then rowed _M_put_nowiden 0x001F5F65 twice (key then " = ") then rowed S Put 0x001F87D5 then rowed _M_put_char 0x001F5E51 newline; callers are writeINI bodies; pattern from Rva001F89E2Write.
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

struct S001F87D5
{
	char _0[4];
	float x;
	float y;
};

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F6951Pad(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int n);
_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F87D5Put(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	const S001F87D5 &s);

void Rva001F8B5FWrite(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const S001F87D5 &value)
{
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(os, pad);
	r._M_put_nowiden(key);
	r._M_put_nowiden(" = ");
	_STL::basic_ostream<char, _STL::char_traits<char> > &r2 = Rva001F87D5Put(os, value);
	r2._M_put_char('\n');
}

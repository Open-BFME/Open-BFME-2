// cl: /DNDEBUG /MD
// ?Rva003A5D34Write@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDABM@Z @0x003A5D34 66B: free ostream INI key-float line with pad via rowed Pad/Put.
// Evidence: calls rowed Pad 0x001F6951 then rowed _M_put_nowiden 0x001F5F65 twice (key then " = ") then rowed Put 0x003A5D1C then rowed _M_put_char 0x001F5E51 newline; 25 callers incl FUN_007a5e78 writeINI bodies; pattern from Rva001F89E2Write; chain lane via 0x001F6951.
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
_STL::basic_ostream<char, _STL::char_traits<char> > &Rva003A5D1CPut(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	float const &f);

void Rva003A5D34Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	float const &value)
{
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(os, pad);
	r._M_put_nowiden(key);
	r._M_put_nowiden(" = ");
	_STL::basic_ostream<char, _STL::char_traits<char> > &r2 = Rva003A5D1CPut(os, value);
	r2._M_put_char('\n');
}

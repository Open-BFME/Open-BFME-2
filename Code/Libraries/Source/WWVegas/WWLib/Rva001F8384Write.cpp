// cl: /DNDEBUG /MD
// ?Rva001F8384Write@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDPB_N@Z @0x001F8384 69B: free ostream INI key-bool line with pad via rowed Pad.
// Evidence: calls rowed Pad 0x001F6951 then rowed _M_put_nowiden 0x001F5F65 twice (key then " = ") then rowed YesNo Put 0x001F6991 then rowed _M_put_char 0x001F5E51 newline; callers are writeINI bodies and cond loop at 0x001F89C3; pattern from Rva001F89E2Write.
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
_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F6991Put(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	bool flag);

void Rva001F8384Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	bool const *value)
{
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(os, pad);
	r._M_put_nowiden(key);
	r._M_put_nowiden(" = ");
	_STL::basic_ostream<char, _STL::char_traits<char> > &r2 = Rva001F6991Put(os, *value);
	r2._M_put_char('\n');
}

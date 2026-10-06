// cl: /DNDEBUG /MD
// ?Rva001F82ABWrite@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDPAPBD@Z @0x001F82AB 67B: free ostream INI key stringptr line with pad via rowed Pad.
// Evidence: calls rowed Pad 0x001F6951 then rowed _M_put_nowiden 0x001F5F65 twice (key then " = ") then rowed _M_put_nowiden on *value then rowed _M_put_char newline; callers are writeINI bodies; pattern from Rva001F89E2Write.
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

void Rva001F82ABWrite(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	char const **value)
{
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(os, pad);
	r._M_put_nowiden(key);
	r._M_put_nowiden(" = ");
	os._M_put_nowiden(*value);
	os._M_put_char('\n');
}

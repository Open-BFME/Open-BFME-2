// cl: /DNDEBUG /MD
// ?Rva001F89E2Write@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDABUVec001F8810@@@Z @0x001F89E2 66B: free ostream INI key-vector line with pad via rowed Pad/Put.
// Evidence: calls rowed Pad 0x001F6951 then rowed _M_put_nowiden 0x001F5F65 twice (key then " = ") then rowed Vec Put 0x001F8810 then rowed _M_put_char 0x001F5E51 newline; callers are writeINI bodies; pattern from Rva001F82EEWrite.
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

struct Vec001F8810
{
	float x;
	float y;
	float z;
};

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F6951Pad(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int n);
_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F8810Put(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	const Vec001F8810 &v);

void Rva001F89E2Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const Vec001F8810 &value)
{
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(os, pad);
	r._M_put_nowiden(key);
	r._M_put_nowiden(" = ");
	_STL::basic_ostream<char, _STL::char_traits<char> > &r2 = Rva001F8810Put(os, value);
	r2._M_put_char('\n');
}

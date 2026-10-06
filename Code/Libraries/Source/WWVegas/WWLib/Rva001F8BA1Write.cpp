// cl: /DNDEBUG /MD
// ?Rva001F8BA1Write@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDABUTreeHintPayload001F8ACB@@@Z @0x001F8BA1 66B: free ostream INI key-uint line with pad via rowed Pad/Put.
// Evidence: calls rowed Pad 0x001F6951 then rowed _M_put_nowiden 0x001F5F65 twice (key then " = ") then rowed TreeHint Put 0x001F84A7 then rowed _M_put_char 0x001F5E51 newline; caller at 0x001F901C; pattern from Rva001F89E2Write.
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

struct TreeHintPayload001F8ACB
{
	unsigned long value;
};

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F6951Pad(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int n);
_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F84A7Put(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	const TreeHintPayload001F8ACB &payload);

void Rva001F8BA1Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const TreeHintPayload001F8ACB &value)
{
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(os, pad);
	r._M_put_nowiden(key);
	r._M_put_nowiden(" = ");
	_STL::basic_ostream<char, _STL::char_traits<char> > &r2 = Rva001F84A7Put(os, value);
	r2._M_put_char('\n');
}

// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva001F6991Put@@YAAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@AAV12@_N@Z @0x001F6991 32B: ostream Yes/No writer.
// Evidence: calls rowed _M_put_nowiden 0x001F5F65 with Yes/No literal selected by bool; caller 0x001F8384 passes ostream plus bool byte and uses result for _M_put_char; pattern from Rva001F696EPut.
namespace _STL
{
template <class C> class char_traits
{
};

template <class C, class T> class basic_ostream
{
public:
	void _M_put_nowiden(char const *s);
};
}

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F6991Put(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	bool flag)
{
	const char *p = flag ? "Yes" : "No";
	os._M_put_nowiden(p);
	return os;
}

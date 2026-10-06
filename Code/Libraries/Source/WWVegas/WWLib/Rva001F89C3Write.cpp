// cl: /DNDEBUG /MD
// ?Rva001F89C3Write@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDPB_N@Z @0x001F89C3 31B: free ostream INI key-bool line skipping false via rowed Write.
// Evidence: checks byte at value ptr then calls rowed Write 0x001F8384 with same 4 args; callers are writeINI bodies; pattern from Rva001F8330Write.
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

void Rva001F8384Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	bool const *value);

void Rva001F89C3Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	bool const *value)
{
	if (*value == false)
		return;
	return Rva001F8384Write(os, pad, key, value);
}

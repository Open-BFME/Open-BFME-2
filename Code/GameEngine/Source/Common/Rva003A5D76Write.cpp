// cl: /DNDEBUG /MD
// ?Rva003A5D76Write@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDABM2@Z @0x003A5D76 42B: guarded ostream INI key-float line writes only when value differs.
// Evidence: calls rowed Rva003A5D34Write 0x003A5D34 with ostream pad key value when float compare differs; SSE movss ucomiss lahf test jnp skip; chain via 0x003A5D34.
namespace _STL
{
template <class C> class char_traits
{
};

template <class C, class T> class basic_ostream
{
};
}

void Rva003A5D34Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	float const &value);

void Rva003A5D76Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	float const &value,
	float const &def)
{
	if (value != def)
		Rva003A5D34Write(os, pad, key, value);
}

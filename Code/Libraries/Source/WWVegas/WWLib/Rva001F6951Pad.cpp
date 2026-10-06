// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva001F6951Pad@@YAAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@AAV12@I@Z @0x001F6951 29B: free ostream pad writes N spaces via rowed put.
// Evidence: calls rowed put 0x001F6537 in dec-jne loop with test-jbe guard for N==0; callers pad key field before INI write; pattern from Rva001F696EPut custom ostream decl for frameless shape.
namespace _STL
{
template <class C> class char_traits
{
};

template <class C, class T> class basic_ostream
{
public:
	basic_ostream &put(char c);
};
}

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F6951Pad(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int n)
{
	for (; n > 0; --n) {
		os.put(' ');
	}
	return os;
}

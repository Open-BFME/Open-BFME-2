// cl: /DNDEBUG /MD
//
// ?Rva003A5D1CPut@@YAAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@AAV12@ABM@Z, retail 0x003A5D1C, 24 bytes.
// Unlock lane; ostream float put via rowed float operator<< at 0x001F8152.
// Caller at 0x003A5D63 passes ostream at +0x08 and float ptr at +0x14, uses
// result as ostream for _M_put_char. Prev ConstIntGetters4, next
// DefaultAlphaModuleInfo::GetSnapshotName. Pattern copied from
// Rva001F8810Put.cpp (minimal _STL decl forcing a CALL, /O1 /DNDEBUG /MD).
namespace _STL
{
template <class C> class char_traits
{
};

template <class C, class T> class basic_ostream
{
public:
	void _M_put_nowiden(char const *s);
	basic_ostream &operator<<(float f);
	void _M_put_char(char c);
};
}

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva003A5D1CPut(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	float const &f)
{
	os << f;
	return os;
}

// cl: /DNDEBUG /MD /EHsc /Od /D_STLP_USE_STATIC_LIB
// stlport46
// Two run wrappers built on the char_traits<char>::length helper at 0x00006F30.
// 0x00028BC0 is STLport 4.5.3's basic_string<char>::find(const char *, size_type)
// const: it forwards (s, pos, length(s)) to the three-argument find at
// 0x00027540. The plain /Od build keeps both calls out of line, as retail does.
// The 0x00028CC0 sibling keeps its address-derived names; its callee is pinned
// (bfmeDoPG at 0x00027740).
#include <string>

namespace _STL {
// Retail's three-argument find and its search core are emitted by
// stlport_reverse_string_search.cpp under /Od /Ob2; this unit only calls them.
template <> string::size_type string::find(const char *, string::size_type, string::size_type) const;
template <> const char *search(const char *, const char *, const char *, const char *, _Eq_traits<char_traits<char> >);
template string::size_type string::find(const char *, string::size_type) const;
}

int bfmeMakeOX(void *text);

class BfmeThingPG
{
public:
	void bfmeDoPG(char *at, void *what, int many);
	void rva00028cc0(void *at, void *what);
};

void BfmeThingPG::rva00028cc0(void *at, void *what)
{
	bfmeDoPG((char *)at, what, bfmeMakeOX(at));
}

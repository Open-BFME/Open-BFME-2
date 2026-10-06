// ?Rva003F2BEBDeleteRange@@YA_NPAPAV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@0_N@Z
// partial score=0.91 date=2026-09-29
// cl: /Oy- /MD
//
// ?Rva003F2BEBDeleteRange@@YA_NPAPAV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@0_N@Z retail 0x003F2BEB 33B
// Range delete over narrow strings. Retail passes the element on the stack and
// the address of the flag argument in ECX, so the callee is the thiscall ICF
// twin of the matched __stdcall delete at 0x00423FBD (body ignores ECX). The
// twin is pinned in symbols.csv under this address-derived member name.
namespace _STL
{
template <class T> class char_traits {};
template <class T> class allocator {};
template <class CharT, class Traits, class Alloc> class basic_string
{
public:
	~basic_string();
};
typedef basic_string<char, char_traits<char>, allocator<char> > narrow_string;
}

class Rva00423FBDThis
{
public:
	void Delete(_STL::narrow_string *p);
};

bool __cdecl Rva003F2BEBDeleteRange(_STL::narrow_string **begin, _STL::narrow_string **end, bool flag)
{
	for (; begin != end; ++begin)
		((Rva00423FBDThis *)&flag)->Delete(*begin);
	return flag;
}

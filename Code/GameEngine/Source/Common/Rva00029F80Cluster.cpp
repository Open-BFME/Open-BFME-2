// cl: /DNDEBUG /MD /EHsc /Od /D_STLP_USE_STATIC_LIB
// stlport46
// Siblings of the BfmeConv1428 wrapper recipe. Both are thin thiscall
// forwarders: the first hands its first two arguments to the private
// _M_range_initialize pinned at 0x000078C0 with a materialised iterator tag;
// its names are address-derived. The second, 0x0002A2A0, is STLport 4.6's
// basic_string<char>::rfind(const char *, size_type) const (_string.h),
// forwarding (s, pos, length(s)) to rfind(const char *, size_type, size_type)
// at 0x00029850 (BfmeConv1480.cpp); plain /Od keeps length out of line.
#include <string>

extern template _STL::string::size_type _STL::string::rfind(const char *, _STL::string::size_type, _STL::string::size_type) const;

namespace _STL {
template string::size_type string::rfind(const char *, string::size_type) const;
}

class Rva00029F80
{
public:
	void rva00029f80(const char *first, const char *last, int unused);

private:
	void rva00078c0(const char *first, const char *last, void *tag);
};

void Rva00029F80::rva00029f80(const char *first, const char *last, int unused)
{
	char tag;
	int pad[4];
	rva00078c0(first, last, &tag);
}

// The retail call in this body reads 0x000078C0, an address the ledger already
// carries as ??$_M_range_initialize@PBD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAEXPBD0ABUforward_iterator_tag@1@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?rva00078c0@Rva00029F80@@AAEXPBD0PAX@Z=??$_M_range_initialize@PBD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAEXPBD0ABUforward_iterator_tag@1@@Z")

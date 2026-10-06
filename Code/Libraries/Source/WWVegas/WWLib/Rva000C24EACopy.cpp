// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__copy@PBVRva000C24EA@@PAV1@H@_STL@@YAPAVRva000C24EA@@PBV1@0PAV1@ABUrandom_access_iterator_tag@0@PAH@Z @0x000C376C 47B
// STL copy over 32-byte Rva000C24EA via rowed operator= @0x000C24EA; caller @0x000C47A8; stride 0x20 sar 5.
#include <vector>
#include <string>

struct DwordTriple
{
	int a;
	int b;
	int c;
};

class Rva000C24EA
{
public:
	Rva000C24EA &operator=(const Rva000C24EA &other);

private:
	int m_00;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_04;
	DwordTriple m_10;
	int m_1C;
};

template Rva000C24EA *_STL::__copy<const Rva000C24EA *, Rva000C24EA *, int>(
	const Rva000C24EA *first, const Rva000C24EA *last, Rva000C24EA *result,
	const _STL::random_access_iterator_tag &, int *);

// ??$copy@PBVRva000C24EA@@PAV1@@_STL@@YAPAVRva000C24EA@@PBV1@0PAV1@@Z @0x000C4795 29B
// copy wrapper over __copy @0x000C376C with tag plus NULL distance; callers @0x000C4D6D @0x000C4DD0.
template Rva000C24EA *_STL::copy<const Rva000C24EA *, Rva000C24EA *>(
	const Rva000C24EA *first, const Rva000C24EA *last, Rva000C24EA *result);

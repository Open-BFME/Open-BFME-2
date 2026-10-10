// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??4Rva000C24EA@@QAEAAV0@ABV0@@Z @0x000C24EA 51B
// Record copy-assign: dword at +0, narrow string at +4 via rowed
// ?assign@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@ABV12@@Z
// @0x000120C0, 12B triple at +0x10 (3x movsd), dword at +0x1C.
// Evidence: ret 4 with this in eax; caller @0x000C3785.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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

Rva000C24EA &Rva000C24EA::operator=(const Rva000C24EA &other)
{
	m_00 = other.m_00;
	m_04.assign(other.m_04);
	m_10 = other.m_10;
	m_1C = other.m_1C;
	return *this;
}

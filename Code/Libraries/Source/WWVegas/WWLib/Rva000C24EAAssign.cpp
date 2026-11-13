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
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::assign(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

#include "DwordTriple.h"

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

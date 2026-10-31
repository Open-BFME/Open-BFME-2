// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Copy assignment (35B) of the stride-0x14 element served by the __copy loop at
// 0x004039E0 (count via idiv 0x14, per-element call) and its 29B forwarding wrapper
// at 0x00403BD2: two scalar words, then a vector<AsciiString> at +8 assigned through
// the rowed operator= 0x000BDB46. Copy ctor ??0Rva00403927@@QAE@ABV0@@Z 35B @0x004039BD
// same layout via rowed vector copy ctor 0x000BC07E unblocks 0x00403B5A.
// Application identity unknown, so an Rva owner name is used. Frameless /O1 matches
// retail (opens with mov eax,[esp+4]).
#include "ascii_string.h"
#include <vector>

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> vector<AsciiString, allocator<AsciiString> >::vector(const vector<AsciiString, allocator<AsciiString> >&);
template <> _Vector_base<AsciiString, allocator<AsciiString> >::_Vector_base(size_t, const allocator<AsciiString>&);
template <> AsciiString *__uninitialized_copy(const AsciiString*, const AsciiString*, AsciiString*, const __false_type&);
template <> vector<AsciiString, allocator<AsciiString> > &vector<AsciiString, allocator<AsciiString> >::operator=(const vector<AsciiString, allocator<AsciiString> >&);
}

class Rva00403927
{
public:
	Rva00403927(const Rva00403927 &other);
	Rva00403927 &operator=(const Rva00403927 &other);
private:
	int m_00;
	int m_04;
	_STL::vector<AsciiString> m_names;
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva00403927::Rva00403927(const Rva00403927 &other)
	: m_00(other.m_00), m_04(other.m_04), m_names(other.m_names)
{
}

// ?bfmeAnchorRva00403927Ctor absent-from-retail
void *bfmeAnchorRva00403927Ctor(void *where, const Rva00403927 &other)
{
	return ::new (where) Rva00403927(other);
}

// ??4Rva00403927@@QAEAAV0@ABV0@@Z @0x00403927
Rva00403927 &Rva00403927::operator=(const Rva00403927 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_names = other.m_names;
	return *this;
}

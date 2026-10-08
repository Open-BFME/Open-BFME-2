// cl: /O1 /EHsc /MD
// WB A864F0 uses the same cache destructor A89F90 as music loader A86AD0.
// Preserve the existing empty-header constructor spelling in this bounded
// repair; its BfmeE16 parameter does not establish the cache element type.
// stlport
// ?rva0032FEF5@Rva0032FEF5@@QAEXXZ, retail 0x0032FEF5, 83 bytes.
// Loop calling pinned 2-arg helper 0x0032FC70 with index and a temp inner
// vector; temp constructed via rowed _Vector_base<BfmeE16> ctor and destroyed
// via rowed ??1LibraryMapCache dtor (same pattern as matched 0x0032FF48 wrapper).
// Evidence: __EH_prolog with mov/or [ebp-4] states, xor edi loop over
// [esi+0x3c], lea/push temp plus index with mov ecx,esi call, tail dtor call.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

struct Rva0019D850Value
{
	int m_words[3];
};

class LibraryMapCache : public _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >
{
public:
// ??0LibraryMapCache@@QAE@XZ present-unmatched
	LibraryMapCache() : _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >(_STL::allocator<BfmeE16>()) {}
	~LibraryMapCache();
};

class Rva0032FEF5 : public _STL::vector<_STL::vector<Rva0019D850Value> >
{
	int m_pad[12];
	int m_count;
public:
	void rva0032FEF5();
};

void Rva0032FEF5::rva0032FEF5()
{
	LibraryMapCache tmp;
	for (int i = 0; i < m_count; ++i)
		this->resize(i, reinterpret_cast<const _STL::vector<Rva0019D850Value> &>(tmp));
}

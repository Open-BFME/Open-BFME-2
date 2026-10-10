// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 24-byte Rva000BB4AC vector allocation/copy helper: base Rva000B9074
// (0x14) plus refcounted pointer tail, stride 0x18. Copy ctor is rowed at
// 0x000BB4AC and _Construct at 0x000BB9C0; vector instantiation emits the
// __uninitialized callers (0x000BBB12 0x000BBB38 and siblings).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

class Rva000BB4AC
{
public:
	Rva000BB4AC();
	Rva000BB4AC(const Rva000BB4AC &o);
private:
	char m_pad[0x18];
};
#include <vector>
template class _STL::vector<Rva000BB4AC, _STL::allocator<Rva000BB4AC> >;

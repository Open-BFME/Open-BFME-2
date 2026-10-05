// cl: /O1 -GX- /Ireference/shims/bfmealloc
// stlport
// vector<Rva0014F480>::_M_insert_overflow @0x00150282, 181B.
// Masked twin of Rva005DBCD1 overflow 0x005DC499.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{ return a < b ? b : a; }
}
#pragma optimize("", on)
#include <vector>
class Rva0014F480 {
public:
 Rva0014F480();
 Rva0014F480(const Rva0014F480 &);
 Rva0014F480 &operator=(const Rva0014F480 &);
 virtual ~Rva0014F480();
 short m_field04, m_field06;
};
template void _STL::vector<Rva0014F480, _STL::allocator<Rva0014F480> >::_M_insert_overflow(
    Rva0014F480 *, const Rva0014F480 &, const _STL::__false_type &, unsigned int, bool);

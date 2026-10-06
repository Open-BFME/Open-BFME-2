// cl: -GX- /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 _vector.h, also present in BFME 1 donor
// 6583b3c1ff21db4a561285717028fdafc780b7db. Original application type unknown.
// Retail boundary 0x005DC499..0x005DC54E, 181B, ret 0x14 proves five arguments.
// Copy calls 0x005DBCD1/0x005DBD4F/0x005DBD78 establish this eight-byte record:
// its rowed constructor installs a vptr and copies shorts at +4 and +6.
// The shared clear path 0x005659CA -> 0x005A6EDA -> 0x0052BF33 destroys an
// eight-byte range through virtual slot zero, then frees the allocation.
// All six helper aliases were independently full-byte verified, including
// their called constructor/destruction chain, before entering symbols.csv.
// Keep the inline max overload local to avoid a competing external definition.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
class Rva005DBCD1 {
public:
 Rva005DBCD1();
 Rva005DBCD1(const Rva005DBCD1 &);
 Rva005DBCD1 &operator=(const Rva005DBCD1 &);
 virtual ~Rva005DBCD1();
 short m_field04, m_field06;
};
// Instantiate only the served overflow member; helper COMDATs retain their
// reference definitions and can link against the existing record constructor.
// Preserve STLport placement-copy inlining without emitting another external
// specialization; StlportConstructCopySiblings.cpp owns the retail helper.
namespace _STL {
static inline void _Construct(Rva005DBCD1 *dest, const Rva005DBCD1 &source) { new (dest) Rva005DBCD1(source); }
}

template void _STL::vector<Rva005DBCD1, _STL::allocator<Rva005DBCD1> >::_M_insert_overflow(
    Rva005DBCD1 *, const Rva005DBCD1 &, const _STL::__false_type &, unsigned int, bool);

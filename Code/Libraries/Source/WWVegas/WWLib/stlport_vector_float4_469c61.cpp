// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 vector helpers for a target-derived 16-byte record.
// Caller 0x538A0B reads four floats into a stack record, reserves via 0x538839,
// then appends it via 0x473F13. Copy/fill workers advance by 16 bytes and
// construct via 0x469C61 -> 0x4254E. The original project type is unresolved.
// The folded copy and allocator are existing ranges, not additional claims.
// Keep this inlined unsigned max overload local; retail has one external owner.
// Define it for speed, then restore this unit's flags for its vector bodies.
#pragma optimize("s", off)
#pragma optimize("t", on)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
struct BfmeFloat4Record00469C61 {
    float x, y, z, w;
    BfmeFloat4Record00469C61() {}
    BfmeFloat4Record00469C61(const BfmeFloat4Record00469C61 &o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
    BfmeFloat4Record00469C61 &operator=(const BfmeFloat4Record00469C61 &o) { x=o.x; y=o.y; z=o.z; w=o.w; return *this; }
};
template BfmeFloat4Record00469C61 *_STL::vector<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> >::_M_allocate_and_copy<BfmeFloat4Record00469C61 *>(unsigned int, BfmeFloat4Record00469C61 *, BfmeFloat4Record00469C61 *);
template void _STL::vector<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> >::reserve(unsigned int);
template void _STL::vector<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> >::_M_insert_overflow(BfmeFloat4Record00469C61 *, const BfmeFloat4Record00469C61 &, const _STL::__false_type &, unsigned int, bool);
template void _STL::vector<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> >::push_back(const BfmeFloat4Record00469C61 &);

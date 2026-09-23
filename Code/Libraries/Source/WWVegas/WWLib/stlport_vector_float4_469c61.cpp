// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 vector helpers for a target-derived 16-byte record.
// Caller 0x538A0B reads four floats into a stack record, reserves via 0x538839,
// then appends it via 0x473F13. Copy/fill workers advance by 16 bytes and
// construct via 0x469C61 -> 0x4254E. The original project type is unresolved.
// The folded copy and allocator are existing ranges, not additional claims.
#include <vector>
struct BfmeFloat4Record00469C61 {
    float x, y, z, w;
    BfmeFloat4Record00469C61() {}
    BfmeFloat4Record00469C61(const BfmeFloat4Record00469C61 &o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
    BfmeFloat4Record00469C61 &operator=(const BfmeFloat4Record00469C61 &o) { x=o.x; y=o.y; z=o.z; w=o.w; return *this; }
};
template class _STL::vector<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> >;

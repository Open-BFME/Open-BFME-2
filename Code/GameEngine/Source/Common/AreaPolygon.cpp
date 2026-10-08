// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0030BAD8@Rva0030BAD8@@QAEXHABUBfmeE8@@@Z
// WorldBuilder 0x00BF5AA0 identifies AreaPolygonBase::insertPoint in
// AreaPolygon.cpp (line 109). Retail 0x0030BAD8..0x0030BAF8 is its
// assertion-free body: insert at begin()+index, then invalidate the bounds.
// The vector at +0 and dirty flag at +24 agree with the rowed parse/delete
// siblings. BfmeE8 preserves the existing provisional two-float point view;
// its original type name is not established by this recovery.
// Keep the established address-derived linker name used by the vtable caller.
// WorldBuilder establishes the original method identity independently above.
// The original STLport algorithm header preserves the out-of-line
// four-argument copy wrapper called at retail 0x0030BA58. The local
// bfmealloc algorithm shim force-inlines it and adds a fifth argument.
// Keep the allocator shim for allocation; select only this original header.
#include "../../../../vendor/stlport/stl/_algobase.h"
#include <vector>

struct BfmeE8 {
    float x, y;
    BfmeE8() {}
    BfmeE8(const BfmeE8& value): x(value.x), y(value.y) {}
};

// Retail 0x0030B9F3..0x0030BA8C is the STLport insertion provider called
// below: the explicit float copy constructor reproduces its movss temporary
// copies. Pointer stride and the point caller establish the eight-byte ABI;
// the original point type name remains unknown.

struct Rva0030BAD8 {
    _STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_points;
    char m_pad[0x24 - 12];
    bool m_dirty;
    void rva0030BAD8(int index, const BfmeE8& point);
};

void Rva0030BAD8::rva0030BAD8(int index, const BfmeE8& point)
{
    m_points.insert(m_points.begin() + index, point);
    m_dirty = true;
}

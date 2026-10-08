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
#include <vector>

struct BfmeE8 { float x; float y; };

// Retail calls the out-of-line provider at 0x0030B9F3. Its native body
// constructs/shifts eight-byte elements or calls _M_insert_overflow, then
// returns begin()+the saved index. Declare the existing provider rather
// than emitting a competing implementation of that still-unmatched body.
namespace _STL {
template<> vector<BfmeE8, allocator<BfmeE8> >::iterator
vector<BfmeE8, allocator<BfmeE8> >::insert(iterator, const value_type&);
}

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

// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Destroy@PAURva00255D17@@@_STL@@YAXPAURva00255D17@@0@Z @0x00050A60 25B range destroy stride 0x24 via rowed dtor 0x00255D17; callers 0x00050A93 0x00064467 0x000644FD; same loop as rowed 0x00481595.
#include <vector>
struct Rva00255D17
{
    ~Rva00255D17();
    unsigned char m_data[0x24];
};
template void _STL::_Destroy<Rva00255D17 *>(Rva00255D17 *, Rva00255D17 *);

// vector dtor (retail 0x00050A79) and _M_clear (0x0006445F): byte-identical
// explicit member instantiations; both call the _Destroy above and _free.
template _STL::vector<Rva00255D17>::~vector();
template void _STL::vector<Rva00255D17>::_M_clear();

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1GeometryShapeVector@@QAE@XZ=??1?$vector@URva00255D17@@V?$allocator@URva00255D17@@@_STL@@@_STL@@QAE@XZ")

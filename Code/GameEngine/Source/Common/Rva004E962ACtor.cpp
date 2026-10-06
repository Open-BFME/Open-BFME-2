// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004E962A@@QAE@XZ @0x004E962A 45B ctor map<int void*> at +0 plus 2x vector<BfmeE16> at +0xc +0x18 plus bool true at +0x24 callees map-int-ptr vector-e16 caller 0x002A9476
#include <map>
#include <vector>
struct BfmeE16 { float x, y, z, w; };
class Rva004E962A
{
public:
    _STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > m_map;
    _STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec1;
    _STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec2;
    bool m_24;
    Rva004E962A();
};

Rva004E962A::Rva004E962A() : m_24(true)
{
}

// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00438FA7@@QAE@XZ, 0x00438FA7, 30B. Target calls the rowed STLport list-base constructor and clears three following words; element size comes from the adjacent BfmePod196 list unit.
#include <list>
struct BfmePod196 { int a[49]; };
class Rva00438FA7
{
public:
    Rva00438FA7();
private:
    _STL::list<BfmePod196> m_items;
    int m_unknown04;
    int m_unknown08;
    int m_unknown0C;
};
Rva00438FA7::Rva00438FA7()
    : m_items(_STL::allocator<BfmePod196>())
{
    m_unknown04 = 0;
    m_unknown08 = 0;
    m_unknown0C = 0;
}

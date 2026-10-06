// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva004E9337@Rva004E9337@@QAEXXZ @0x004E9337 28B clear vector<void*> at +0 via rowed erase 0x0031BD55 then free buffer via rowed _free 0x00030830 callees 0x0031BD55 0x00030830 callers 0x002A8A18 0x002A9260
#include <vector>
extern "C" void __cdecl free(void *);
class Rva004E9337
{
public:
    _STL::vector<void *, _STL::allocator<void *> > m_vec;
    void rva004E9337();
};

void Rva004E9337::rva004E9337()
{
    m_vec.erase(m_vec.begin(), m_vec.end());
    void **b = m_vec.begin();
    if (b)
        free(b);
}

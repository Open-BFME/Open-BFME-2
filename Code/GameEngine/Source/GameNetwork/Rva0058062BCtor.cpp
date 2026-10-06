// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0058062B@@QAE@PAXI@Z @0x0058062B 27B.
// Ctor-like init: stores first arg at +0x00 then constructs vector<ushort> at +0x04
// with second arg via rowed 0x002339F3, returns this. Evidence: caller 0x00581171
// passes esi plus virtual result; ret 8 with this in eax.
#include <vector>

class Rva0058062B
{
public:
    Rva0058062B(void *a, unsigned int n);

private:
    void *m_00;
    _STL::vector<unsigned short> m_04;
};

Rva0058062B::Rva0058062B(void *a, unsigned int n) : m_00(a), m_04(n)
{
}

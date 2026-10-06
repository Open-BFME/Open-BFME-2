// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector<BfmePoolRef10> _M_clear at RVA 0x00569DFF calls _Destroy @0x00569A74 plus free.
class BfmePoolRef10 { public: ~BfmePoolRef10(); char m_pad[12]; };
#include <vector>
template void _STL::vector<BfmePoolRef10>::_M_clear();

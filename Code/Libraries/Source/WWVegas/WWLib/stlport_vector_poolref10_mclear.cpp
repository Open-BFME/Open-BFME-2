// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector<BfmePoolRef10> _M_clear at RVA 0x00569DFF calls _Destroy @0x00569A74 plus free.
struct BfmePoolHolder88;
class BfmePoolRef10 { BfmePoolHolder88 *m_target; public: ~BfmePoolRef10(); };
#include <vector>
namespace _STL { template <> void _Destroy<BfmePoolRef10 *>(BfmePoolRef10 *, BfmePoolRef10 *); }
template void _STL::vector<BfmePoolRef10>::_M_clear();

// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector<Rva000BEDF0Record> _M_clear at RVA 0x000C695D calls _Destroy @0x000C37E6 plus free.
struct Rva000BEDF0Record { public: ~Rva000BEDF0Record(); char m_pad[0x14]; };
#include <vector>
template void _STL::vector<Rva000BEDF0Record>::_M_clear();

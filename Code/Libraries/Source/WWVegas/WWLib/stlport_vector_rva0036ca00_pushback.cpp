// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?push_back@?$vector@VRva0036CA00Str@@V?$allocator@VRva0036CA00Str@@@_STL@@@_STL@@QAEXABVRva0036CA00Str@@@Z @0x0005A048 55B
// Evidence: chain lane calls just-landed _M_insert_overflow 0x00058ADE plus rowed _Construct 0x002393AA; caller 0x0005AC80; same 55B shape as Unicode push_back 0x0005CBE7 and Rva004E32F2 push_back 0x00566BB4.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

class Rva0036CA00Str
{
public:
    Rva0036CA00Str();
    Rva0036CA00Str(const Rva0036CA00Str &);
    ~Rva0036CA00Str();
    Rva0036CA00Str &operator=(const Rva0036CA00Str &);
private:
    void *m_data;
};

namespace _STL {
template <> void _Construct<Rva0036CA00Str, Rva0036CA00Str>(Rva0036CA00Str *, const Rva0036CA00Str &);
}

template void _STL::vector<Rva0036CA00Str, _STL::allocator<Rva0036CA00Str> >::push_back(const Rva0036CA00Str &);

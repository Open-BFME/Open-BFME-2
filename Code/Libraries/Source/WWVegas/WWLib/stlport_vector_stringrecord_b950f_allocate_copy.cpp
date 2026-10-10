// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 12-byte BfmeStringRecord000B950F vector allocation/copy helper at RVA 0xBC6FE.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

class AsciiString { public: AsciiString(const AsciiString &); __forceinline ~AsciiString(); protected: void releaseBuffer(); private: void *m_data; };
struct BfmeStringRecord000B950F {
    unsigned int word0;
    AsciiString text;
    unsigned int word1;
    BfmeStringRecord000B950F();
    BfmeStringRecord000B950F(const BfmeStringRecord000B950F &o) : word0(o.word0), text(o.text), word1(o.word1) {}
};
#include <memory>
template void _STL::_Construct<BfmeStringRecord000B950F,BfmeStringRecord000B950F>(BfmeStringRecord000B950F*,const BfmeStringRecord000B950F&);
#include <vector>
template class _STL::vector<BfmeStringRecord000B950F, _STL::allocator<BfmeStringRecord000B950F> >;

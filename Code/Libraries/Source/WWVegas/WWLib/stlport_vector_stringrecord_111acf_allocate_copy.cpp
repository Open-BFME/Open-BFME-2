// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 28-byte BfmeStringRecord00111ACF vector allocation/copy helper at RVA 0x101F5C.
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
#include <vector>
struct BfmeStringRecord00111ACF {
    AsciiString first;
    unsigned int word4;
    struct FloatStorage { float values[4]; } middle;
    AsciiString second;
    BfmeStringRecord00111ACF();
    BfmeStringRecord00111ACF(const BfmeStringRecord00111ACF &);
};
namespace _STL {
template <> void _Construct<BfmeStringRecord00111ACF, BfmeStringRecord00111ACF>(BfmeStringRecord00111ACF *, const BfmeStringRecord00111ACF &);
}
template class _STL::vector<BfmeStringRecord00111ACF, _STL::allocator<BfmeStringRecord00111ACF> >;

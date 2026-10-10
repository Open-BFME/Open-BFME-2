// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 12-byte BfmeContainerRecord002CF46E vector allocation/copy helper at RVA 0x2CFBF4.
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
class BfmeFixedStorage002CF0F0 { char m_bytes[4]; public: __declspec(nothrow) BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &); };
#include <vector>
struct BfmeContainerRecord002CF46E {
    BfmeFixedStorage002CF0F0 storage;
    AsciiString text;
    unsigned int word8;
    BfmeContainerRecord002CF46E();
    BfmeContainerRecord002CF46E(const BfmeContainerRecord002CF46E &);
};
namespace _STL {
template <> void _Construct<BfmeContainerRecord002CF46E, BfmeContainerRecord002CF46E>(BfmeContainerRecord002CF46E *, const BfmeContainerRecord002CF46E &);
}
template class _STL::vector<BfmeContainerRecord002CF46E, _STL::allocator<BfmeContainerRecord002CF46E> >;

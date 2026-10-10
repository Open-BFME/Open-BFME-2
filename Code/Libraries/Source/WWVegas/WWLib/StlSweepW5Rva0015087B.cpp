// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <memory>

struct Rva0015087BElement { unsigned words[2];Rva0015087BElement();Rva0015087BElement(const Rva0015087BElement&b){words[0]=b.words[0];words[1]=b.words[1];}bool operator<(const Rva0015087BElement&)const;bool operator==(const Rva0015087BElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva0015087BElement, _STL::allocator<Rva0015087BElement> >::_M_fill_insert(Rva0015087BElement *, unsigned int, Rva0015087BElement const &);

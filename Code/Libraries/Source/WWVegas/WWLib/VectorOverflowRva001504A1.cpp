// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference: pristine STLport4.5.3 vector::_M_insert_overflow.
// Retail 0x001504A1, 183B; Ghidra boundary, ret14 ABI and 76-byte
// arithmetic independently establish the overflow and storage width. The
// address-derived record is an opaque ABI view; no application class or
// member layout is inferred. Each helper pin comes from this target's calls.
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

struct Rva001504A1Record
{
public:
	Rva001504A1Record();
	Rva001504A1Record(const Rva001504A1Record&);
	~Rva001504A1Record();
	Rva001504A1Record&operator=(const Rva001504A1Record&);
	char bytes[76]; // +0x00
};
// Native calls at 0x001504F7 and 0x0015053A already name these rowed
// placement-copy and vector cleanup providers. Retain their opaque views.
struct Rva0014F647Element;
class Rva0014F8C6 { public: void rva0014F8C6(); };
namespace _STL {
template<> void _Construct<Rva0014F647Element,Rva0014F647Element>(Rva0014F647Element*,const Rva0014F647Element&);
template<> __declspec(dllimport) __forceinline void _Construct<Rva001504A1Record,Rva001504A1Record>(Rva001504A1Record*p,const Rva001504A1Record&v)
{ _Construct(reinterpret_cast<Rva0014F647Element*>(p),reinterpret_cast<const Rva0014F647Element&>(v)); }
template<> __declspec(dllimport) __forceinline void vector<Rva001504A1Record>::_M_clear()
{ ((Rva0014F8C6*)this)->rva0014F8C6(); }
}
template void _STL::vector<Rva001504A1Record>::_M_insert_overflow(Rva001504A1Record*,const Rva001504A1Record&,const _STL::__false_type&,unsigned int,bool);

// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport4.5.3 _vector.c is the source for native5EFC30..5EFD39 (265B).
// Native insertion and resize callers prove the counted handle array and
// three size words. The shared handle view retains count08/releases base04.
// The assignment ABI view is the existing4B Rva005EEFD2 owner at5EEFD2.
// Visible out-of-line wrappers preserve native dead-argument-slot reuse;
// declarations alone add locals, and inline wrappers add extra tag pushes.
// Both new typed wrappers are complete byte/relocation twins of the existing
// copy_backward5EF46B and fill5EF488 owners; they recover zero extra bytes.


#include "../../../../GameEngine/Source/Common/RegionIconSlotReferenceView.h"
class Rva005EEFD2 {public:Rva005EEFD2 &operator=(const Rva005EEFD2&);private:void *m_ptr;};
#include <vector>
namespace _STL {
template<class P,class D>P __copy_backward(P,P,P,const random_access_iterator_tag&,D*);

template<> __declspec(nothrow) void _Construct<Rva005EFD53Element,Rva005EFD53Element>(Rva005EFD53Element*,const Rva005EFD53Element&);
template<> __declspec(noinline) Rva005EFD53Element *__copy_backward_ptrs<Rva005EFD53Element*,Rva005EFD53Element*>(Rva005EFD53Element*a,Rva005EFD53Element*b,Rva005EFD53Element*c,const __false_type&) {return reinterpret_cast<Rva005EFD53Element*>(__copy_backward<Rva005EEFD2*,int>(reinterpret_cast<Rva005EEFD2*>(a),reinterpret_cast<Rva005EEFD2*>(b),reinterpret_cast<Rva005EEFD2*>(c),random_access_iterator_tag(),(int*)0));}
template<> __declspec(noinline) void fill<Rva005EFD53Element*,Rva005EFD53Element>(Rva005EFD53Element*a,Rva005EFD53Element*b,const Rva005EFD53Element&c){for(;a!=b;++a)*reinterpret_cast<Rva005EEFD2*>(a)=reinterpret_cast<const Rva005EEFD2&>(c);}
template<> __declspec(noinline) Rva005EFD53Element *uninitialized_fill_n<Rva005EFD53Element*,unsigned,Rva005EFD53Element>(Rva005EFD53Element*a,unsigned n,const Rva005EFD53Element&c){return __uninitialized_fill_n(a,n,c,__false_type());}
}
template void _STL::vector<Rva005EFD53Element>::_M_fill_insert(Rva005EFD53Element*,unsigned,const Rva005EFD53Element&);

// cl: /O1 /G7 /Oy- /EHsc- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport4.5.3 from the verified BFME1 pointer9cbfb551fe20dae985f91f2319d8997287b6a705.
// Native323B4F7EE9 mutates the12B vector header and copies4B owning-reference
// slots; native183B4F922C supplies that header in ECX and three range pointers.
// Copy/backward dispatches use the existing complete29B reference-tag and49B
// worker providers. The local4B view names no original application type.
// Visible noinline dispatch bodies preserve the compiler's knowledge that the
// empty tag is unused while retaining native out-of-line call boundaries.
#include <vector>
struct TargetRef00217D4C {virtual void *destroy(unsigned); int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva004F87BCElement {
 TargetRef00217D4C *m_ptr;
 Rva004F87BCElement(const Rva004F87BCElement &p):m_ptr(p.m_ptr) {if(m_ptr) ++m_ptr->references;}
 ~Rva004F87BCElement() {if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);}
 __declspec(noinline) Rva004F87BCElement &operator=(const Rva004F87BCElement &p) {
  if(this!=&p){if(p.m_ptr)++p.m_ptr->references;if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);m_ptr=p.m_ptr;}return *this;
 }
};
typedef _STL::vector<Rva004F87BCElement> UnitVector;
struct TreeHintRef00217D4C {void *m_ptr;};
namespace _STL {
template<class Input,class Output> Output __copy_ptrs(Input,Input,Output,const __false_type &);
template<> TreeHintRef00217D4C *__copy_ptrs<TreeHintRef00217D4C *,TreeHintRef00217D4C *>(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,const __false_type &);
template<> TreeHintRef00217D4C *__copy_backward<TreeHintRef00217D4C *,TreeHintRef00217D4C *,int>(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,const random_access_iterator_tag &,int *);
template<> __declspec(noinline) Rva004F87BCElement *copy<Rva004F87BCElement *,Rva004F87BCElement *>(Rva004F87BCElement *first,Rva004F87BCElement *last,Rva004F87BCElement *result)
{
 __false_type tag;
 typedef TreeHintRef00217D4C *(__cdecl *Dispatcher)(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,const __false_type &);
 Dispatcher dispatch=__copy_ptrs<TreeHintRef00217D4C *,TreeHintRef00217D4C *>;
 return reinterpret_cast<Rva004F87BCElement *>(dispatch(reinterpret_cast<TreeHintRef00217D4C *>(first),reinterpret_cast<TreeHintRef00217D4C *>(last),reinterpret_cast<TreeHintRef00217D4C *>(result),tag));
}
template<> __declspec(noinline) Rva004F87BCElement *__copy_backward_ptrs<Rva004F87BCElement *,Rva004F87BCElement *>(Rva004F87BCElement *first,Rva004F87BCElement *last,Rva004F87BCElement *result,const __false_type &)
{
 random_access_iterator_tag tag;
 return reinterpret_cast<Rva004F87BCElement *>(__copy_backward(reinterpret_cast<TreeHintRef00217D4C *>(first),reinterpret_cast<TreeHintRef00217D4C *>(last),reinterpret_cast<TreeHintRef00217D4C *>(result),tag,(int *)0));
}

template<> void UnitVector::_M_clear();
}
template void UnitVector::insert<Rva004F87BCElement *>(Rva004F87BCElement *,Rva004F87BCElement *,Rva004F87BCElement *);

template void UnitVector::_M_insert_dispatch<Rva004F87BCElement *>(Rva004F87BCElement *,Rva004F87BCElement *,Rva004F87BCElement *,const _STL::__false_type &);

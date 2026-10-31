// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Native copy 0x0014F480 and vtable 0x007D3854 establish an eight-byte
// polymorphic record with its index at +4 and virtual cleanup at slot zero.
// Preserve the existing placeholder spelling until the native type's views are unified.
// Full copy/algorithm/cleanup bodies are verified; this is not an original class declaration.
// cl: /O1 /arch:SSE /G7 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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


extern "C" const void* const __identifier("??_7SourceNamespace_AmbientLight@FXShaderParameterSourceNamespaceSAS@@6B@")[ ];
class __declspec(novtable) Rva0014F401 {
public:
  Rva0014F401(const Rva0014F401&);
  virtual ~Rva0014F401() {}
};
struct __declspec(novtable) Rva001506BFElement : Rva0014F401 {
  __declspec(noinline) Rva001506BFElement(const Rva001506BFElement& other):Rva0014F401(other) {
    *(const void**)this=__identifier("??_7SourceNamespace_AmbientLight@FXShaderParameterSourceNamespaceSAS@@6B@");
    index=other.index;
  }
  virtual ~Rva001506BFElement() {}
  int index;
};


namespace _STL { static __forceinline void _Construct(Rva001506BFElement* dest,const Rva001506BFElement& source){ if(dest) dest->Rva001506BFElement::Rva001506BFElement(source); } }
namespace _STL {
template<> __declspec(noinline) Rva001506BFElement* __copy_backward_ptrs<Rva001506BFElement*,Rva001506BFElement*>(Rva001506BFElement* first,Rva001506BFElement* last,Rva001506BFElement* result,const __false_type&) {
  return __copy_backward(first,last,result,random_access_iterator_tag(),(int*)0);
}
template<> __declspec(noinline) Rva001506BFElement* uninitialized_fill_n<Rva001506BFElement*,unsigned,Rva001506BFElement>(Rva001506BFElement* first,unsigned count,const Rva001506BFElement& value) {
  return __uninitialized_fill_n(first,count,value,__false_type());
}
}
// STLport 4.5.3 insertion, retaining the native finish value across the copy.
// The native base copy only writes the new element's vptr; it cannot modify
// this vector. Keep its existing out-of-line owner instead of emitting a duplicate.
template<> void _STL::vector<Rva001506BFElement,_STL::allocator<Rva001506BFElement> >::_M_fill_insert(iterator __position,size_type __n,const Rva001506BFElement& __x) {
  if (__n != 0) {
    if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
      const pointer __finish = this->_M_finish;
      Rva001506BFElement __x_copy = __x;
      const size_type __elems_after = __finish - __position;
      pointer __old_finish = this->_M_finish;
      if (__elems_after > __n) {
        __uninitialized_copy(this->_M_finish - __n, this->_M_finish, this->_M_finish, _IsPODType());
        this->_M_finish += __n;
        __copy_backward_ptrs(__position, __old_finish - __n, __old_finish, _TrivialAss());
        _STLP_STD::fill(__position, __position + __n, __x_copy);
      }
      else {
        uninitialized_fill_n(this->_M_finish, __n - __elems_after, __x_copy);
        this->_M_finish += __n - __elems_after;
        __uninitialized_copy(__position, __old_finish, this->_M_finish, _IsPODType());
        this->_M_finish += __elems_after;
        _STLP_STD::fill(__position, __old_finish, __x_copy);
      }
    }
    else 
      _M_insert_overflow(__position, __x, _IsPODType(), __n);
  }
}
// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva001506BFElement, _STL::allocator<Rva001506BFElement> >::_M_fill_insert(Rva001506BFElement *, unsigned int, Rva001506BFElement const &);

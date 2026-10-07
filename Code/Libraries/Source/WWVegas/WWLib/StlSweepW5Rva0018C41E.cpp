// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <stl/_algobase.h>
struct Rva0018C41EElement { char bytes[2]; bool operator<(const Rva0018C41EElement&)const; bool operator==(const Rva0018C41EElement&)const; };
namespace _STL { template <> struct __type_traits<Rva0018C41EElement> : __type_traits_aux<1> {}; }
#include <vector>

// Native 0x18C600..0x18C6D5 is the STLport fill-insert sibling of the
// rowed overflow below. Its stride, copy and fill loads are two bytes.
// A scalar word temporary retains retail's argument-slot reuse; the opaque
// element remains a trivial two-byte storage view. Every native callee,
// including fill_n at 0xAD8C9 and overflow at 0x18C41E, is already resolved.
namespace _STL {
template<> void vector<Rva0018C41EElement, allocator<Rva0018C41EElement> >::_M_fill_insert(
 Rva0018C41EElement *__position, unsigned int __n, const Rva0018C41EElement &__x)
{
 if (__n != 0) {
  if ((unsigned int)(_M_end_of_storage._M_data - _M_finish) >= __n) {
   unsigned short __x_copy = *(const unsigned short *)&__x;
   const unsigned int __elems_after = _M_finish - __position;
   Rva0018C41EElement *__old_finish = _M_finish;
   if (__elems_after > __n) {
    __uninitialized_copy(_M_finish - __n, _M_finish, _M_finish, __true_type());
    _M_finish += __n;
    __copy_backward_ptrs(__position, __old_finish - __n, __old_finish, __true_type());
    fill(__position, __position + __n, *(const Rva0018C41EElement *)&__x_copy);
   } else {
    uninitialized_fill_n(_M_finish, __n - __elems_after, *(const Rva0018C41EElement *)&__x_copy);
    _M_finish += __n - __elems_after;
    __uninitialized_copy(__position, __old_finish, _M_finish, __true_type());
    _M_finish += __elems_after;
    fill(__position, __old_finish, *(const Rva0018C41EElement *)&__x_copy);
   }
  } else _M_insert_overflow(__position, __x, __true_type(), __n);
 }
}
}
// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva0018C41EElement, _STL::allocator<Rva0018C41EElement> >::_M_insert_overflow(Rva0018C41EElement *, Rva0018C41EElement const &, _STL::__true_type const &, unsigned int, bool);

// Native 0x18C7E5..0x18C822 takes size and a word value, calls the local
// fill-insert sibling on growth, and uses the existing two-byte erase ABI
// on shrink. The original container and application element remain unknown.
struct Rva0018C7E5Vector : _STL::vector<Rva0018C41EElement, _STL::allocator<Rva0018C41EElement> > {
 void resize(unsigned int n, unsigned short x);
};
void Rva0018C7E5Vector::resize(unsigned int n, unsigned short x)
{
 if (n < size()) {
  typedef _STL::vector<unsigned short, _STL::allocator<unsigned short> > WordEraseView;
  ((WordEraseView *)this)->erase((unsigned short *)(begin()+n),(unsigned short *)end());
 }
 else _M_fill_insert(end(), n-size(), *(const Rva0018C41EElement *)&x);
}

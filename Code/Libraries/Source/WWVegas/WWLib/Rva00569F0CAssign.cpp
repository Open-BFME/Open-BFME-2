// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Adapted from BF1 f98983a7 inputs/vendor/stlport/stl/_vector.h:274.
// Native 00569F0C..00569FB3 RET12 proves three-word vector ABI and 20B stride.
// All five allocation/copy/cleanup callees already have verified providers.
// The existing neutral caller-view name is retained: original template spelling
// and the unused third argument type are not independently established.
// Record bytes are opaque here; constructor/string layout belongs to the exact
// BfmeStringRecord00568CE0 providers. Empty tag constructor has no state.
int rva00569450(void *,void *,void *);
struct BfmeStringRecord00568CE0 { char opaque[20]; };
namespace _STL {
struct __false_type {__false_type(){}};
template<class T> class allocator {};
template<class I> void _Destroy(I,I);
template<class I,class O> O __uninitialized_copy(I,I,O,const __false_type &);
template<class T,class A> class vector {
protected:
 template<class I> T *_M_allocate_and_copy(unsigned n,I first,I last);
 void _M_clear();
 T *_M_start,*_M_finish,*_M_end_of_storage;
};
}
struct Rva00569F0CVec : _STL::vector<BfmeStringRecord00568CE0,_STL::allocator<BfmeStringRecord00568CE0> > {
 void rva00569F0C(void *,void *,bool *);
};
void Rva00569F0CVec::rva00569F0C(void *a,void *b,bool *){
 const BfmeStringRecord00568CE0 *first=static_cast<const BfmeStringRecord00568CE0 *>(a),*last=static_cast<const BfmeStringRecord00568CE0 *>(b);
 unsigned len=last-first;
 if(len>static_cast<unsigned>(_M_end_of_storage-_M_start)){
  BfmeStringRecord00568CE0 *tmp=_M_allocate_and_copy(len,first,last);
  _M_clear();_M_start=tmp;_M_end_of_storage=tmp+len;_M_finish=_M_end_of_storage;
 }else if(static_cast<unsigned>(_M_finish-_M_start)>=len){
  BfmeStringRecord00568CE0 *end=reinterpret_cast<BfmeStringRecord00568CE0 *>(rva00569450(const_cast<BfmeStringRecord00568CE0 *>(first),const_cast<BfmeStringRecord00568CE0 *>(last),_M_start));
  _STL::_Destroy(end,_M_finish);_M_finish=end;
 }else{
  int bytes=(_M_finish-_M_start)*sizeof(BfmeStringRecord00568CE0);
  const BfmeStringRecord00568CE0 *mid=reinterpret_cast<const BfmeStringRecord00568CE0 *>(reinterpret_cast<const char *>(first)+bytes);
  rva00569450(const_cast<BfmeStringRecord00568CE0 *>(first),const_cast<BfmeStringRecord00568CE0 *>(mid),_M_start);
  _M_finish=_STL::__uninitialized_copy(mid,last,_M_finish,_STL::__false_type());
 }
}

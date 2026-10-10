// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP=
// Native 18C705..18C732 allocator45 and 18C73C..18C7E5 assign169.
// STLport4.5.3 vector::_M_allocate_and_copy/_M_assign_aux are semantic guides.
// Target proof: three pointer words; two-byte destination stride; input tree
// nodes projected by owned copy18C2E7 and counted/advanced by D20DB/5F4D8F.
// Original application element and container instantiation remain unknown.
// The native copy dispatch18C3C9 receives an unused fourth metadata argument
// (explicitly pushed by 18C705/18C73C and range forward18C533). Rehome that
// 29B dispatch here with the observed four-argument ABI; retire its old
// three-argument interface and the pointer-instantiated allocator interface.
// The distance specialization is the full byte-and-relocation twin of the
// established node-count owner; its application key meaning is not inferred.
// The target input is a four-byte tree-node cursor, not a pointer into the
// two-byte destination array. The original application element remains unknown.
struct Rva0018C2E7Node { int unknown; void *parent; void *left; void *right; short value; };
namespace _STL {struct __false_type;}
short *__cdecl Rva0018C3C9Copy(Rva0018C2E7Node *, Rva0018C2E7Node *, short *,const _STL::__false_type &);
struct Rva0018C533Input;
struct Rva0018C533Output;
Rva0018C533Output *__cdecl Rva0018C533RangeForward(Rva0018C533Input *, Rva0018C533Input *, Rva0018C533Output *);
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
 struct _Rb_tree_node_base;
 struct input_iterator_tag {}; struct __false_type {};
 struct forward_iterator_tag : input_iterator_tag {};
 template<class T> class allocator { public: T *allocate(unsigned int,const void *) const; };
 template<class I> int __distance(const I &,const I &,const input_iterator_tag &);
 template<class I,class D> void advance(I &,D);
}
// The existing generic tree cursor providers only advance/count the node
// token. Their application key interpretation is not used in this unit.
struct Rva005E59FCKeyIterator { _STL::_Rb_tree_node_base *node; };
namespace _STL {
template<class T> struct _Rb_global {static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);};
template<> __declspec(noinline) int __distance(const Rva005E59FCKeyIterator &first,const Rva005E59FCKeyIterator &last,const input_iterator_tag &) {
 int result=0;
 _Rb_tree_node_base *node=first.node;
 while(node!=last.node){node=_Rb_global<bool>::_M_increment(node);++result;}
 return result;
}
}
short *__cdecl Rva0018C2E7Copy(Rva0018C2E7Node*,Rva0018C2E7Node*,short*,void*,int);
__declspec(noinline) short *__cdecl Rva0018C3C9Copy(Rva0018C2E7Node *first,Rva0018C2E7Node *last,short *result,const _STL::__false_type &) {
 char category;
 return Rva0018C2E7Copy(first,last,result,&category,0);
}
static __forceinline short *copyTreeWords(Rva0018C2E7Node *first,Rva0018C2E7Node *last,short *result) {
 return Rva0018C3C9Copy(first,last,result,_STL::__false_type());
}
struct Rva0018C73CStorage : _STL::allocator<short> {short *data;};
class Rva0018C73CWordVector {
public:
 short *allocateCopy(unsigned int,Rva005E59FCKeyIterator,Rva005E59FCKeyIterator);
 void assign(Rva005E59FCKeyIterator,Rva005E59FCKeyIterator,const _STL::forward_iterator_tag&);
private:
 short *begin;
 short *end;
 Rva0018C73CStorage storage;
};
short *Rva0018C73CWordVector::allocateCopy(unsigned int n,Rva005E59FCKeyIterator first,Rva005E59FCKeyIterator last) {
 short *result=storage.allocate(n,0);
 Rva0018C3C9Copy((Rva0018C2E7Node*)first.node,(Rva0018C2E7Node*)last.node,result,_STL::__false_type());
 return result;
}
void Rva0018C73CWordVector::assign(Rva005E59FCKeyIterator first,Rva005E59FCKeyIterator last,const _STL::forward_iterator_tag &) {
 unsigned int len=_STL::__distance(first,last,_STL::input_iterator_tag());
 short *finish;
 if(len>(unsigned int)(storage.data-begin)) {
  short *fresh=allocateCopy(len,first,last);
  if(begin) Rva00030830GameFree(begin);
  begin=fresh;
  finish=begin+len;
  storage.data=finish;
 } else if((unsigned int)(end-begin)>=len) {
  finish=(short*)Rva0018C533RangeForward((Rva0018C533Input*)first.node,(Rva0018C533Input*)last.node,(Rva0018C533Output*)begin);
 } else {
  Rva005E59FCKeyIterator mid=first;
  _STL::advance(mid,(unsigned int)(end-begin));
  Rva0018C533RangeForward((Rva0018C533Input*)first.node,(Rva0018C533Input*)mid.node,(Rva0018C533Output*)begin);
  finish=copyTreeWords((Rva0018C2E7Node*)mid.node,(Rva0018C2E7Node*)last.node,end);
 }
 end=finish;
}

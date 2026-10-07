// Reference algorithm: STLport4.5.3 _M_fill_insert and __uninitialized_copy.
// Native265B body33A05E has12B ScienceType-vector elements; their copy ctor
// and complete uninitialized-copy loop are established in existing rows.
// Keep the copy template visible as in the reference: a declaration alone
// unnecessarily keeps the empty dispatch argument live and changes six stack
// operands. Empty tags have no state; the explicit empty constructor avoids
// emitting aggregate padding initialization which retail never performs.
// Reuses the existing typed fill/copy-backward/overflow providers, without
// new callee pins or new aliases. The IntVec helpers are existing folded
// providers for the same three-pointer vector representation; the overflow
// element is the existing opaque12B owner at339FA7, not a new type claim.
// cl: /EHs /MD /DNDEBUG
// Reference algorithm: STLport 4.5.3 _vector.c _M_fill_insert.
enum ScienceType { SCIENCE_INVALID = -1 };
struct Rva0033A23AElement { char words[12]; };
extern "C" void __cdecl free(void *);
namespace _STL {
template <class T> class allocator;
struct __false_type { __false_type() {} };
template <class T,class A> class vector {
 T *m_start,*m_finish,*m_end_of_storage;
public:
 vector(const vector&);
 ~vector() {if(m_start) ::free(m_start);}
 void _M_fill_insert(T *position,unsigned int n,const T& value);
protected:
 template<class U,class B> friend class vector;
 void _M_insert_overflow(T*,const T&,const __false_type&,unsigned int,bool);
};
template <class T1,class T2> void _Construct(T1 *,const T2 &);
template <class I,class O> O __uninitialized_copy(I first,I last,O result,const __false_type&) {
 O current=result;
 for(;first!=last;++first,++current) _Construct(current,*first);
 return current;
}
template <class F,class N,class T> F uninitialized_fill_n(F,N,const T&);
template <class F,class T> void fill(F,F,const T&);
template <class I,class O> O __copy_backward_ptrs(I,I,O,const __false_type&);
}
typedef _STL::vector<ScienceType,_STL::allocator<ScienceType> > SciVec;
typedef _STL::vector<int,_STL::allocator<int> > IntVec;
IntVec *__cdecl Rva00339D57Copy(IntVec*,IntVec*,IntVec*,void*);
inline IntVec *copy_backward_dispatch(IntVec* first,IntVec* last,IntVec* dest,const _STL::__false_type& tag) {return Rva00339D57Copy(first,last,dest,(void*)&tag);}
namespace _STL {
template <class T,class A>
void vector<T,A>::_M_fill_insert(T *position,unsigned int n,const T& value) {
 if(n!=0) {
  if((unsigned int)(m_end_of_storage-m_finish)>=n) {
   T value_copy=value;
   const unsigned int elems_after=m_finish-position;
   T *old_finish=m_finish;
   if(elems_after>n) {
    __uninitialized_copy(m_finish-n,m_finish,m_finish,__false_type());
    m_finish+=n;
    copy_backward_dispatch((IntVec*)position,(IntVec*)(old_finish-n),(IntVec*)old_finish,__false_type());
    fill((IntVec*)position,(IntVec*)(position+n),(const IntVec&)value_copy);
   } else {
    uninitialized_fill_n(m_finish,n-elems_after,value_copy);
    m_finish+=n-elems_after;
    __uninitialized_copy(position,old_finish,m_finish,__false_type());
    m_finish+=elems_after;
    fill((IntVec*)position,(IntVec*)old_finish,(const IntVec&)value_copy);
   }
  } else {
   ((vector<Rva0033A23AElement,allocator<Rva0033A23AElement> >*)this)->_M_insert_overflow((Rva0033A23AElement*)position,(const Rva0033A23AElement&)value,__false_type(),n,false);
  }
 }
}
}
typedef _STL::vector<SciVec,_STL::allocator<SciVec> > SciVecVec;
template void SciVecVec::_M_fill_insert(SciVec*,unsigned int,const SciVec&);

template SciVec *_STL::__uninitialized_copy(SciVec *,SciVec *,SciVec *,const _STL::__false_type &);

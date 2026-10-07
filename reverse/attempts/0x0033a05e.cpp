// ?_M_fill_insert@?$vector@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@V?$allocator@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@2@@_STL@@QAEXPAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@2@IABV32@@Z
// partial score=0.977 date=2026-10-07
// stlport
// cl: /O1 /G7 /EHs /MD /DNDEBUG
// Reference algorithm: STLport 4.5.3 _vector.c _M_fill_insert.
enum ScienceType { SCIENCE_INVALID = -1 };
struct Rva0033A23AElement { char words[12]; };
void __cdecl free(void *);
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
template <class I,class O> O __uninitialized_copy(I,I,O,const __false_type&);
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

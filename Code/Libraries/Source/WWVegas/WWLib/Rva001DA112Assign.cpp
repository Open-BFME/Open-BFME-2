// STLport 4.5.3 range-assign body at native 0x001DA112..0x001DA19E (140B, RET 12).
// Target evidence: three 8-byte-element vector paths (grow via _M_allocate_and_copy +
// _M_clear, in-place copy + destroy-tail, copy-prefix + uninitialized_copy tail) over the
// rowed providers 0x001D9C9F, 0x004C3D8B, 0x001D9BD3, 0x0032C0CA and 0x001D9B3C.
// The class and element names stay address-derived; the operation shape is the STLport
// _M_assign_aux reference. The named const __false_type local is load-bearing: the
// compiler's temporary slot for the tag is what retail keeps.
// cl: /I. /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport

struct Rva001DAAF2Element {char bytes[8];Rva001DAAF2Element(const Rva001DAAF2Element&);~Rva001DAAF2Element();};
struct FXBoneInfo {char bytes[8]; FXBoneInfo&operator=(const FXBoneInfo&);};
#include "../../../../GameEngine/Include/Common/RvaPair0032C0CA.h"
// _M_clear is retail's shared 8-byte clear worker 0x004C3D8B (ICF), rowed as
// vector<BfmeStringRecord00426A5B>::_M_clear; StlportVectorInsertOverflowFamily.cpp
// reaches it the same way.
struct BfmeStringRecord00426A5B;
void Rva0032C0CADestroyPairs(RvaPair0032C0CA*,RvaPair0032C0CA*);
class Rva001DA112;
namespace _STL {
struct __false_type {};
template<class T>class allocator {};
template<class T,class A=allocator<T> >class vector {
friend class ::Rva001DA112;protected:template<class I>T*_M_allocate_and_copy(unsigned,I,I);void _M_clear();};
template<class I,class O>O copy(I,I,O);
template<class I,class O>O __uninitialized_copy(I,I,O,const __false_type&);
}
class Rva001DA112 {public:void rva001DA112(int,int,char*);private:
 Rva001DAAF2Element*_M_start,*_M_finish,*end;
 unsigned capacity()const{return end-_M_start;}unsigned size()const{return _M_finish-_M_start;}
};
void Rva001DA112::rva001DA112(int firstArg,int lastArg,char*){
 Rva001DAAF2Element*first=(Rva001DAAF2Element*)firstArg;
 Rva001DAAF2Element*last=(Rva001DAAF2Element*)lastArg;
 const _STL::__false_type falseType;
 unsigned len=last-first;
 if(len>capacity()){
  Rva001DAAF2Element*tmp=((_STL::vector<Rva001DAAF2Element>*)this)->_M_allocate_and_copy(len,first,last);
  ((_STL::vector<BfmeStringRecord00426A5B>*)this)->_M_clear(); _M_start=tmp;_M_finish=tmp+len;end=tmp+len;
 }else if(size()>=len){
  Rva001DAAF2Element*finish=(Rva001DAAF2Element*)_STL::copy((FXBoneInfo*)first,(FXBoneInfo*)last,(FXBoneInfo*)_M_start);
  Rva0032C0CADestroyPairs((RvaPair0032C0CA*)finish,(RvaPair0032C0CA*)_M_finish);
  _M_finish=finish;
 }else{
  Rva001DAAF2Element*mid=first+size();
  _STL::copy((FXBoneInfo*)first,(FXBoneInfo*)mid,(FXBoneInfo*)_M_start);
  _M_finish=_STL::__uninitialized_copy(mid,last,_M_finish,falseType);
 }
}

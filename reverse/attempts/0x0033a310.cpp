// ?iniParseScienceVectorVector@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.88584 date=2026-10-08
// cl: /O1 /EHs /MD /DNDEBUG
extern "C" void __cdecl free(void *);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char*,const char*);
enum ScienceType {SCIENCE_INVALID=-1};
struct Rva0033A23AElement {char words[12];};
struct DynamicPortalLink;
class Rva00339E80 {public: DynamicPortalLink *rva00339E80(DynamicPortalLink*,DynamicPortalLink*);};
namespace _STL {
struct __false_type;
template<class T> class allocator {public:allocator() {}};
template<class T,class A> class _Vector_base {
protected:T *m_start,*m_finish,*m_end_of_storage;
public:_Vector_base(const A&);
};
template<class T,class A> class vector : protected _Vector_base<T,A> {
public:
 vector(const A&a=A()):_Vector_base<T,A>(a) {}
 vector(const vector&);
 ~vector(){if(this->m_start)::free(this->m_start);}
 void resize(unsigned int n,T value);
 __declspec(noinline) void resize(unsigned int n){resize(n,T());}
 void push_back(const T&);
 void _M_insert_overflow(T*,const T&,const __false_type&,unsigned int,bool);
 T *erase(T*,T*);
 T *begin(){return this->m_start;}
 T *end(){return this->m_finish;}
 bool empty(){return this->m_start==this->m_finish;}
 T&back(){return *(this->m_finish-1);}
 void clear(){erase(begin(),end());}
};
}
typedef _STL::vector<ScienceType,_STL::allocator<ScienceType> > SciVec;
typedef _STL::vector<SciVec,_STL::allocator<SciVec> > SciVecVec;
namespace _STL {
struct __false_type {__false_type() {}};
template<class T,class U> void _Construct(T*,const U&);
template<> void vector<Rva0033A23AElement,allocator<Rva0033A23AElement> >::_M_insert_overflow(Rva0033A23AElement*,const Rva0033A23AElement&,const __false_type&,unsigned int,bool);
template<> void vector<SciVec,allocator<SciVec> >::push_back(const SciVec&);
template<> inline SciVec *vector<SciVec,allocator<SciVec> >::erase(SciVec*first,SciVec*last) {
 return (SciVec*)((Rva00339E80*)this)->rva00339E80((DynamicPortalLink*)first,(DynamicPortalLink*)last);
}
}
class INI {
public:const char *getNextTokenOrNull(const char* separators=0);
 static ScienceType scanScience(const char*);
};
void iniParseScienceVectorVector(INI *ini,void*,void*store,const void*) {
 SciVecVec *asv=(SciVecVec*)store;
 asv->resize(1);
 SciVec *vec=&asv->back();
 for(const char*token=ini->getNextTokenOrNull();token;token=ini->getNextTokenOrNull()) {
  if(_strcmpi(token,"None")==0){vec->clear();break;}
  if(_strcmpi(token,"OR")==0){
   if(vec->empty())break;
   asv->push_back(SciVec());
   vec=&asv->back();
  } else vec->push_back(INI::scanScience(token));
 }
 if(vec->empty())asv->clear();
}

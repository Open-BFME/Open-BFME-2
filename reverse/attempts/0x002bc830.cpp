// ?Rva002BC830Append@@YAXAAV?$vector@URva002B72C9@@V?$allocator@URva002B72C9@@@_STL@@@_STL@@IABUICoord2DBase@@@Z
// partial score=0.96 date=2026-10-09
// stlport
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
void __cdecl free(void*);
struct ICoord2DBase {int x,y;};
struct ICoord2D:ICoord2DBase {__forceinline ICoord2D(){x=y=0;}bool operator==(const ICoord2DBase&)const;};
class ModuleData;
namespace _STL {
template<class T>class allocator{public:allocator(){}~allocator(){}};
template<class T,class A=allocator<T> >class _Vector_base{public:_Vector_base(const A&);T*start,*finish,*limit;};
template<class T,class A=allocator<T> >class vector;
template<>class vector<unsigned,allocator<unsigned> >{public:
 unsigned*start,*finish,*limit;
 __forceinline vector(const allocator<int>&a){((_Vector_base<int>*)this)->_Vector_base<int>::_Vector_base(a);}
 __forceinline ~vector(){if(start)free(start);}
};
template<>class vector<const ModuleData*,allocator<const ModuleData*> >{public:void push_back(const ModuleData*const&);};
}
struct Rva002B72C9:ICoord2D {
 _STL::vector<unsigned>values08;
 Rva002B72C9(const ICoord2DBase*,unsigned);
 __forceinline ~Rva002B72C9(){}
};
namespace _STL {template<>class vector<Rva002B72C9,allocator<Rva002B72C9> > {public:Rva002B72C9*start,*finish,*limit;void push_back(const Rva002B72C9&);__forceinline unsigned size()const{return finish-start;}__forceinline Rva002B72C9*begin(){return start;}};}
Rva002B72C9::Rva002B72C9(const ICoord2DBase*position,unsigned payload):values08(*(const _STL::allocator<int>*)((const char*)&position+3)){
 x=position->x;y=position->y;
 ((_STL::vector<const ModuleData*>*)&values08)->push_back(*(const ModuleData*const*)&payload);
}
void __cdecl Rva002BC830Append(_STL::vector<Rva002B72C9>&records,unsigned payload,const ICoord2DBase&position){
 unsigned count=records.size();Rva002B72C9*begin=records.begin();
 unsigned offset=0;
 for(unsigned i=0;i<count;++i,offset+=sizeof(Rva002B72C9)){
  if(((ICoord2D*)((unsigned)begin+offset))->operator==(position)){
   ((_STL::vector<const ModuleData*>*)&begin[i].values08)->push_back(*(const ModuleData*const*)&payload);
   return;
  }
 }
 Rva002B72C9 entry(&position,payload);
 records.push_back(entry);
}

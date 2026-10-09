// stlport
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// Native2B8ED2..2B8F27 RET8 builds the20B record copied by owned2B72C9.
// Target calls ICoord2D equality4CAD at prefix0 and its payload vector8
// uses the independently owned four-byte push4DFCB0. Original type/name
// remain unknown. The target loans byte+3 of the pointer argument home to
// the stateless allocator interface; vector-base211E58 does not read it.
// This read-only loan preserves the native frame and initializes the same
// three-pointer unsigned payload header. No alias pin is introduced.
// Coordinate-prefix inheritance is a structural view, not an original
// hierarchy claim. Existing copy source independently proves20B stride.
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

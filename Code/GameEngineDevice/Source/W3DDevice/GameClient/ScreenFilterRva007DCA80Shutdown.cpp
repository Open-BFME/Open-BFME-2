// cl: /DNDEBUG /MD
// Retail0x007DCAF0: vtable0x01128C5C slot1, matched Rva007DCA80 constructor.
struct ComObject;
struct ComVtable{char pad[8];unsigned (__stdcall *Release)(ComObject*);};
struct ComObject{ComVtable*v;};
struct Gen_p12pod{int words[3];};
namespace _STL{template<class T>class allocator{};template<class T,class A=allocator<T> >class vector{public:T*m_start;T*m_finish;T*m_end;};template<>class vector<Gen_p12pod,allocator<Gen_p12pod> >{public:Gen_p12pod*m_start;Gen_p12pod*m_finish;Gen_p12pod*m_end;Gen_p12pod*erase(Gen_p12pod*first,Gen_p12pod*last);Gen_p12pod*begin(){return m_start;}Gen_p12pod*end(){return m_finish;}void clear(){erase(begin(),end());}};}
class Rva007DCA80{public:virtual int init();virtual int shutdown();ComObject*shader[2];char pad[0x34-12];_STL::vector<Gen_p12pod> vec;ComObject*texture[3];ComObject*surface[3];};
int Rva007DCA80::shutdown(){
 if(shader[0])shader[0]->v->Release(shader[0]);if(shader[1])shader[1]->v->Release(shader[1]);shader[0]=0;shader[1]=0;
 vec.clear();
 if(surface[0])surface[0]->v->Release(surface[0]);surface[0]=0;
 if(texture[0])texture[0]->v->Release(texture[0]);texture[0]=0;
 if(surface[1])surface[1]->v->Release(surface[1]);surface[1]=0;
 if(texture[1])texture[1]->v->Release(texture[1]);texture[1]=0;
 return 1;
}


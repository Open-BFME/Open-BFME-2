// cl: /O1 /G7 /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}
struct Rva00240E18Node {char unknown[0x18];unsigned index18,index1c;};
namespace _STL {template<> void**vector<void*>::erase(void**,void**);}
class Rva00240E18 {public:void rva00240E18(bool);private:
 char unknown00[0x30];float scalar30,scalar34;char unknown38[8];unsigned value40;
 char unknown44[0x68];unsigned valueac;char unknownb0[0x18];
 _STL::vector<void*>groups[4];_STL::vector<void*>last;unsigned value104;char unknown108[4];unsigned value10c;
};
void Rva00240E18::rva00240E18(bool flag){
 value40=0;scalar30=64.0f;scalar34=64.0f;valueac=0;
 for(int i=0;i<4;++i){
  for(void**p=groups[i].begin();p!=groups[i].end();++p){
   Rva00240E18Node*node=(Rva00240E18Node*)*p;node->index1c=~0u;node->index18=~0u;
  }
  groups[i].clear();
 }
 for(void**p=last.begin();p!=last.end();++p){
  Rva00240E18Node*node=(Rva00240E18Node*)*p;node->index1c=~0u;node->index18=~0u;
 }
 last.clear();value104=0;if(!flag)value10c=1;
}

// Native240E18..240EBC RET4 plus WBcf1080 independently establish
// clear40/ac,64.0f at30/34, four pointer vectors c8..f8 then fifth f8,
// pointed-node index invalidation18/1c, clear104 and conditional10c flag.
// No original class or method name is inferred from nearby GameLogic rows.

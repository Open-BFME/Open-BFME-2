// ?rva001F8A38@Rva001F8A38@@QBEXAAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@PAX@Z
// partial score=0.925 date=2026-10-10
// stlport
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Native [1F8A38,1F8ACB). Four-byte polymorphic-source vector atC4/C8;
// invokes slot8 with the second argument, collects returned pointer words
// in a reserved temporary vector, then exchanges its three-word header with
// the first argument. Provider ModuleData element spelling is only an ABI view.
#include <vector>
class ModuleData;
class AsciiString;
namespace _STL {template<>void vector<AsciiString>::swap(vector<AsciiString>&);}
void __cdecl Rva00030830GameFree(void*);
namespace _STL {template<>inline _Vector_base<const ModuleData*,allocator<const ModuleData*> >::~_Vector_base() {if(_M_start)Rva00030830GameFree(_M_start);}}
namespace _STL {
template<>void vector<const ModuleData*>::reserve(unsigned);
template<>void vector<const ModuleData*>::push_back(const ModuleData*const&);
}
static __forceinline void reserveCollected(_STL::vector<const ModuleData*>&buffer,unsigned count){buffer.reserve(count);}
class Rva001F8A38Source {public:virtual void slot0();virtual void slot1();virtual const ModuleData *collect(void*);};
class Rva001F8A38 {public:void rva001F8A38(_STL::vector<const ModuleData*>&,void*) const;private:char prefix[0xc4];Rva001F8A38Source **begin,**end,**capacity;};
void Rva001F8A38::rva001F8A38(_STL::vector<const ModuleData*>&out,void*context) const{
 _STL::vector<const ModuleData*>temporary;
 reserveCollected(temporary,end-begin);
 for(Rva001F8A38Source **it=begin;it!=end;++it){
  const ModuleData*value=(*it)->collect(context);
  temporary.push_back(value);
 }
 reinterpret_cast<_STL::vector<AsciiString>&>(temporary).swap(reinterpret_cast<_STL::vector<AsciiString>&>(out));
}

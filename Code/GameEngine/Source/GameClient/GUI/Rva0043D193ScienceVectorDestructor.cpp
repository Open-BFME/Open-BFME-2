// cl: /O1 /Ob2 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native43D193..43D1C9/54B cleanup is called on screen43D1C9+288 at43D31B.
// Rowed clear43D3A8 and cost-add43D5CB independently establish a ScienceType
// vector at+8 and scalar at+14 in the24B prefix. Native free30830 consumes
// its storage; the complete17B game-pool provider verifies independently.
// Native final vptrBE2B78 names exactly three __purecall entries. The local
// base models that table without asserting original method names. Suppressing
// the derived table write through novtable reproduces the absence of an
// initial vptr store; an explicit base dtor preserves the native EH lifetime.
// Both owner names and the field at+4 remain unknown. No additional layout
// is inferred from the table shape. Native writes the base table after free.
#include <vector>
enum ScienceType { SCIENCE_INVALID=0 };
void Rva00030830FreeAllocation(void*);
namespace _STL {
// ?allocator<ScienceType>::deallocate present-unmatched
template<> inline void allocator<ScienceType>::deallocate(ScienceType*p,unsigned int)const {if(p)::Rva00030830FreeAllocation(p);}
}
class Rva0043D193Base {
public: virtual void f0()=0;virtual void f1()=0;virtual void f2()=0;
// ?Rva0043D193Base::~Rva0043D193Base present-unmatched
~Rva0043D193Base() {}
};
class __declspec(novtable) Rva0043D193:public Rva0043D193Base {
public: ~Rva0043D193();virtual void f0();virtual void f1();virtual void f2();
private: int unknown4;_STL::vector<ScienceType> sciences;int unknown14;
};
Rva0043D193::~Rva0043D193() {}
#pragma comment(linker,"/alternatename:?Rva00030830FreeAllocation@@YAXPAX@Z=_free")

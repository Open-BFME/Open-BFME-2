// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
// Native2B8AEA..2B8BFE276B: delayed-event module vectorCC and gateE8.
// Field4 is decremented via owned3FD1EB; slots4/5 process or advance,
// then collected pointer slots are removed by native80B2B5023. The
// latter binding uses N1's verified address-derived owner and entry
// spelling (read-only Rva002B5023Remove.cpp, findings16:03); its body
// remains N1's work. WBd899d0 is a structural, unnamed twin.
// STLport header ctor and GameMemory CPP free are established providers;
// specialize deallocation to the native game heap, rather than CRTfree.
// Inline counter getter gives MOV/TEST/SETAL; index before size and early
// return preserve XORzero plus distinct true/false unwind cleanup paths.
template<> _STL::_Vector_base<int,_STL::allocator<int> >::_Vector_base(const _STL::allocator<int>&);
void __cdecl Rva00030830FreeAllocation(void*);
template<> __forceinline void _STL::allocator<int>::deallocate(int*p,unsigned)const {if(p)Rva00030830FreeAllocation(p);}
class Glo012F1028Entry{public:virtual void*deleteInstance(int);virtual void s1();virtual void s2();virtual void s3();virtual bool process();virtual bool advance(bool);unsigned counter;__forceinline unsigned getRemaining()const{return counter;}};
class Rva003FD1EB{public:unsigned rva003FD1EB();};
class Rva002B5023Owner{public:void rva002B5023(Glo012F1028Entry*);};
class Rva002D3627Host;extern Rva002D3627Host*g_00DFEF18;
class LivingWorldManager;extern LivingWorldManager*TheLivingWorldManager;
class ManagerStateView{public:
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual bool ready();char pad[0x14-4];int mode;
};
struct WorldStateView{char pad[0x2C0];bool active;};
class ModuleData;
class Rva002B8AEA {public:void rva002B8AEA();char pad[0xCC];_STL::vector<Glo012F1028Entry*> entries;char padD8[16];bool locked;};
void Rva002B8AEA::rva002B8AEA(){
 _STL::vector<int> collected;
 ManagerStateView*state=(ManagerStateView*)g_00DFEF18;
 if(state->mode==1 && state->ready() && !((WorldStateView*)TheLivingWorldManager)->active && !locked){
  for(unsigned i=0;i<entries.size();++i){
   Glo012F1028Entry*entry=entries[i];
   if((entry->counter && !((Rva003FD1EB*)entry)->rva003FD1EB() && entry->process()) || entry->advance(entry->getRemaining()==0))
    ((_STL::vector<const ModuleData*>*)&collected)->push_back((const ModuleData*const&)entry);
  }
  unsigned i=0;unsigned count=collected.size();for(;i<count;++i)((Rva002B5023Owner*)this)->rva002B5023((Glo012F1028Entry*)collected[i]);
  return;
 }
}

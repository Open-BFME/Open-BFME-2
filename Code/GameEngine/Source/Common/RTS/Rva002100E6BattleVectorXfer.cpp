// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native2100E6..2101C6 (224B), thiscall RET8. Called twice from2101C6.
// Stock BF1 LivingWorldRegionManager transfer loops supply the version/load
// skeleton; native independently proves Snapshot slot30, unsigned count7C,
// pointer vector reservation/push and0x40 default Battle constructor3F6A3A.
// ModuleData is the existing byte-proved4-byte vector carrier instantiation;
// these values are LivingWorldBattle pointers, not ModuleData identities.
#include <vector>
class ModuleData;
struct XferVersion {unsigned char version,current;unsigned short padding;};
class Xfer {public:
 virtual void slot00();virtual bool isLoading();
 virtual void slot02();virtual void slot03();virtual void slot04();
 virtual void slot05();virtual void slot06();virtual void slot07();
 virtual void slot08();virtual void slot09();virtual void xferVersion(XferVersion*);
 virtual void slot0B();virtual void xferSnapshot(void*);
 virtual void slot0D();virtual void slot0E();virtual void slot0F();
 virtual void slot10();virtual void slot11();virtual void slot12();
 virtual void slot13();virtual void slot14();virtual void slot15();
 virtual void slot16();virtual void slot17();virtual void slot18();
 virtual void slot19();virtual void slot1A();virtual void slot1B();
 virtual void slot1C();virtual void slot1D();virtual void slot1E();
 virtual void xferUnsignedInt(unsigned int*);
};
class LivingWorldBattle {public:LivingWorldBattle();char opaque[64];};
namespace _STL {
 template<>void vector<const ModuleData*,allocator<const ModuleData*> >::reserve(unsigned int);
 template<>void vector<const ModuleData*,allocator<const ModuleData*> >::push_back(const ModuleData*const&);
}
class Rva0020EE29 {public:void rva002100E6(void*,void*);};
void Rva0020EE29::rva002100E6(void*arg,void*range){
 Xfer*xfer=(Xfer*)arg;
 _STL::vector<const ModuleData*>&battles=*(_STL::vector<const ModuleData*>*)range;
 XferVersion version;version.version=1;version.current=1;xfer->xferVersion(&version);
 if(xfer->isLoading()){
  int count;xfer->xferUnsignedInt((unsigned int*)&count);
  ((_STL::vector<void*>*)&battles)->erase(((_STL::vector<void*>*)&battles)->begin(),((_STL::vector<void*>*)&battles)->end());
  battles.reserve(count);
  for(int i=0;i<count;++i){
   const ModuleData*battle=(const ModuleData*)new LivingWorldBattle;
   xfer->xferSnapshot((void*)battle);battles.push_back(battle);
  }
 }else{
  int count=battles.size();xfer->xferUnsignedInt((unsigned int*)&count);
  for(int i=0;i<count;++i)xfer->xferSnapshot((void*)battles[i]);
 }
}

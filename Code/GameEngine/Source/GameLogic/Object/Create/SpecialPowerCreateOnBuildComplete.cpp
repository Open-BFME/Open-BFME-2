// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Target004B93EF..004B9428: Create-interface callback, gate slot3, clear
// the interface-local flag4, then scan Object244 modules and notify the
// interface returned by each module's C-subobject slot8 through its slot7.
// Twin: matched Object::rva0028AB4E uses the same loop at0028AB4E with
// different measured slots. SpecialPowerCreate identity is carried by the
// established SpecialPowerCreate ctor004B9345 installing secondary table
// 008596A4 at10; its slot1 points004B93EF. CreateModule.h provides the
// callback name; names of the queried interfaces remain
// unresolved. No Object or module layout beyond these accesses is inferred.
class SpecialPowerBuildResult {
public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();
 virtual void s4();virtual void s5();virtual void s6();virtual void s7();
};
class SpecialPowerModuleScanFace {
public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();
 virtual void s4();virtual void s5();virtual void s6();virtual void s7();
 virtual SpecialPowerBuildResult *s8();
};
struct SpecialPowerModuleScan { unsigned char prefix[0xC]; SpecialPowerModuleScanFace face; };
class Object {
public: unsigned char prefix[0x244]; SpecialPowerModuleScan **modules;
};
struct SpecialPowerCreateHead {virtual void anchor();unsigned char prefix[4];Object *object;unsigned char tail[4];};
class SpecialPowerCreateFace {
public:
 virtual void s0();virtual void onBuildComplete();virtual void s2();virtual bool shouldDoCreate();
 virtual void s4();virtual void s5();virtual void s6();virtual void s7();
 virtual void s8();virtual void s9();virtual void s10();virtual void s11();
 virtual void s12();
};
class SpecialPowerCreate : public SpecialPowerCreateHead, public SpecialPowerCreateFace {
public:virtual void onBuildComplete();bool flag;
};
void SpecialPowerCreate::onBuildComplete()
{
 if(shouldDoCreate()) {
  flag=false;
  for(SpecialPowerModuleScan **m=object->modules;*m;++m) {
   SpecialPowerBuildResult *r=(*m)->face.s8();
   if(r)r->s7();
  }
 }
}

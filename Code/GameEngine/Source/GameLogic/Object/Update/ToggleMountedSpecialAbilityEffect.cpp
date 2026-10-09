// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii
// Native 004ADF0B..004AE0AC (417B), slot17 of the mounted update.
// Identity: ModuleFactory24F68A registers ToggleMountedSpecialAbilityUpdate;
// ctor4ADAB5 installs the vtables and clears byte8C. WB12285C0 has the same
// base-trigger, template, kind, weapons, disguise and selected-drawable flow.
// Existing ToggleHidden/ToggleDeploy slot17 C++ supplies the base/owner view;
// the mounted extension and all offsets are established from retail, rather
// than inferred from the sibling source. No clean BF1/ZH mounted donor exists.
// Data CD is CancelDisguiseWhenDismounting; D0 is the one-word template name.
// Object model-condition words start10C; template-kind and condition214 are
// independently tested. Container slots42/69 and AI slot142 retain unknown
// names. Slot110 is the previously recovered isIdle interface. Cache the
// initial container only for the null/count tests; reload it for slot42,
// since the count virtual can replace it. This reproduces MOV ECX/TEST ECX.
// The function-local const name key reproduces the native EH state pair.
#include "ascii_string.h"
enum KindOfType { KIND_UNKNOWN=-1 };
enum WeaponSetType { WEAPON_UNKNOWN=0 };
enum NameKeyType { KEY_UNKNOWN=0 };
class Module;
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
template<int N> class MountedSlots : public MountedSlots<N-1> { public: virtual void gap(char(*)[N])=0; };
template<> class MountedSlots<0> {};
class MountedAIView : public MountedSlots<110> {
public: virtual bool isIdle() const=0;
virtual void a111()=0;
virtual void a112()=0;
virtual void a113()=0;
virtual void a114()=0;
virtual void a115()=0;
virtual void a116()=0;
virtual void a117()=0;
virtual void a118()=0;
virtual void a119()=0;
virtual void a120()=0;
virtual void a121()=0;
virtual void a122()=0;
virtual void a123()=0;
virtual void a124()=0;
virtual void a125()=0;
virtual void a126()=0;
virtual void a127()=0;
virtual void a128()=0;
virtual void a129()=0;
virtual void a130()=0;
virtual void a131()=0;
virtual void a132()=0;
virtual void a133()=0;
virtual void a134()=0;
virtual void a135()=0;
virtual void a136()=0;
virtual void a137()=0;
virtual void a138()=0;
virtual void a139()=0;
virtual void a140()=0;
virtual void a141()=0;
virtual void slot142(int)=0;
};
class MountedContainView {
public:
virtual void c0()=0;
virtual void c1()=0;
virtual void c2()=0;
virtual void c3()=0;
virtual void c4()=0;
virtual void c5()=0;
virtual void c6()=0;
virtual void c7()=0;
virtual void c8()=0;
virtual void c9()=0;
virtual void c10()=0;
virtual void c11()=0;
virtual void c12()=0;
virtual void c13()=0;
virtual void c14()=0;
virtual void c15()=0;
virtual void c16()=0;
virtual void c17()=0;
virtual void c18()=0;
virtual void c19()=0;
virtual void c20()=0;
virtual void c21()=0;
virtual void c22()=0;
virtual void c23()=0;
virtual void c24()=0;
virtual void c25()=0;
virtual void c26()=0;
virtual void c27()=0;
virtual void c28()=0;
virtual void c29()=0;
virtual void c30()=0;
virtual void c31()=0;
virtual void c32()=0;
virtual void c33()=0;
virtual void c34()=0;
virtual void c35()=0;
virtual void c36()=0;
virtual void c37()=0;
virtual void c38()=0;
virtual void c39()=0;
virtual void c40()=0;
virtual void c41()=0;
virtual void slot42(int)=0;
virtual void c43()=0;
virtual void c44()=0;
virtual void c45()=0;
virtual void c46()=0;
virtual void c47()=0;
virtual void c48()=0;
virtual void c49()=0;
virtual void c50()=0;
virtual void c51()=0;
virtual void c52()=0;
virtual void c53()=0;
virtual void c54()=0;
virtual void c55()=0;
virtual void c56()=0;
virtual void c57()=0;
virtual void c58()=0;
virtual void c59()=0;
virtual void c60()=0;
virtual void c61()=0;
virtual void c62()=0;
virtual void c63()=0;
virtual void c64()=0;
virtual void c65()=0;
virtual void c66()=0;
virtual void c67()=0;
virtual void c68()=0;
virtual unsigned slot69(int) const=0;
};
class Drawable { public: char pad[0x43C]; bool selected; };
class ControlBar { public: char pad[0x28]; bool dirty; };
extern ControlBar *TheControlBar;
class SpecialDisguiseUpdate { public: void rva004B05F5(bool); };
struct MountedFlags {
 unsigned words[19];
 __forceinline unsigned test(unsigned bit) const { return words[bit>>5] & (1U<<(bit&31)); }
 __forceinline void clear(unsigned bit) { words[bit>>5]&=~(1U<<(bit&31)); }
 __forceinline void set(unsigned bit) { words[bit>>5]|=(1U<<(bit&31)); }
};
class Object {
public:
 bool isKindOf(KindOfType) const;
 void rva0028AE6D();
 void clearWeaponSetFlag(WeaponSetType);
 void setWeaponSetFlag(WeaponSetType);
 void rva0028B79C(int);
 void rva0028B78A(int);
 Module *findModule(NameKeyType) const;
 Drawable *getDrawable() const;
 __forceinline void clearCondition214(){ if(flags.test(214)){flags.clear(214);rva0028AE6D();} }
 __forceinline void setCondition214(){ if(!flags.test(214)){flags.set(214);rva0028AE6D();} }
 char pad0[0x10C]; MountedFlags flags;
 char pad158[0x250-0x158]; MountedContainView *contain; void *body; MountedAIView *ai;
};
struct MountedDataView { char pad0[0xCD]; bool cancelDisguise; char padCE[2]; StringBase<char> mountedTemplate; };
class SpecialAbilityUpdate : public MountedSlots<17> {
public:
 virtual void triggerAbilityEffect();
 const MountedDataView *data; Object *owner; char padC[0x24-0xC]; int state;
 char pad28[0x8C-0x28]; bool flag8C;
};
class ToggleMountedSpecialAbilityUpdate : public SpecialAbilityUpdate {
public:
 virtual void triggerAbilityEffect();
 void createMountedTemplate();
};
void ToggleMountedSpecialAbilityUpdate::triggerAbilityEffect()
{
 SpecialAbilityUpdate::triggerAbilityEffect();
 Object *obj=owner;
 MountedAIView *ai=obj->ai;
 flag8C=false;
 if(!ai->isIdle()) return;
 const MountedDataView *d=data;
 if(state!=1) return;
 if(!d->mountedTemplate.isEmpty()) createMountedTemplate();
 else if(obj->isKindOf((KindOfType)214)) {
  MountedContainView *contain=obj->contain;
  if(contain && contain->slot69(0)>0) obj->contain->slot42(0);
  obj->clearCondition214();
  obj->ai->slot142(0);
  obj->clearWeaponSetFlag((WeaponSetType)21);
  obj->rva0028B79C(6);
  if(d->cancelDisguise && obj->isKindOf((KindOfType)300)) {
   static const NameKeyType key=TheNameKeyGenerator->nameToKey("SpecialDisguiseUpdate");
   SpecialDisguiseUpdate *disguise=(SpecialDisguiseUpdate*)obj->findModule(key);
   if(disguise) disguise->rva004B05F5(true);
  }
 } else {
  obj->setCondition214();
  obj->ai->slot142(7);
  obj->setWeaponSetFlag((WeaponSetType)21);
  obj->rva0028B78A(6);
 }
 Drawable *drawable=obj->getDrawable();
 if(drawable && drawable->selected) TheControlBar->dirty=true;
}

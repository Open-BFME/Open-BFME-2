// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common /Ireference/shims/moduledata
// stlport
// HordeMeleeAmoeba slot 3, native 00588ABB..00588B8A (207B, RET4).
// WB 01470F20 paired by the ctor's vtable; the class name is independently
// owned by 00587D9C. BFME1 Xfer/version conventions guide the transfer;
// the 60B record, version bytes, field offsets and chained calls are target facts.
#include <vector>
#include "Coord3DBase.h"
#include "Common/Snapshot.h"
class Object;
struct BfmePod60 {
 BfmePod60();
 Coord3DBase position;
 bool needsPosition;char opaque0d[3];int index;
 int values[8];int opaque34;unsigned char opaque38;bool loaded39;char opaque3a[2];
};
namespace _STL {template<> void vector<BfmePod60>::resize(size_type);}
struct HmaTransferVersion {unsigned char minimum,current; HmaTransferVersion(unsigned char c,unsigned char m):minimum(m),current(c) {}};
class HmaTransferView {
public:
 virtual void s0();
 virtual bool isLoading();
 virtual void s2();
 virtual bool isCRC();
 virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();
 virtual HmaTransferView &version(HmaTransferVersion &);
 virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();virtual void s20();virtual void s21();virtual void s22();virtual void s23();
 virtual HmaTransferView &position(Coord3DBase &);
 virtual void s25();virtual void s26();virtual void s27();virtual void s28();virtual void s29();
 virtual HmaTransferView &count(unsigned &);
 virtual HmaTransferView &integer(int &);virtual void s32();virtual void s33();virtual void s34();virtual void s35();
 virtual HmaTransferView &boolean(bool &);
};
class Rva0058731DHost;
Rva0058731DHost *Rva0058731DCheck(Rva0058731DHost*,int);
class Rva005D6FCC : public Snapshot {public:virtual ~Rva005D6FCC();void *held;};
class HordeMeleeAmoeba : public Rva005D6FCC {
public:
 virtual void xfer(Xfer *);
 bool rva005879C8(Object*);
 _STL::vector<BfmePod60> slots;
 bool flag14;void *other;
};
void HordeMeleeAmoeba::xfer(Xfer *xfer)
{
 HmaTransferView *view=(HmaTransferView*)xfer;
 if(view->isCRC())return;
 HmaTransferVersion version(3,1);
 view->version(version);
 if(version.current<2)return;
 view->boolean(flag14);
 unsigned count=slots.size();
 view->count(count);
 slots.resize(count);
 for(BfmePod60 *slot=slots.begin();slot!=slots.end();++slot) {
  HmaTransferView &hmaTransferView=view->position(slot->position);
  HmaTransferView &transferStream=((HmaTransferView*)&hmaTransferView)->boolean(slot->needsPosition);
  Rva0058731DCheck((Rva0058731DHost*)&((HmaTransferView*)&transferStream)->integer(slot->index),(int)slot->values);
  if(version.current>2)view->boolean(slot->loaded39);
  else if(view->isLoading())slot->loaded39=true;
 }
}

#include <list>
#include <math.h>
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
enum WeaponSlotType { HmaWeaponSlotInvalid=-1 };
enum ObjectStatusTypes { HmaStatus26=0x26 };
class Rva002C9400ByteField {public: unsigned char get()const;};
class Weapon {public:
 const Rva002C9400ByteField *getTemplate()const{return data;}
 float getAttackRange(const Object*)const;
 void *vptr;const Rva002C9400ByteField *data;
};
class AIUpdateInterface {public:Object *getCurrentVictim()const;};
class Rva001E3591 {public:bool rva001E3591();};
template<int N> class HmaVirtualSlots:public HmaVirtualSlots<N-1>{public:virtual void gap(char(*)[N]);};
template<> class HmaVirtualSlots<0>{};
class HmaUnitAIView:public HmaVirtualSlots<111>{public:
 virtual bool engaged();
 char opaque04[0x140-4];Rva001E3591 *path;
};
struct HmaObjectTemplate {char opaque[0x108];unsigned char kinds108;};
class Object {public:
 const Weapon *getCurrentWeapon(WeaponSlotType*)const;
 float rva00263763(const void*)const;
 bool testStatus(ObjectStatusTypes)const;
 void *vptr;HmaObjectTemplate *data;char opaque08[0x38-8];Coord3DBase position;
 char opaque44[0x78-0x44];ObjectID id78;
 char opaque7c[0x258-0x7c];HmaUnitAIView *ai;
 char opaque25c[0x274-0x25c];Object *related;
};
struct HmaHolder {char opaque[8];Object *owner;};
struct Rva0046247DPair {void *first;_STL::list<Object*> *second;};
class Rva00587204 {public:Rva0046247DPair &rva00587204(Rva0046247DPair&);};
class HmaDelegateView:public HmaVirtualSlots<89>{public:virtual void select(Object*);};
bool HordeMeleeAmoeba::rva005879C8(Object *victim)
{
 if(!victim)return false;
 Object *owner=((HmaHolder*)held)->owner;
 const Weapon *weapon=owner->getCurrentWeapon(0);
 if(!weapon || !weapon->getTemplate()->get())return false;
 float range=weapon->getAttackRange(owner);
 if(!(victim->data->kinds108&0x80) && fabs(owner->position.z-victim->position.z)>20.0f)return false;
 range=range-(-10.0f);
 if(range<0.1f)range=0.1f;
 bool near=victim->rva00263763(owner)<range*range;
 Object *related=victim->related;
 if(!related && victim->testStatus(HmaStatus26))related=TheGameLogic->findObjectByID(victim->id78);
 Rva0046247DPair pair;
 ((Rva00587204*)this)->rva00587204(pair);
 bool found=false;
 // Compare the public node identities directly, preserving the inlined walk
 // without emitting this TU's non-retail iterator-comparison COMDAT.
 for(_STL::list<Object*>::iterator i=pair.second->begin();i._M_node!=pair.second->end()._M_node;++i) {
  HmaUnitAIView *unit=(*i)->ai;
  if(!unit)continue;
  if(unit->engaged()) {
   if(near){found=true;break;}
   Object *current=((AIUpdateInterface*)unit)->getCurrentVictim();
   if(!current)continue;
   if(current==victim || current->related==victim){found=true;break;}
   if(related) {
    Object *currentRelated=current->related;
    if(!currentRelated && current->testStatus(HmaStatus26)) {
     currentRelated=TheGameLogic->findObjectByID(current->id78);
     if(currentRelated==related){found=true;break;}
    }
    if(currentRelated==related){found=true;break;}
   }
  } else if(near) {
   if(unit->path && unit->path->rva001E3591())return false;
   found=true;break;
  }
 }
 if(found) {
  ((HmaDelegateView*)((char*)held+0x11c))->select(victim);
  return true;
 }
 return false;
}

// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
class FreelistPool;
extern FreelistPool g_freelistPool00DB8FEC;
// stlport
// ?rva00473212@HordeContain@@UAEPAVObject@@PAV2@PBV2@_N@Z, retail 0x00473212
// (1415 B, EH, RET 0xC), directly after the banner transfer 0x00473197.
// It combines the contained member lists of two hordes, resolves the
// replacement template, creates the combined horde, merges the upgrade masks
// and hands the surviving banner carrier (higher veterancy wins) to it.
// Original method spelling unknown. BF1 f98983a7d AddMemberSyncXP guides the
// banner/XP helper; native code and WorldBuilder independently establish the
// HordeContain primary and +0x11C secondary receivers. LatchRestore<bool> is
// the Zero Hour guard (native vftable BC5314, slot 0 the owned 0x00051A46
// destructor). Scoring is switched off around the carrier transfer and the
// destruction of the merged hordes through Zero Hour's isScoringEnabled /
// enableScoring byte at GameLogic +0x98.
// Codegen notes: the veterancy comparison goes through the inline
// getExperienceTracker()/getVeterancyLevel() accessors (direct field reads
// put the first carrier in EAX and keep the GameLogic load in the arms); the
// member list lives at function scope; a failed containment returns null
// after destroying the new object; pool-list disposal cannot throw.
#include "ascii_string.h"
#include <list>
#include <algorithm>
#include <string.h>
#include "Common/LatchRestore.h"
class Object;
// Keep typed node comparisons local and bind the out-of-line node factory
// to retail's pooled list implementation at 0x001EB9AC.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
class HordeContain;
class ThingTemplate;
class Team;
class Matrix3D;
enum ObjectStatusTypes 
{
 STATUS_NONE = 0 
}
;
enum CommandSourceType 
{
 CMD_FROM_PLAYER=0, CMD_FROM_AI=2 
}
;
#include "../../../../Include/Common/BfmeFixedStorage128.h"
namespace _STL 
{
 template<unsigned N> struct _Base_bitset;
 template<> struct _Base_bitset<32> 
 {
  void _M_do_or(const _Base_bitset<32>&);
  unsigned long words[32];
  
 }
 ;
 
}
#include "../../../../Include/GameLogic/ExperienceTracker.h"
#include "../../../Common/Thing/thing.h"
template<int N> class Slots : public Slots<N-1> 
{
 public: virtual void gap(char (*)[N]) = 0;
 
}
;
template<> class Slots<1> 
{
 public: virtual void gap(char (*)[1]) = 0;
 
}
;
class ModuleSlot15 : public Slots<15> 
{
 public: virtual void clear();
 
}
;
class ContainsView : public Slots<31> 
{
 public: virtual class ContainResult *result();
 
}
;
class ContainResult : public Slots<134> 
{
 public: virtual HordeContain *horde();
 
}
;
class AICommandInterface 
{
 public: void rva0045003E(int,CommandSourceType);
 
}
;
class AIView 
{
 public:
 char pad[0x20];
 AICommandInterface commands;
 
}
;
class ThingTemplate 
{
 public:
 char pad[0x64];
 AsciiString name;
 char pad68[0x115-0x68];
 unsigned char kind115;
 
}
;
class Object 
{
 public:
 void *rva0028C197() const;
 void *rva0028BC58(int);
 void rva0028BAAE(int);
 bool testStatus(ObjectStatusTypes) const;
 void setStatus(ObjectStatusTypes,bool);
 char pad0[4];
 ThingTemplate *type;
 char pad8[0x250-8];
 ContainsView *contain;
 char pad254[4];
 AIView *ai;
 char pad25C[8];
 ExperienceTracker *tracker;
 ExperienceTracker *getExperienceTracker() const { return tracker; }
 char pad268[0x274-0x268];
 Object *parent;
 char pad278[0x284-0x278];
 BfmeFixedStorage128 upgrades;
 Team *team;
 char pad308[0x45C-0x308];
 int value45C;
 const Matrix3D *transform() const 
 {
  return (const Matrix3D *)((const char *)this+8);
  
 }
 ContainsView *getContain() const 
 {
  return contain;
  
 }
 Team *getTeam() const 
 {
  return team;
  
 }
 Object *getParent() const 
 {
  return parent;
  
 }
 bool isHorde() const 
 {
  return (type->kind115 & 0x20)!=0;
  
 }
 
}
;
#include "../../../Common/GameLogicObjectLookupView.h"
// The scoring byte at +0x98 (Zero Hour's m_isScoringEnabled) is private in
// the shared view; Zero Hour's enableScoring writes it.
struct HordeScoringView 
{
 char pad[0x98];
 bool scoringEnabled;
 
}
;
extern GameLogic *TheGameLogic;
struct CreateMask 
{
 unsigned long words[4];
 
}
;
enum ObjectID; class ThingFactory
{
 public: const ThingTemplate *findTemplate(const AsciiString &);
 Object *newObject(const ThingTemplate *,Team *,const CreateMask *,ObjectID);
 
}
;
extern ThingFactory *TheThingFactory;
class Rva002D06CA 
{
 public: void *rva002D06CA(const AsciiString *);
 
}
;
#include "../../../../Include/GameLogic/AIPathfind.h"
class AI 
{
 public: char pad[0x10];
 Pathfinder *pathfinder;
 
}
;
extern AI *TheAI;
struct Rva0046D158Record 
{
 AsciiString from, replacement;
 
}
;
struct ModuleData 
{
 char pad[0x1F4];
 char ordinaryNames[0x24];
 char bannerNames[0x20];
 bool matchNamed;
 char pad239[3];
 AsciiString name;
 
}
;
#include "../../../../Include/Common/FreelistProxyHead.h"
#include "../../../../Include/Common/FreelistPool.h"
extern FreelistPool g_freelistPool00DB8FEC;
namespace _STL {
// The rowed Object-pointer factory uses this dedicated 12-byte-node pool.
template <> inline __declspec(noinline)
_List_node<Object *> *list<Object *, allocator<Object *> >::_M_create_node(Object *const &value)
{
    _List_node<Object *> *node = (_List_node<Object *> *)g_freelistPool00DB8FEC.pop();
    Object **valuePtr = (Object **)((char *)node + 8);
    if (valuePtr)
        *valuePtr = value;
    return node;
}
}

#include "../../../../Include/Common/Rva001EB984Member.h"
// Byte copy of the rowed 0x001EB984 init, visible so cl sees that the
// allocator temporary's address is not kept.
__declspec(noinline) inline void *Rva001EB984Member::init(void *context)
{
 (void)context;
 char dummyAlloc;
 ((FreelistProxyHead *)this)->setup(&dummyAlloc,0);
 void *node=g_freelistPool00DB8FEC.pop();
 ((void **)node)[0]=node;
 ((void **)node)[1]=node;
 m_head=node;
 return this;
}
#include "../../../../Include/Common/Rva001EB769.h"
typedef _STL::list<Object*>::iterator ObjectIterator;
// The native caller inlines the vendored erase body. Keep its allocator
// operation and return iterator, with a TU-local inline specialization.
namespace _STL 
{
 template<> __declspec(dllimport) __forceinline ObjectIterator list<Object*>::erase(ObjectIterator position)
 
 {
  _List_node_base *next=position._M_node->_M_next;
  _List_node_base *prev=position._M_node->_M_prev;
  _Node *node=(_Node*)position._M_node;
  prev->_M_next=next;
  next->_M_prev=prev;
  _Destroy(&node->_M_data);
  *(void**)node=(*(void **)((char *)&::g_freelistPool00DB8FEC + 8));
  (*(void **)((char *)&::g_freelistPool00DB8FEC + 8))=node;
  return ObjectIterator((_Node*)next);
  
 }
 
}
class ObjectList 
{
 public:
 ObjectList() 
 {
  char alloc;
  reinterpret_cast<Rva001EB984Member*>(this)->init(&alloc);
  
 }
 ~ObjectList() throw()
 {
  reinterpret_cast<Rva001EB769*>(this)->rva001EB769();
  
 }
 _STL::_List_node_base *head;
 ObjectIterator begin() 
 {
  return ObjectIterator((_STL::_List_node<Object*>*)head->_M_next);
  
 }
 ObjectIterator end() 
 {
  return ObjectIterator((_STL::_List_node<Object*>*)head);
  
 }
 Object *front() 
 {
  return (Object*)(( _STL::_List_node<Object*>*)head->_M_next)->_M_data;
  
 }
 Object *back() 
 {
  return (Object*)(( _STL::_List_node<Object*>*)head->_M_prev)->_M_data;
  
 }
 bool empty() 
 {
  return head->_M_next==head;
  
 }
 void append(Object *&object) 
 {
  _STL::list<Object*> *view = reinterpret_cast<_STL::list<Object*>*>(this);
  view->insert(view->end(),object);
  
 }
 
}
;
class HordePrimary : public Slots<33> 
{
 public:
 virtual void reset(bool);
 char pad4[4];
 Object *owner;
 char padC[0x11C-0xC];
 ModuleData *data() const 
 {
  return *(ModuleData **)((char*)this+4);
  
 }
 
}
;
struct HordeMemberSlot 
{
 int id;
 const int &value() const 
 {
  return id;
  
 }
 int *storage() 
 {
  return &id;
  
 }
 
}
;
class HordeInterface : public Slots<17> 
{
 public:
 virtual void collect(ObjectList &);
 virtual void gap18();
 virtual void gap19();
 virtual void gap20();
 virtual void gap21();
 virtual void gap22();
 virtual void gap23();
 virtual void gap24();
 virtual void gap25();
 virtual void gap26();
 virtual bool accepts(Object *,int,const void *,bool);
 virtual void gap28();
 virtual Object *rva00473212(Object *,const Object *,bool);
 virtual void replaceMembers(ObjectList &);
 virtual void gap31();
 virtual void gap32();
 virtual void gap33();
 virtual void gap34();
 virtual void gap35();
 virtual void gap36();
 virtual void gap37();
 virtual void gap38();
 virtual void gap39();
 virtual void gap40();
 virtual void gap41();
 virtual void gap42();
 virtual void gap43();
 virtual void gap44();
 virtual void gap45();
 virtual void gap46();
 virtual void gap47();
 virtual void gap48();
 virtual void gap49();
 virtual void gap50();
 virtual void gap51();
 virtual void gap52();
 virtual void gap53();
 virtual void gap54();
 virtual void gap55();
 virtual void gap56();
 virtual void gap57();
 virtual void gap58();
 virtual void gap59();
 virtual void gap60();
 virtual void gap61();
 virtual void gap62();
 virtual void gap63();
 virtual void gap64();
 virtual void gap65();
 virtual void gap66();
 virtual void gap67();
 virtual void gap68();
 virtual void gap69();
 virtual void gap70();
 virtual void gap71();
 virtual void gap72();
 virtual void gap73();
 virtual void gap74();
 virtual void gap75();
 virtual void gap76();
 virtual void gap77();
 virtual void gap78();
 virtual void gap79();
 virtual void gap80();
 virtual void gap81();
 virtual void gap82();
 virtual void gap83();
 virtual void gap84();
 virtual void gap85();
 virtual void gap86();
 virtual void gap87();
 virtual void gap88();
 virtual void gap89();
 virtual void gap90();
 virtual void gap91();
 virtual void gap92();
 virtual void gap93();
 virtual void gap94();
 virtual void gap95();
 virtual void gap96();
 virtual void gap97();
 virtual void gap98();
 virtual void gap99();
 virtual void gap100();
 virtual void gap101();
 virtual void gap102();
 virtual void gap103();
 virtual void gap104();
 virtual void gap105();
 virtual void gap106();
 virtual void gap107();
 virtual void gap108();
 virtual void gap109();
 virtual void gap110();
 virtual void gap111();
 virtual void gap112();
 virtual void gap113();
 virtual void gap114();
 virtual void gap115();
 virtual void gap116();
 virtual void gap117();
 virtual void gap118();
 virtual void gap119();
 virtual void gap120();
 virtual void gap121();
 virtual void refresh();
 char pad4[1];
 bool transferring;
 char pad6[0x7C-6];
 bool flag7C;
 char pad7D[0x148-0x7D];
 HordeMemberSlot ordinary;
 int ordinaryIndex,carrierID;
 char pad154[0x198-0x154];
 bool suppress;
 
}
;
class UpgradeView : public Slots<93> 
{
 public: virtual void upgradesChanged(BfmeFixedStorage128 *,bool);
 
}
;
class HordeContain : public HordePrimary, public HordeInterface 
{
 public:
 void rva00468E79(int,int,bool);
 HordeMemberSlot *getOrdinarySlot() 
 {
  return &ordinary;
  
 }
 int getBannerCarrierIndexToUse(const Object *,const ThingTemplate **);
 void rva00473125(Object *,int *,int);
 void rva00473197(Object *,const Object *,bool,bool);
 Rva0046D158Record *rva0046D158(AsciiString);
 virtual Object *rva00473212(Object *,const Object *,bool);
 
}
;
Object *HordeContain::rva00473212(Object *object,const Object *source,bool flag)

{
 const ModuleData *fields = data();
 if (!object) return 0;
 if (object->getParent()) object=object->getParent();
 if (!flag7C) reset(true);
 transferring=true;
 if (!object->getParent() && !object->isHorde()) 
 {
  HordeMemberSlot *memberSlot = getOrdinarySlot();
  const int &slotValue = memberSlot->value();
  if (accepts(object,slotValue,&fields->ordinaryNames,false)) 
  {
   rva00473125(object,memberSlot->storage(),ordinaryIndex);
   return 0;
   
  }
  if (accepts(object,carrierID,&fields->bannerNames,flag)) 
  {
   if (flag || owner->getExperienceTracker()->getVeterancyLevel()<=1) 
   {
    rva00473197(object,source,flag,!suppress);
    return 0;
    
   }
   
  }
  if (!fields->matchNamed) return 0;
  
 }
 if (!object->rva0028C197()) 
 {
  if (!fields->matchNamed || fields->name.compare(object->type->name)!=0) return 0;
  
 }
 ThingTemplate *objectType = object->type;
 Rva0046D158Record *record = rva0046D158(objectType->name);
 if (!record) return 0;
 AsciiString replacement(record->replacement);
 const ThingTemplate *type=TheThingFactory->findTemplate(replacement);
 if (!type) return 0;
 Object *created;

 ModuleSlot15 *module=(ModuleSlot15*)owner->rva0028BC58(0);
 if (module) module->clear();
 module=(ModuleSlot15*)object->rva0028BC58(0);
 if (module) module->clear();
 refresh();
 ObjectList members;
 collect(members);
 Object *firstCarrier=TheGameLogic->findObjectByID((ObjectID)carrierID);
 Object *firstMember=0;
 if (firstCarrier) 
 {
  ObjectIterator found = _STL::find(members.begin(),members.end(),firstCarrier);
  if (found._M_node != members.head) 
  {
   reinterpret_cast<_STL::list<Object*>*>(&members)->erase(found);
   
  }

  if (!members.empty()) firstMember=members.front();
  
 }
 Object *secondCarrier=0;
 Object *secondMember=0;
 if (object->isHorde()) 
 {
  HordeContain *other=object->contain->result()->horde();
  other->refresh();
  other->collect(members);
  secondCarrier=TheGameLogic->findObjectByID((ObjectID)other->carrierID);
  if (secondCarrier) 
  {
   ObjectIterator found = _STL::find(members.begin(),members.end(),secondCarrier);
   if (found._M_node != members.head) 
   {
    reinterpret_cast<_STL::list<Object*>*>(&members)->erase(found);
    
   }
   if (!members.empty()) secondMember=members.back();
   
  }
  
 }
 else 
 {
  if (object->ai) object->ai->commands.rva0045003E(0,CMD_FROM_AI);
  members.append(object);
  
 }
 
 {
  CreateMask mask;
  memset(&mask,0,sizeof(mask));
  created=TheThingFactory->newObject(type,owner->getTeam(),&mask,(ObjectID)0);
  
 }
 reinterpret_cast<Thing*>(created)->setTransformMatrix(object->transform());
 TheAI->pathfinder->AddObjectToPathfindMap(created);
 BfmeFixedStorage128 upgrades(owner->upgrades);
 reinterpret_cast<_STL::_Base_bitset<32>*>(&upgrades)->_M_do_or(*reinterpret_cast<_STL::_Base_bitset<32>*>(&object->upgrades));
 reinterpret_cast<_STL::_Base_bitset<32>*>(&created->upgrades)->_M_do_or(*reinterpret_cast<_STL::_Base_bitset<32>*>(&upgrades));
 if (owner->testStatus((ObjectStatusTypes)73)) created->setStatus((ObjectStatusTypes)73,true);
 ContainResult *result=created->getContain() ? created->getContain()->result() : 0;
 if (!result) 
 {
  TheGameLogic->destroyObject(created);
  return 0;
  
 }
 else 
 {
  HordeContain *combined=result->horde();
  Object *carrier=0;
  const Object *member=0;
  if (firstCarrier && secondCarrier) 
  {
   if (firstCarrier->getExperienceTracker()->getVeterancyLevel()>=secondCarrier->getExperienceTracker()->getVeterancyLevel()) 
   {
    member=firstMember;
    carrier=firstCarrier;
    TheGameLogic->destroyObject(secondCarrier);
    
   }
   else 
   {
    carrier=secondCarrier;
    member=secondMember;
    TheGameLogic->destroyObject(firstCarrier);
    
   }
   
  }
  else if (firstCarrier) 
  {
   carrier=firstCarrier;
   member=firstMember;
   
  }
  else if (secondCarrier) 
  {
   carrier=secondCarrier;
   member=secondMember;
   
  }
  bool savedLatch=TheGameLogic->isScoringEnabled();
  ((HordeScoringView *)TheGameLogic)->scoringEnabled=false;
  created->rva0028BAAE(owner->value45C);
  if (carrier) 
  {
   if (member) 
   {
    LatchRestore<bool> suppress(combined->suppress,true);
    combined->rva00473212(carrier,member,true);
    
   }
   else TheGameLogic->destroyObject(carrier);
   
  }
  combined->replaceMembers(members);
  ((HordeScoringView *)TheGameLogic)->scoringEnabled=savedLatch;
  if (object->isHorde()) TheGameLogic->destroyObject(object);
  TheGameLogic->destroyObject(owner);
  reinterpret_cast<UpgradeView*>((char*)combined+0x20)->upgradesChanged(&created->upgrades,false);
  
 }
 
 return created;
 
}

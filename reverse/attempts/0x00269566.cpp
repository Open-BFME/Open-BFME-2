// ?NotifyPathHasInvalidPortals@AIUpdateInterface@@QAEXXZ
// partial score=0.978 date=2026-10-10
// ?NotifyPathHasInvalidPortals@AIUpdateInterface@@QAEXXZ
// partial score=0.9248446320271678 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /I. /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native269566..2697FC RET0; WB E599C0 named AIUpdateInterface::NotifyPathHasInvalidPortals.
// Named WB body resolves prior pin-only identity blocker; AIUpdate.cpp9187..9263.
// Horde bit109/template114, object model-condition bit122/base10C+word3,
// AI path140/loco1F0 and Object AI258 established directly in target accesses.
// Path-family/ZH provide data and service guides; horde-specific sequence follows WB and native.
// Retail frame4C and calls match; first b-loop entry is five bytes longer.
// Best score uses temporary self269566 and genuine ObjectID vector-swap candidate567ECD;
// no pins written. The swap must be fully verified as a relocation twin on landing.
// Integer nested flag test/SetBit restores TEST DWORD/OR DWORD versus scalar LEA/SHR.
#include <vector>
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
void __cdecl Rva00030830FreeAllocation(void*);
template<> __forceinline void _STL::allocator<ObjectID>::deallocate(ObjectID*p,unsigned)const{if(p)Rva00030830FreeAllocation(p);}
class NotifyFlags {public: unsigned int bits[19];unsigned test(int bit)const{return bits[bit>>5]&(1u<<(bit&31));} void SetBit(int bit){bits[bit>>5]|=1u<<(bit&31);}};
class AIUpdateInterface;
class ThingTemplate {public:char pad[0x114];unsigned int hordeKinds;unsigned getKinds()const{return hordeKinds;}};
class Thing {public: void setPosition(const Coord3D*);char pad0[4];ThingTemplate *templ;};
enum DamageType { DAMAGE_INVALID=8 };enum DeathType { DEATH_INVALID=0 };enum PathfindLayerEnum {LAYER_INVALID=0};
class Object:public Thing {public:
 Object*rva002931F5(bool); void *rva0028C197() const;void kill(DamageType,DeathType);void rva0028AE6D();
 __forceinline unsigned testCond()const{return modelCondition.test(122);}
 __forceinline void setCond(){modelCondition.SetBit(122);rva0028AE6D();}
 char pad8[0x10c-8];NotifyFlags modelCondition;char pad158[0x258-0x158];AIUpdateInterface *ai;
};
struct Rva003642DFNode;
struct Rva003642DFResult {Rva003642DFResult();Rva003642DFNode*node;Coord3D pos;};
class Rva0008BB38FloatField;
class Rva001E3511 {public:int rva001E3511();};
class Path {public:Rva003642DFResult rva00364521(const Rva0008BB38FloatField*);Coord3D rva003641F2() const;};
template<int N> class NotifySlots:public NotifySlots<N-1>{public:virtual void gap(char(*)[N])=0;};template<>class NotifySlots<0>{};
struct BfmeE12 { float x, y, z; }; // 12B element-agnostic swap stand-in; swap touches only header pointers
class NotifyHorde:public NotifySlots<135>{public:virtual void slot135(_STL::vector<ObjectID>*,_STL::vector<ObjectID>*,_STL::vector<ObjectID>*)=0;};
class TerrainLogic:public NotifySlots<35>{public:virtual void *slot35(int)=0;PathfindLayerEnum getLayerForDestination(Object*,const Coord3D*);};
class Rva0028B525DwordSlot {public:void set(int);};
extern TerrainLogic*TheTerrainLogic;extern GameLogic*TheGameLogic;
class AIUpdateInterface {public:void destroyPath();void NotifyPathHasInvalidPortals();char pad0[8];Object*owner;char padC[0x140-0xc];Path*path;char pad144[0x1f0-0x144];Rva0008BB38FloatField*loco;};
void AIUpdateInterface::NotifyPathHasInvalidPortals(){
 Object *obj=owner;
 if(!(obj->templ->hordeKinds&0x2000)){
  Object *brain=obj->rva002931F5(false);
  if(brain){if(!brain->ai)return;if(brain->ai->path)brain->ai->NotifyPathHasInvalidPortals();else destroyPath();return;}
 }
 Path *objPath=path;if(!objPath)return;
 Rva003642DFResult closest=objPath->rva00364521(loco);
 if(((Rva001E3511*)&closest)->rva001E3511()==0x7fffffff || TheTerrainLogic->slot35(((Rva001E3511*)&closest)->rva001E3511())){destroyPath();return;}
 if(obj->templ->getKinds()&0x2000){
  NotifyHorde*hci=(NotifyHorde*)obj->rva0028C197();if(!hci)return;
  _STL::vector<ObjectID> a,b,c;hci->slot135(&a,&b,&c);
  for(_STL::vector<ObjectID>::iterator i=b.begin();(i?i:i)!=b.end();++i){Object*member=TheGameLogic->findObjectByID(*i);if(member){member->kill(DAMAGE_INVALID,DEATH_INVALID);if(!member->testCond())member->setCond();}}
  bool swapped=false;if(c.size()<a.size()){reinterpret_cast<_STL::vector<BfmeE12>&>(c).swap(reinterpret_cast<_STL::vector<BfmeE12>&>(a));swapped=true;}
  for(_STL::vector<ObjectID>::iterator i=a.begin();i!=a.end();++i){Object*member=TheGameLogic->findObjectByID(*i);if(member){member->kill(DAMAGE_INVALID,DEATH_INVALID);if(!member->testCond())member->setCond();}}
  for(_STL::vector<ObjectID>::iterator i=c.begin();i!=c.end();++i){Object*member=TheGameLogic->findObjectByID(*i);if(member&&member->ai)member->ai->destroyPath();}
  if(swapped){Path *lastPath=path;Coord3D pos=lastPath->rva003641F2();obj->setPosition(&pos);((Rva0028B525DwordSlot*)obj)->set(TheTerrainLogic->getLayerForDestination(obj,&pos));}
  destroyPath();
 }else obj->kill(DAMAGE_INVALID,DEATH_INVALID);
}

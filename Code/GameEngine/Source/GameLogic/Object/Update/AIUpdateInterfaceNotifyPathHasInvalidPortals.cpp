// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs  /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native269566..2697FC RET0; WB E599C0 named AIUpdateInterface::NotifyPathHasInvalidPortals.
// Named WB body resolves prior pin-only identity blocker; AIUpdate.cpp9187..9263.
// Horde bit109/template114, object model-condition bit122/base10C+word3,
// AI path140/loco1F0 and Object AI258 established directly in target accesses.
// Path-family/ZH provide data and service guides; horde-specific sequence follows WB and native.
// The self-recursive call resolves to this row; the ObjectID vector swap is the
// genuine candidate 0x00567ECD (no pins written).
// Integer nested flag test/SetBit restores TEST DWORD/OR DWORD versus scalar LEA/SHR.
#include <vector>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
// The lookup chain (ObjectIdMap::find 0x002888D4 and GameLogic::findObjectByID
// 0x00049DC5, rowed COMDAT copies, as in GarrisonContainRemoveInvalidObjects.cpp)
// is visible in this unit; with it the natural first loop test gives retail's
// entry (mov ebx,begin / jmp to the bottom test) without the old equal-arm test.
struct VisLookupNode { VisLookupNode *next; ObjectID key; Object *object; };
struct VisLookupBuckets {
 VisLookupNode **begin,**end,**capacity;
 unsigned int size() const { return end-begin; }
 VisLookupNode *const &operator[](unsigned int i) const { return begin[i]; }
};
struct VisLookupMap { unsigned char hashEqual[4]; VisLookupBuckets buckets; };
inline ObjectIdNode *ObjectIdMap::find(const ObjectID &id) {
 VisLookupMap *map=(VisLookupMap*)this;
 unsigned int bucket=(unsigned int)id % map->buckets.size();
 VisLookupNode *node;
 for(node=map->buckets[bucket];node && node->key!=id;node=node->next) {}
 return (ObjectIdNode*)node;
}
inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == 0)
		return 0;
	ObjectIdNode *node = m_map.find(id);
	if (node == 0)
		return 0;
	return node->object;
}
void __cdecl Rva00030830FreeAllocation(void*);
template<> __forceinline void _STL::allocator<ObjectID>::deallocate(ObjectID*p,unsigned)const{if(p)::free(p);}
class NotifyFlags {public: unsigned int bits[19];unsigned test(int bit)const{return bits[bit>>5]&(1u<<(bit&31));} void SetBit(int bit){bits[bit>>5]|=1u<<(bit&31);}};
class AIUpdateInterface;
#include "../../../../Include/Common/ThingTemplate.h"
#include "../../../Common/Thing/thing.h"
enum DamageType { DAMAGE_INVALID=8 };enum DeathType { DEATH_INVALID=0 };enum PathfindLayerEnum {LAYER_INVALID=0};
class Object:public Thing {public:
 Object*rva002931F5(bool); void *rva0028C197() const;void kill(DamageType,DeathType);void rva0028AE6D();
 __forceinline unsigned testCond()const{return modelCondition.test(122);}
 __forceinline void setCond(){modelCondition.SetBit(122);rva0028AE6D();}
 char pad60[0x10c-0x60];NotifyFlags modelCondition;char pad158[0x258-0x158];AIUpdateInterface *ai;
};
struct Rva003642DFNode;
struct Rva003642DFResult {Rva003642DFResult();Rva003642DFNode*node;Coord3D pos;};
class Rva0008BB38FloatField;
#include "../../../../Include/GameLogic/Module/Rva001E3511.h"
#include "../../../../Include/GameLogic/PathfindPath.h"
template<int N> class NotifySlots:public NotifySlots<N-1>{public:virtual void gap(char(*)[N])=0;};template<>class NotifySlots<0>{};
struct BfmeE12 { float x, y, z; }; // 12B element-agnostic swap stand-in; swap touches only header pointers
class NotifyHorde:public NotifySlots<135>{public:virtual void slot135(_STL::vector<ObjectID>*,_STL::vector<ObjectID>*,_STL::vector<ObjectID>*)=0;};
#include "../../../../Include/GameLogic/TerrainLogic.h"
class Rva0028B525DwordSlot {public:void set(int);};
extern TerrainLogic*TheTerrainLogic;extern GameLogic*TheGameLogic;
class AIUpdateInterface {public:void destroyPath();void NotifyPathHasInvalidPortals();char pad0[8];Object*owner;char padC[0x140-0xc];Path*path;char pad144[0x1f0-0x144];Rva0008BB38FloatField*loco;};
void AIUpdateInterface::NotifyPathHasInvalidPortals(){
 Object *obj=owner;
 if(!(obj->m_template->m_kindof[3]&0x2000)){
  Object *brain=obj->rva002931F5(false);
  if(brain){if(!brain->ai)return;if(brain->ai->path)brain->ai->NotifyPathHasInvalidPortals();else destroyPath();return;}
 }
 Path *objPath=path;if(!objPath)return;
 Rva003642DFResult closest=objPath->rva00364521(loco);
 if(((Rva001E3511*)&closest)->rva001E3511()==0x7fffffff || TheTerrainLogic->getWaypointByID(((Rva001E3511*)&closest)->rva001E3511())){destroyPath();return;}
 if(obj->m_template->m_kindof[3]&0x2000){
  NotifyHorde*hci=(NotifyHorde*)obj->rva0028C197();if(!hci)return;
  _STL::vector<ObjectID> a,b,c;hci->slot135(&a,&b,&c);
  for(_STL::vector<ObjectID>::iterator i=b.begin();i!=b.end();++i){Object*member=TheGameLogic->findObjectByID(*i);if(member){member->kill(DAMAGE_INVALID,DEATH_INVALID);if(!member->testCond())member->setCond();}}
  bool swapped=false;if(c.size()<a.size()){reinterpret_cast<_STL::vector<BfmeE12>&>(c).swap(reinterpret_cast<_STL::vector<BfmeE12>&>(a));swapped=true;}
  for(_STL::vector<ObjectID>::iterator i=a.begin();i!=a.end();++i){Object*member=TheGameLogic->findObjectByID(*i);if(member){member->kill(DAMAGE_INVALID,DEATH_INVALID);if(!member->testCond())member->setCond();}}
  for(_STL::vector<ObjectID>::iterator i=c.begin();i!=c.end();++i){Object*member=TheGameLogic->findObjectByID(*i);if(member&&member->ai)member->ai->destroyPath();}
  if(swapped){Path *lastPath=path;Coord3D pos=lastPath->rva003641F2();obj->setPosition(&pos);((Rva0028B525DwordSlot*)obj)->set(TheTerrainLogic->getLayerForDestination(obj,&pos));}
  destroyPath();
 }else obj->kill(DAMAGE_INVALID,DEATH_INVALID);
}

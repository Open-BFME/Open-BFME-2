// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common
// Native 27B18C..27B47F RET4; unnamed WB CB7E40 supplies damage/EVA control flow.
// BF1 f989 / ZH Drawable lack this BF2 notification method; existing partition
// filter callers guide filter lifetime, while target vftables prove the slots.
// The shared lookup declarations keep the converged GameLogic global consistent.
// Visible lookup bodies describe the native read-only map operation.
// stlport
#include <vector>
#include "GameLogicObjectLookupView.h"
#include "PartitionRangeQueryCallView.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
enum KindOfType 
{
 RvaKind0=0
}
;

class Player
{
 public:char pad[0x54];
 int index;
 bool isLocalPlayer()const;
 
}
;
struct DamageInfo
{
 char pad0[8];
 ObjectID source;
 unsigned playerMask;
 int damageType;
 int p14;
 int p18;
 int p1c;
 char pad20[5];
 bool report;
 char pad26[0x70-0x26];
 float amount;
 
}
;
struct BfmeDamageTemplate
{
 char pad[0x10e];
 unsigned char flag10e;
 char pad10f[4];
 unsigned char flag113;
 char pad114[4];
 unsigned char flag118;
 char pad119[0x580-0x119];
 int m_evaEventDamagedOwner,m_evaEventDamagedFromShroudedSourceOwner,m_evaEventDamagedByFireOwner,m_evaEventSecondDamageFarFromFirstOwner;
 float range;
 unsigned delay;
 int event598;
 
}
;
class Drawable;
class Object
{
 public:void*vp;
 BfmeDamageTemplate*data;
 char pad08[0x38-8];
 Coord3D position;
 char pad44[0x260-0x44];
 void*radarInfo;
 Player*getControllingPlayer()const;
 bool isKindOf(KindOfType)const;
 bool rva00293926(KindOfType);
 bool rva00294471(void*,int);
 
}
;
#include "../Common/Thing/thing.h"
enum EvaEventID 
{
 EVA_INVALID=-1
}
;
#include "../../Include/GameClient/Eva.h"
extern Eva*TheEva;
#include "../../Include/Common/Radar.h"
extern Radar*TheRadar;
extern GameLogic *TheGameLogic;
class Rva002D3756
{
 public:void rva002D3756(void*);
 
}
;
class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
class Rva00271B03
{
 public:void rva00271B03();
 
}
;
#include "../../Include/GameLogic/PartitionFilter.h"
class Rva00271B3CFilter:public Rva000421C8
{
 public:Rva00271B3CFilter(int e):event(e)
 {
  
 }
 virtual bool allow(Object*);
 int event;
 
}
;
class Rva00260E2AFilter:public Rva000421C8
{
 public:Rva00260E2AFilter(Player*p):player(p)
 {
  
 }
 virtual bool allow(Object*);
 virtual int getPlayerMask();
 Player*player;
 
}
;
extern PartitionManager*ThePartitionManager;
class Drawable
{
 public:void rva0027B18C(DamageInfo*);
 const Coord3D *getPosition() const;
 char pad00[4];
 BfmeDamageTemplate*data;
 char pad08[0xfc-8];
 Object*object;
 char pad100[0x388-0x100];
 unsigned nextFrame;
 char pad38c[0x440-0x38c];
 bool active440;
 
}
;
struct DamageLookupNodeView { DamageLookupNodeView *next; ObjectID key; Object *object; };
struct DamageLookupMapView { unsigned count; _STL::vector<DamageLookupNodeView*> buckets; };
inline __declspec(noinline) ObjectIdNode *ObjectIdMap::find(const ObjectID &id)
{
 DamageLookupMapView *map = (DamageLookupMapView *)this;
 unsigned bucket = (unsigned)id % map->buckets.size();
 DamageLookupNodeView *node = map->buckets[bucket];
 while(node) {
  if(node->key == id) break;
  node = node->next;
 }
 return (ObjectIdNode *)node;
}
inline __declspec(noinline) Object *GameLogic::findObjectByID(ObjectID id)
{
 if(id == INVALID_OBJECT_ID) return 0;
 ObjectIdNode *node = m_map.find(id);
 if(!node) return 0;
 return node->object;
}
void Drawable::rva0027B18C(DamageInfo*damage)
{
 Object*obj=object;
 if(!obj)return;
 if((obj->data->flag10e&0x40)&&(obj->data->flag118&0x40))return;
 Player*player=obj->getControllingPlayer();
 const BfmeDamageTemplate*templ=data;
 if(!(damage->amount>0.0f)||damage->damageType==10||damage->damageType==7||damage->p1c==22||damage->p18==2||(damage->playerMask&(1<<player->index))||!player->isLocalPlayer())return;
 if(damage->report)
 {
  if(obj->radarInfo)TheRadar->tryUnderAttackEvent(obj);
  if(templ)
  {
   Object*attacker=TheGameLogic->findObjectByID(damage->source);
   int event598=templ->event598;
   int event,other;
   if(event598!=-1&&!obj->isKindOf((KindOfType)157)&&!obj->rva00293926((KindOfType)63)&&!obj->rva00293926((KindOfType)37)&&attacker&&!attacker->rva00294471(player,1))
   {
    event=event598;
    other=templ->m_evaEventSecondDamageFarFromFirstOwner;
    
   }
   else if(damage->damageType==23&&templ->m_evaEventDamagedByFireOwner!=-1)
   {
    event=templ->m_evaEventDamagedByFireOwner;
    other=-1;
    
   }
   else if(damage->damageType!=23&&attacker&&((Thing*)attacker)->getDrawable()&&((Thing*)attacker)->getDrawable()->active440&&templ->m_evaEventDamagedFromShroudedSourceOwner!=-1)
   {
    event=templ->m_evaEventDamagedFromShroudedSourceOwner;
    other=templ->m_evaEventSecondDamageFarFromFirstOwner;
    
   }
   else
   {
    event=templ->m_evaEventDamagedOwner;
    other=templ->m_evaEventSecondDamageFarFromFirstOwner;
    
   }
   if(event!=-1)
   {
   GameLogic* gl=TheGameLogic;
   unsigned now=gl->getFrame();
   if(nextFrame<=now&&(TheEva->isEventBlockedByTimeout((EvaEventID)event)||TheEva->isEventAboutToPlay((EvaEventID)event))&&other!=-1)TheEva->reportEvaEvent((EvaEventID)other,&obj->position,0);
   else TheEva->reportEvaEvent((EvaEventID)event,&obj->position,0);
    float range=templ->range;
    if(range<=0.0f||templ->m_evaEventDamagedOwner==-1)((Rva00271B03*)this)->rva00271B03();
    else
    {
     Rva00271B3CFilter eventFilter(templ->m_evaEventDamagedOwner);
     Rva00260E2AFilter playerFilter(player);
     eventFilter.link(&playerFilter);
     BfmeWideResult objects=ThePartitionManager->iterateObjectsInRange(getPosition(),range,2,&eventFilter,0);
     for(Object*nearbyObject=objects.next();nearbyObject;nearbyObject=objects.next())if(((Thing*)nearbyObject)->getDrawable())((Rva00271B03*)((Thing*)nearbyObject)->getDrawable())->rva00271B03();
     
    }
    
   }
   
  }
  
 }
 if(data->flag113&4)((Rva002D3756 *)theRadarWindowOverrideSource)->rva002D3756(obj);
 
}

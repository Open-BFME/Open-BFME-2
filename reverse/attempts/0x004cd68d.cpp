// ?triggerAbilityEffect@TeleportToCasterSpecialPower@@UAEXXZ
// partial score=0.8494083737864078 date=2026-10-09
// cl: /O1 /G7 /O2 /Os /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Include /I.
// stlport
// TeleportToCasterSpecialPower::teleportList: WB12777E0 assertion84 establishes name; native4CD51B..4CD68D RET8 establishes extent370 and layout/calls.
// No applicable clean BF1/ZH TeleportToCaster source at readonly9cbfb551. Data+CC/D0 ring radii, Object44 orientation/258 AI; native vector element IDs use shared lookup enum.
#include <vector>
#include <string.h>
#include <math.h>
#include "Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
namespace _STL {template<> __forceinline _Vector_base<ObjectID,allocator<ObjectID> >::~_Vector_base() { if(_M_start!=0) _M_end_of_storage.deallocate(_M_start,_M_end_of_storage._M_data-_M_start); }}
extern GameLogic *TheGameLogic;
enum CommandSourceType{COMMANDSOURCE_SCRIPT=2};
class AICommandInterface{public:void aiIdle(CommandSourceType);};
struct TeleportAI{char pad[0x20];AICommandInterface commands;};
class Player;
struct TeleportThingTemplate{char pad[0x115];unsigned char kind115;};
enum ObjectStatusTypes{STATUS_UNK=-1};
class Object{public:char pad[4];TeleportThingTemplate *thingTemplate;char pad08[0x38-8];Coord3D position;float orientation;char pad48[0x74-0x48];ObjectID id,storedByID;char pad7C[0x258-0x7C];TeleportAI *ai;void teleportTo(const Coord3D*,bool);Player *getControllingPlayer()const;bool testStatus(ObjectStatusTypes)const;};
class Thing{public:void setOrientation(float);};
class Rva004CD4DC{public:void rva004CD4DC(Object*);};
class FXList;class Matrix3D;
struct TeleportData{char pad[0xC8];float radius,minRadius,maxRadius;const FXList *endFX;};
struct FindPositionOptions{
 FindPositionOptions():flags(0),minRadius(0),maxRadius(0),startAngle(-99999.9f),maxZDelta(1e10f),ignoreObject(0),sourceToPathToDest(0),relationshipObject(0){}
 unsigned flags;float minRadius,maxRadius,startAngle,maxZDelta;const Object *ignoreObject,*sourceToPathToDest,*relationshipObject;
};
double __cdecl Rva000422A0Atan2(float,float);
class TeleportToCasterSpecialPower{public:virtual void triggerAbilityEffect();const TeleportData *data;Object *owner;char pad0C[0x44-0x0C];Coord3D targetPosition;void teleportList(const _STL::vector<ObjectID>*,const Coord3D*);};
void TeleportToCasterSpecialPower::teleportList(const _STL::vector<ObjectID>*ids,const Coord3D*center){
 const TeleportData *moduleData=data;
 FindPositionOptions options;options.minRadius=moduleData->minRadius;options.maxRadius=moduleData->maxRadius;
 int count=ids->size();float angleSpacing=6.28318530718f/count;float angle=0;
 for(_STL::vector<ObjectID>::const_iterator it=ids->begin();it!=ids->end();++it,angle+=angleSpacing){
  Object *object=TheGameLogic->findObjectByID(*it);
  if(object){
   ((Rva004CD4DC*)this)->rva004CD4DC(object);
   float orientation=object->orientation;options.startAngle=angle;Coord3D position;
   if(PartitionManager::findPositionAround(center,&options,&position)){double dx=(double)position.x-center->x;float dy=(float)((double)position.y-center->y);orientation=(float)Rva000422A0Atan2(dy,(float)dx);}
   else position=*center;
   if(object->ai)object->ai->commands.aiIdle(COMMANDSOURCE_SCRIPT);
   ((Thing*)object)->setOrientation(orientation);object->teleportTo(&position,false);
   ((Rva004CD4DC*)this)->rva004CD4DC(object);
  }
 }
}

// StoreObjectsSpecialPower lookup: target128B proves owner+8 object, object244 module list and slot4 name-key query; store+88 vector uses ObjectID-width unsigned slots.
enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Rva004CD45CItem
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual NameKeyType getKey();
	unsigned char m_pad[0x88 - 4];
	unsigned int *m_vecBeg;
	unsigned int *m_vecEnd;
};

struct Rva004CD45CMid
{
	unsigned char m_pad[0x244];
	Rva004CD45CItem **m_list;
};

class Rva004CD45C
{
public:
	unsigned char m_pad0[8];
	Rva004CD45CMid *m_mid;
	void *rva004CD45C();
};

// ?rva004CD45C@Rva004CD45C@@QAEPAXXZ @0x004CD45C128B
void *Rva004CD45C::rva004CD45C()
{
	static NameKeyType s_key = TheNameKeyGenerator->nameToKey("StoreObjectsSpecialPower");
	Rva004CD45CMid *mid = m_mid;
	Rva004CD45CItem **pp = mid->m_list;
	for (;;) {
		Rva004CD45CItem *cur = *pp;
		if (cur == 0)
			return 0;
		if (cur->getKey() != s_key) {
			pp++;
			continue;
		}
		cur = *pp;
		if (cur == 0) {
			pp++;
			continue;
		}
		unsigned int **vec = (unsigned int **)((char *)cur + 0x88);
		unsigned int diff = vec[1] - vec[0];
		if (diff > 0)
			return cur;
		pp++;
	}
}

// Target622B virtual override: WB1277B60 directly calls SpecialAbility base trigger, then teleports stored IDs or a filtered range and plays endFX.
class SpecialAbilityUpdate{public:virtual void triggerAbilityEffect();};
class Rva004CDA35{public:void rva004CDA35();};
class Rva0044E633{public:void *rva0044E633();};
class Overridable{public:const Overridable *friend_getFinalOverride()const;};
template<int N>class TeleportSlots:public TeleportSlots<N-1>{public:virtual void gap(char(*)[N])=0;};template<>class TeleportSlots<0>{};
class TeleportPowerInterface:public TeleportSlots<6>{public:virtual const Overridable *getTemplate()const;};
class Rva000421C8{public:Rva000421C8():m_next(0){}virtual ~Rva000421C8(){}virtual bool allow(Object*)=0;virtual int getPlayerMask();Rva000421C8 *link(Rva000421C8*);Rva000421C8 *m_next;};
class Rva002614ECFilter:public Rva000421C8{public:Rva002614ECFilter(const void *what,Player *player,bool match):m_what(what),m_player(player),m_match(match){}virtual bool allow(Object*);const void *m_what;Player*m_player;bool m_match;};
class Rva002611BFFilter:public Rva000421C8{public:Rva002611BFFilter(Object*o):m_object(o){}virtual bool allow(Object*);Object*m_object;};
class Rva00260EB1Filter:public Rva000421C8{public:Rva00260EB1Filter(Object*o,int flags,bool inverse):m_object(o),m_flags(flags),m_inverse(inverse){}virtual bool allow(Object*);virtual int getPlayerMask();Object*m_object;int m_flags;bool m_inverse;};
class Rva0026119DFilter:public Rva000421C8{public:virtual bool allow(Object*);};
class Rva002614DFFilter:public Rva000421C8{public:Rva002614DFFilter(Object*o):m_object(o){}virtual bool allow(Object*);Object*m_object;};
class BfmeFixedStorage0004543D{public:char bits[28];BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D&)throw();};
class Rva0006EE7A{public:Rva0006EE7A(int,int,int)throw();unsigned bits[7];};
template<int N>class BitFlags{public:unsigned bits[7];};extern BitFlags<116> KINDOFMASK_NONE;
class PartitionFilterRejectByKindOf:public Rva000421C8{public:PartitionFilterRejectByKindOf(const BfmeFixedStorage0004543D&,const BfmeFixedStorage0004543D&)throw();virtual bool allow(Object*);BfmeFixedStorage0004543D a,b;};
class BfmeObject872Header{public:__forceinline BfmeObject872Header(){memset(bits,0,sizeof(bits));}BfmeObject872Header(const BfmeObject872Header&);unsigned bits[4];};
class Rva0023DA79{public:Rva0023DA79*rva0023DA79(int,int);unsigned bits[4];};
class Rva002FDF1C:public Rva000421C8{public:Rva002FDF1C(const BfmeObject872Header&,const BfmeObject872Header&);virtual bool allow(Object*);BfmeObject872Header a,b;};
class FXList{public:static void doFXPos(const FXList*,const Coord3D*,const Matrix3D*,float,const Coord3D*);};
extern PartitionManager *ThePartitionManager;
void TeleportToCasterSpecialPower::triggerAbilityEffect(){
 ((SpecialAbilityUpdate*)this)->SpecialAbilityUpdate::triggerAbilityEffect();
 Object *object=owner;const TeleportData *moduleData=data;
 Rva004CD45CItem *stored=(Rva004CD45CItem*)((Rva004CD45C*)this)->rva004CD45C();
 if(stored){teleportList((const _STL::vector<ObjectID>*)&stored->m_vecBeg,&targetPosition);((Rva004CDA35*)stored)->rva004CDA35();}
 else{
  const Overridable *power=((TeleportPowerInterface*)((Rva0044E633*)this)->rva0044E633())->getTemplate()->friend_getFinalOverride();
  const void *what=(const char*)power+0x60;
  Rva0023DA79 statusMask;
  BfmeWideResult result=ThePartitionManager->iterateObjectsInRange(&targetPosition,moduleData->radius,0,
    Rva002614DFFilter(object).link(Rva0026119DFilter().link(PartitionFilterRejectByKindOf(*(const BfmeFixedStorage0004543D*)&Rva0006EE7A(0,7,0x86),*(const BfmeFixedStorage0004543D*)&KINDOFMASK_NONE).link(
     Rva00260EB1Filter(object,4,false).link(Rva002611BFFilter(object).link(&Rva002614ECFilter(what,object->getControllingPlayer(),true))->link(
      &Rva002FDF1C(*(BfmeObject872Header*)statusMask.rva0023DA79(0,0x26),BfmeObject872Header())))))),1);
  _STL::vector<ObjectID> ids;
  Object *item;
  while((item=result.next())!=0){
   Object *caster=TheGameLogic->findObjectByID(item->storedByID);
   if(caster&&(caster->thingTemplate->kind115&0x20))continue;
   if(item->testStatus((ObjectStatusTypes)3)||item->testStatus((ObjectStatusTypes)2))continue;
   ObjectID id=item->id;ids.push_back(id);
  }
  teleportList(&ids,&object->position);
 }
 FXList::doFXPos(moduleData->endFX,&targetPosition,0,0.0f,0);
}

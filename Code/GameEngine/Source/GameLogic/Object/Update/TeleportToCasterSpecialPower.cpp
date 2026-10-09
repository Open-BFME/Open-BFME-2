// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include /I.
// stlport
// TeleportToCasterSpecialPower::teleportList: WB12777E0 assertion84 establishes name; native4CD51B..4CD68D RET8 establishes extent370 and layout/calls.
// No applicable clean BF1/ZH TeleportToCaster source at donor9cbfb551 (rechecked at0bef414b). Data+CC/D0 ring radii, Object44 orientation/258 AI; native vector element IDs use shared lookup enum.
#include <vector>
#include <math.h>
#include "Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
extern GameLogic *TheGameLogic;
enum CommandSourceType{COMMANDSOURCE_SCRIPT=2};
class AICommandInterface{public:void aiIdle(CommandSourceType);};
struct TeleportAI{char pad[0x20];AICommandInterface commands;};
class Object{public:char pad[0x44];float orientation;char pad48[0x258-0x48];TeleportAI *ai;void teleportTo(const Coord3D*,bool);};
class Thing{public:void setOrientation(float);};
class Rva004CD4DC{public:void rva004CD4DC(Object*);};
struct TeleportData{char pad[0xCC];float minRadius,maxRadius;};
struct FindPositionOptions{
 FindPositionOptions():flags(0),minRadius(0),maxRadius(0),startAngle(-99999.9f),maxZDelta(1e10f),ignoreObject(0),sourceToPathToDest(0),relationshipObject(0){}
 unsigned flags;float minRadius,maxRadius,startAngle,maxZDelta;const Object *ignoreObject,*sourceToPathToDest,*relationshipObject;
};
double __cdecl Rva000422A0Atan2(float,float);
class TeleportToCasterSpecialPower{public:char pad[4];const TeleportData *data;void teleportList(const _STL::vector<ObjectID>*,const Coord3D*);};
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

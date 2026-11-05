// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Whole file:17B primary slot5 at462213 and340B secondary slot0 at4622FC.
// Native4622FC..462450/RET0 and WB11907E0 independently identify triggerFlee.
// The +10 interface receiver reads Object at-8 and moduleData at-C; the
// matched ctor46217B establishes these interface offsets and tableC4307C.
// Module-data ctor254ECE plus parse table establish the waypoint name14,
// requires-specific-trigger10 and die-on-map18 fields. Native Object fields
// position38, AI258, Body254 and condition word128 are direct evidence.
// Native waypoint prefix holds positionC; terrain slots6/34 provide ground
// height and named-waypoint lookup, and TheAI's pathfinder sits at10.
// Every existing named global and callee spelling is retained; in particular
// the294D61 reporting provider is still opaque, despite WB's scoreTheKill lead.
// No original payload name, full object size, new pin or alias is asserted.
// Retained BF1 CEE35 RunOffMapBehaviorDestructor.cpp was compiled under BF2
// settings as a read-only lead search (zero placements); it supports related
// interface inheritance only and contains no triggerFlee body. WB and native
// supply this body's behavior. No ZH RunOffMapBehavior source exists there.
// Member-wise direction copying permits the native SSE two-component scale;
// a conditional boolean flag test retains DWORD operations instead of byte
// narrowing. Force-inline expresses the observed inlined bit operations,
// without claiming retail's historical annotation. All other views are
// accessed prefixes, not allocating layouts.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "ascii_string.h"
#include "../../../Common/GameLogicObjectLookupView.h"
class Object;

#include "../../command_source_type.h"
enum DamageType { DAMAGE_8=8 };
enum DeathType { DEATH_0=0 };
enum ObjectStatusTypes { STATUS_32=0x32 };
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
struct DamageInfoSourceView { char pad00[8];ObjectID id; };
class RunOffBodyView { public:
 
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
 
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual const DamageInfoSourceView *lastDamage() const;
};
#include "../../../Common/Thing/thing.h"
struct RunOffModelFlagsView {
 unsigned words[19];
 __forceinline bool test(unsigned bit) const {if(words[bit>>5] & (1U<<(bit&31)))return true;return false;}
 __forceinline void set(unsigned bit) {words[bit>>5] |= 1U<<(bit&31);}
};
class Object : public Thing {public:
 AIUpdateInterface *ai() const {return m_ai;}
 RunOffBodyView *body() const {return m_body;}
 void kill(DamageType,DeathType);
 void setStatus(ObjectStatusTypes,bool);
 void rva0028AE6D();
 
 friend class RunOffMapBehavior;
 private:char pad60[0x10c-0x60];RunOffModelFlagsView m_conditions;char pad158[0x254-0x158];RunOffBodyView *m_body;AIUpdateInterface *m_ai;
};
class Rva00294D61 {public:void report(Object *,int);};

extern GameLogic *TheGameLogic;
#include "../../../../Include/GameLogic/AIPathfind.h"
class AI;extern AI *TheAI;
struct RunOffAIView {char pad00[0x10];Pathfinder *pathfinder;};
struct RunOffWaypointView {char pad00[0xc];Coord3D position;};
class TerrainLogic;extern TerrainLogic *TheTerrainLogic;
class RunOffTerrainView {public:
 
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual float groundHeight(float,float,void *);
 
 virtual void v7();
 virtual void v8();
 virtual void v9();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void v20();
 virtual void v21();
 virtual void v22();
 virtual void v23();
 virtual void v24();
 virtual void v25();
 virtual void v26();
 virtual void v27();
 virtual void v28();
 virtual void v29();
 virtual void v30();
 virtual void v31();
 virtual void v32();
 virtual void v33();
 virtual RunOffWaypointView *waypoint(const AsciiString &) const;
};
struct RunOffMapBehaviorModuleData {char pad00[0x10];bool m_10;AsciiString waypointName;bool dieOnMap;};
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
class RunOffMapBehaviorInterface {public:virtual void triggerFlee()=0;};
class RunOffMapBehavior:public BehaviorModule,public RunOffMapBehaviorInterface {public:
 virtual NameKeyType getModuleNameKey() const;virtual void rva00462213();virtual void triggerFlee();
};
void RunOffMapBehavior::rva00462213()
{
	if (!reinterpret_cast<const RunOffMapBehaviorModuleData *>(getModuleData())->m_10)
		triggerFlee();
}

void RunOffMapBehavior::triggerFlee()
{
	Object *obj = getObject();
	AIUpdateInterface *ai = obj->ai();
	if (!ai)
		return;
	const RunOffMapBehaviorModuleData *data = reinterpret_cast<const RunOffMapBehaviorModuleData *>(getModuleData());
	if (!data)
		return;
	Coord3D destination;
	RunOffWaypointView *waypoint = ((RunOffTerrainView *)TheTerrainLogic)->waypoint(data->waypointName);
	if (waypoint)
		destination = waypoint->position;
	else
	{
		const Coord3D *source = obj->getUnitDirectionVector2D();
		Coord3D direction;
		direction.x = source->x;
		direction.y = source->y;
		direction.z = source->z;
		Coord3D *dir = &direction;
		dir->x *= 500.0f;
		dir->y *= 500.0f;
		destination.x = obj->getPosition()->x + direction.x;
		destination.y = obj->getPosition()->y + direction.y;
		destination.z = ((RunOffTerrainView *)TheTerrainLogic)->groundHeight(destination.x, destination.y, 0);
	}
	Pathfinder *pf = ((RunOffAIView *)TheAI)->pathfinder;
	if (!pf->QuickDoesPathExist(obj, obj->getPosition(), &destination, 0))
	{
		ObjectID source = obj->body()->lastDamage() ? obj->body()->lastDamage()->id : INVALID_OBJECT_ID;
		Object *killer = TheGameLogic->findObjectByID(source);
		if (killer)
			((Rva00294D61 *)killer)->report(obj, 1);
		obj->kill(DAMAGE_8, DEATH_0);
		return;
	}
	if (data->dieOnMap == true)
		ai->aiMoveToAndDie(&destination, CMD_FROM_AI);
	else
		ai->aiMoveToAndDelete(&destination, CMD_FROM_AI);
	obj->setStatus(STATUS_32, true);
	if (!obj->m_conditions.test(0xfc))
	{
		obj->m_conditions.set(0xfc);
		obj->rva0028AE6D();
	}
}

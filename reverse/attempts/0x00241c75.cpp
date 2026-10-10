// ?rva00241C75@@YAXHPBVGameSlot@@PAVPlayer@@PBVPlayerTemplate@@@Z
// partial score=0.6730951214339518 date=2026-10-10
// ?rva00241C75@@YAXHPBVGameSlot@@PAVPlayer@@PBVPlayerTemplate@@@Z
// Complete UNVERIFIED bank. Temporary read-only scorer map assigns the
// three-argument living-world helper to native24104A; no pin is proposed.
// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /I. /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// Lookup via g_009FF000 Rva002D06CA 0x002D06CA, GlobalData guard +0x1110,
// set<AsciiString> ctor 0x000D3A71 + notify 0x0033CF34 + merge 0x0061F010,
// CreateMask via ji_006291ae, ThingFactory::newObject 0x002D0A23,
// Thing::setOrientation 0x0030AB9D + setPosition 0x0030AA80, pathfind + adjust.
// Evidence: callers at 0x002411BF 0x00241DA1 0x00242195, prev 0x00240DF1 next 0x002418E2.
#include "ascii_string.h"
#include <math.h>
#define _OPERATOR_NEW_DEFINED_
#include "vector3.h"
#include <set>

#include "Code/Libraries/Include/Lib/Coord3D.h"
struct Rva001408C0Target;
class AssetList {public:AssetList():pad(0),changed(true){} private:_STL::set<Rva001408C0Target*> prototypes;unsigned pad;bool changed;};
struct AssetLoadMode{bool alternate;AssetLoadMode():alternate(false){}};
class ThingTemplate;
class ThingFactory;
class Team;
class Object;
class Thing;
class LocomotorSet;
class Pathfinder;
class BFMEPathfinderMapShim;
class GlobalData;
class AI;
struct CreateMask;

extern ThingFactory *TheThingFactory;

class GlobalData
{
public:
	char m_pad[0x1110];
	unsigned char m_1110;
};

extern GlobalData *TheWritableGlobalData;

class Rva0020AA00Target
{
public:
	void notify(int a, int b);
};

void __cdecl bfmeMergeReceiverKeys(int value);

extern "C" void *__cdecl memset(void *,int,unsigned int);
#pragma function(memset)

struct CreateMask
{
	char m_data[0x10];
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);	// 0x002D06CA
public:
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, bool flag);
};

class Thing
{
public:
	void setOrientation(float v);
	void setPosition(const Coord3D *pos);
};

class ThingTemplate
{
public:
	char m_pad[0x108];
	unsigned char m_flags108;
	char m_pad2[0x4D0 - 0x109];
	float m_orient4D0;
};

class Team
{
public:
	char m_pad[0x5D];
	unsigned char m_5d;
	unsigned char m_5e;
};

class LocomotorSet
{
public:
	char m_data[4];
};

class AIUpdateInterface
{
public:
	char m_pad[0x1CC];
	LocomotorSet m_loco;
};

enum NameKeyType {NetworkNameKeyUnknown};
class Module;
class Object
{
public:
	void rva0028ACEE(int a, int b);
protected:Module *findModule(NameKeyType) const;
public:Module *lookupModule(NameKeyType n)const{return findModule(n);}
};

class Rva0028CBFD
{
public:
	void rva0028CBFD();
};

class BFMEPathfinderMapShim
{
public:
	void addObjectToPathfindMap(Object *obj);
};

class Pathfinder
{
public:
 void AddObjectToPathfindMap(Object*);
	bool adjustDestination(Object *obj, const LocomotorSet &set, Coord3D *dst, const Coord3D *group);
};

class AI
{
public:
	char m_pad[0x10];
	Pathfinder *m_pf;
};

extern AI *TheAI;

class Player
{
public:
	char m_pad[0x2EC];
	Team *m_team;
	char pad2F0[0x3AC-0x2F0];
	int livingId;
	void onStructureCreated(Object*,Object*);
 void onUnitCreated(Object*,Object*);
	void onStructureConstructionComplete(Object*,Object*,bool);
};

static Object *placeObjectAtPosition(int slot, AsciiString name, const Coord3D *pos, Player *player, const void *playerTemplate)
{
	void *tmplRaw = (void *)TheThingFactory->findTemplate(name);
	if (tmplRaw == 0)
		return 0;
	ThingTemplate *tmpl = (ThingTemplate *)tmplRaw;
	if (TheWritableGlobalData->m_1110 == 0) {
		AssetLoadMode mode;
		AssetList receivers;
		((Rva0020AA00Target *)tmpl)->notify((int)&receivers, (int)&mode);
		bfmeMergeReceiverKeys((int)&receivers);
	}
	Object *obj;
	{
	CreateMask mask;
	memset(&mask, 0, 0x10);
	Team *team = player->m_team;
	obj = TheThingFactory->newObject((const ThingTemplate *)tmpl, team, &mask, false);
	}
	if (obj) {
	ThingTemplate *t2 = *(ThingTemplate **)((char *)obj + 4);
	((Thing *)obj)->setOrientation(t2->m_orient4D0);
	((Thing *)obj)->setPosition(pos);
	Team *t = player->m_team;
	((Rva0028CBFD *)obj)->rva0028CBFD();
	if (t != 0) {
		if (t->m_5d == 0) {
			t->m_5e = 1;
			t->m_5d = 1;
		}
	}
	TheAI->m_pf->AddObjectToPathfindMap(obj);
	AIUpdateInterface *aiu = *(AIUpdateInterface **)((char *)obj + 0x258);
	if (aiu && !((*(ThingTemplate **)((char *)obj + 4))->m_flags108 & 4)) {
		LocomotorSet *loco = &aiu->m_loco;
		Pathfinder *pf = TheAI->m_pf;
		if (pf->adjustDestination(obj, *loco, (Coord3D *)pos, 0)) {
			obj->rva0028ACEE((int)pos, 1);
			((Thing*)obj)->setPosition(pos);
		}
	}
	}
	return obj;
}


#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Rva003F468D;
class Rva0020E89C;
class Rva002E2903Player;
class Rva0020E6B7RegionManager {public:Rva003F468D *rva0020E6B7();};
class Rva0020EAF6View {public:Rva0020E89C *rva0020EAF6(int);};
class Rva002BA8F1Logic {public:char pad[0xB0];Rva0020E6B7RegionManager *regions;char padB4[4];int currentRegion;Rva002E2903Player *find(int,unsigned*);};
extern Rva002BA8F1Logic *TheLivingWorldLogic;
class LivingWorldBattle {public:void *rva003F4FBD(void*);};
struct LivingArmy {char pad[0x20];int id;};
struct LivingBuildingTemplate {char pad[0xC];AsciiString name;};
class LivingWorldBuilding {public:char pad[0x18];int id;char pad1C[0xC];LivingBuildingTemplate *definition;};
class LivingWorldRegion {public:char pad[0x13C];int owner;int rva003F05CE();LivingWorldBuilding *GetBuildingByIndex(int)const;};
class Waypoint {public:Waypoint(unsigned,AsciiString,const Coord3D*,AsciiString,AsciiString,AsciiString,bool,int,AsciiString);virtual ~Waypoint();char pad[8];Coord3D position;char rest[0xC0-0x18];};
Waypoint *Rva00506CC3FindWaypoint(const AsciiString&);
void ValidateLivingWorldBuildPlotWaypoints(Waypoint*,int);
class Rva0040D280Sub {public:void method(Object*,int);};
class PlayerTemplate;
void PlaceLivingWorldObjectsForPlayer(Player *player,const PlayerTemplate *unusedTemplate,int unusedSlot) {
 if(TheGameLogic->m_114==3) return;
 LivingWorldRegion *region; int armyId;
 {
 int livingId=player->livingId;
 int savedLivingId;
 *(volatile int*)&savedLivingId=livingId;
 if(livingId==-1) return;
 LivingWorldBattle *battle=(LivingWorldBattle*)TheLivingWorldLogic->regions->rva0020E6B7();
 if(!battle) return;
 Rva002E2903Player *worldPlayer=TheLivingWorldLogic->find(livingId,0);
 if(!worldPlayer) return;
 LivingArmy *army=(LivingArmy*)battle->rva003F4FBD(worldPlayer);
 armyId=army?army->id:0;
 if(!armyId) return;
 int currentRegion=TheLivingWorldLogic->currentRegion;
 region=(LivingWorldRegion*)((Rva0020EAF6View*)TheLivingWorldLogic->regions)->rva0020EAF6(currentRegion);
 if(!region || region->owner!=savedLivingId) return;
 }
 AsciiString waypointName("Player_1_Start");
 Waypoint *start=Rva00506CC3FindWaypoint(waypointName);
 if(!start) return;
 ValidateLivingWorldBuildPlotWaypoints(start,region->rva003F05CE());
 for(int i=0;i<region->rva003F05CE();++i){
  LivingWorldBuilding *building=region->GetBuildingByIndex(i);
  const AsciiString &name=building->definition->name;
  if(name.isEmpty()) continue;
  waypointName.format("Player_1_BuildPlot_%d",i+1);
  Waypoint *waypoint=Rva00506CC3FindWaypoint(waypointName);
  if(!waypoint) continue;
  Coord3D pos; pos.x=waypoint->position.x;pos.y=waypoint->position.y;pos.z=waypoint->position.z;
  Object *obj=placeObjectAtPosition(0,name,&pos,player,0);
  if(!obj) continue;
  player->onStructureCreated(0,obj);
  player->onStructureConstructionComplete(0,obj,false);
  ((Rva0040D280Sub*)((char*)TheGameLogic+0x184))->method(obj,armyId);
  *(int*)((char*)obj+0x464)=building->id;
 }
}
// Reference: ZH GameLogic.cpp548 network-start placement. WB CFABB0
// confirms the BFME additions; native241C75..2421F5 supplies every offset,
// mode branch, CastleBehavior radius, ten starting offsets and polar math.
class GameSlot {public:char pad[0x10];int startPos;};
class PlayerTemplate {public:char pad[0x44];AsciiString startingBuilding;};
class Rva001FD19E {public:const char *rva001FD19E(int);};
class Rva001FD2D9 {public:Coord3D *rva001FD2D9(Coord3D*,int);};
struct FindPositionOptions {unsigned flags;float minRadius,maxRadius,startAngle,maxZDelta;void *ignoreObject;const void *sourceToPathToDest;void *relationshipObject;};
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;
class NetworkPartitionDispatch {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void update();};
class TerrainLogic {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual float getGroundHeight(float,float,Coord3D*);};
extern TerrainLogic *TheTerrainLogic;
struct NetworkObjectPrefix {char pad[0x88];AsciiString name;char pad8C[0xB8-0x8C];float radius,width;};
class Rva00395A60 {public:float rva00395A60();};
class CastleBehavior {public:static NameKeyType rva0003955DA();};
class Rva002A9BF2 {public:void rva002A9D02(int,Object*,int);};
void rva00241C75(int slotNum,const GameSlot *slot,Player *player,const PlayerTemplate *pt) {
 int startPos=slot->startPos;
 AsciiString waypointName;waypointName.format("Player_%d_Start",startPos+1);
 AsciiString rallyName;rallyName.format("Player_%d_Rally",startPos+1);
 Waypoint *start=Rva00506CC3FindWaypoint(waypointName);
 Waypoint *rally=Rva00506CC3FindWaypoint(rallyName);
 if(!start)return;
 Coord3D pos=start->position;
 pos.z=TheTerrainLogic->getGroundHeight(pos.x,pos.y,0);
 if(TheGameLogic->m_114!=3){PlaceLivingWorldObjectsForPlayer(player,pt,slotNum);return;}
 AsciiString buildingName(pt->startingBuilding);
 float radius=50.0f;Object *yard=0;
 if(buildingName.isNotEmpty() && *(const int*)((const char*)start+0x60)==0) {
  yard=placeObjectAtPosition(slotNum,buildingName,&pos,player,pt);
  if(!yard)return;
  NetworkObjectPrefix *view=reinterpret_cast<NetworkObjectPrefix*>(yard);
  radius=view->radius;
  Module *castle=yard->lookupModule(CastleBehavior::rva0003955DA());
  if(castle)radius=reinterpret_cast<Rva00395A60*>(castle)->rva00395A60();
  AsciiString name;name.format("BASE_FLAG_%d",startPos+1);view->name=name;
  player->onStructureCreated(0,yard);
  reinterpret_cast<Rva002A9BF2*>(player)->rva002A9D02(0,yard,0);
  pos.y-=view->width*0.5f;
  pos.z=TheTerrainLogic->getGroundHeight(pos.x,pos.y,0);
 }
 if(rally){pos=rally->position;pos.z=TheTerrainLogic->getGroundHeight(pos.x,pos.y,0);}
 Coord3D origin=start->position;
 if(yard)origin=*reinterpret_cast<const Coord3D*>((const char*)yard+0x38);
 for(int i=0;i<10;++i) {
  const AsciiString &unitTemplate=*reinterpret_cast<const AsciiString*>(reinterpret_cast<Rva001FD19E*>(const_cast<PlayerTemplate*>(pt))->rva001FD19E(i));
  AsciiString unitName(unitTemplate);
  if(unitName.isEmpty())continue;
  Coord3D offset;reinterpret_cast<Rva001FD2D9*>(const_cast<PlayerTemplate*>(pt))->rva001FD2D9(&offset,i);
  Coord3D zero={0.0f,0.0f,0.0f};Coord3D objPos;
  if(offset==zero)objPos=pos;
  else {
   Vector3 direction(offset.x,offset.y,offset.z);direction.Normalize();
   Vector3 delta(1.0f,-1.0f,0.0f);delta*=WWMath::Inv_Sqrt(2.0f);
   Vector3 reference(0.0f,1.0f,0.0f);
   float angle=(float)acos(Vector3::Dot_Product(direction,reference));
   if(direction.X*reference.Y-direction.Y*reference.X<0.0f)angle*=-1.0f;
   delta.Rotate_Z(angle);delta*=offset.GetLength();
   objPos.x=delta.X;objPos.y=delta.Y;objPos.z=delta.Z;
   objPos.x+=origin.x;objPos.y+=origin.y;objPos.z+=origin.z;
  }
  FindPositionOptions options={0,radius,radius*1.4f,-99999.9f,10000000000.0f,0,0,0};
  reinterpret_cast<NetworkPartitionDispatch*>(ThePartitionManager)->update();
  Coord3D zero2={0.0f,0.0f,0.0f};
  bool found=(offset==zero2)?PartitionManager::findPositionAround(&objPos,&options,&objPos):true;
  if(found){Object *unit=placeObjectAtPosition(slotNum,unitName,&objPos,player,pt);if(unit)player->onUnitCreated(0,unit);}
 }
}

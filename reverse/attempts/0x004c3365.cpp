// ?doSpecialPowerAtLocation@OCLSpecialPower@@UAEXPBUCoord3D@@I@Z
// partial score=0.7981522575551262 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include /ICode/GameEngine/Source
// stlport
#include <vector>
#include <float.h>
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "Common/PartitionRangeQueryCallView.h"
class Player;
class Upgrade;
enum UpgradeStatusType { UPGRADE_COMPLETE=2 };
class UpgradeTemplate { public: char pad[4]; int type; };
class Player { public: Upgrade *rva002AE329(const UpgradeTemplate *,UpgradeStatusType,int); };
class UpgradeCenter { public: const UpgradeTemplate *findUpgrade(const AsciiString &) const; };
extern UpgradeCenter *TheUpgradeCenter;
class Object { public: char pad[0x38]; Coord3D pos; Player *getControllingPlayer() const; };
class ObjectFilter { public: bool isValid() const; int index; char rest[12]; };
class Rva000421C8 {
public: Rva000421C8():next(0){} virtual ~Rva000421C8(){} virtual bool allow(Object *)=0; virtual int getPlayerMask();
Rva000421C8 *next;
};
class Rva002614ECFilter:public Rva000421C8 {
public: Rva002614ECFilter(const void *what,Player *player,bool match):what(what),player(player),match(match){}
virtual bool allow(Object *); const void *what; Player *player; bool match;
};
extern PartitionManager *ThePartitionManager;
class Pathfinder { public: bool AdjustToNearestValidCell(Coord3D *); };
class AI { public: char pad[0x10]; Pathfinder *pathfinder; };
extern AI *TheAI;
struct Waypoint { char pad[0xC]; Coord3D pos; };
class TerrainLogic {
public:
virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual void s18();virtual void s1C();virtual void s20();virtual void s24();virtual void s28();virtual void s2C();virtual void s30();
virtual Coord3D findClosestEdgePoint(const Coord3D *);
virtual Coord3D findFarthestEdgePoint(const Coord3D *);
virtual void s3C();virtual void s40();virtual void s44();virtual void s48();virtual void s4C();virtual void s50();virtual void s54();virtual void s58();virtual void s5C();virtual void s60();virtual void s64();virtual void s68();virtual void s6C();virtual void s70();virtual void s74();virtual void s78();virtual void s7C();virtual void s80();virtual void s84();
virtual Waypoint *getWaypoint(const AsciiString &);
};
extern TerrainLogic *TheTerrainLogic;
class ObjectCreationList {public:void create(void*,void*,void*,int);void create(void*,void*,void*,void*,int);
 static inline void create(ObjectCreationList *ocl, Object *owner, Coord3D *a, const Coord3D *b,int c) { if(ocl)ocl->create(owner,a,(void*)b,c); }
 static inline void create(ObjectCreationList *ocl, Object *owner, Coord3D *a, const Coord3D *b,void *c,int d) { if(ocl)ocl->create(owner,a,(void*)b,c,d); }
};
struct OCLData { char pad[0x8C]; int location; _STL::vector<AsciiString> upgrades; ObjectFilter filter; };
class Module {public:virtual ~Module(); protected:const OCLData *data;};
class ObjectModule:public Module {protected:Object *object;};
class BehaviorModuleInterface { public:virtual void behaviorSlot0();};
class BehaviorModule:public ObjectModule,public BehaviorModuleInterface {};
class SpecialPowerModuleInterface {public:virtual void doSpecialPower(unsigned)=0; virtual void doSpecialPowerAtObject(Object*,unsigned)=0; virtual void doSpecialPowerAtLocation(const Coord3D*,unsigned)=0;};
class SpecialPowerModule:public BehaviorModule,public SpecialPowerModuleInterface {public:virtual void doSpecialPower(unsigned);virtual void doSpecialPowerAtObject(Object*,unsigned);virtual void doSpecialPowerAtLocation(const Coord3D*,unsigned);};
class Rva004C31A8ScienceSelector {public:unsigned select() const;};
class OCLSpecialPower:public SpecialPowerModule {public:virtual void doSpecialPowerAtLocation(const Coord3D*,unsigned);};
void OCLSpecialPower::doSpecialPowerAtLocation(const Coord3D *location,unsigned flags)
{
 if(!location)return;
 SpecialPowerModule::doSpecialPowerAtLocation(location,flags);
 ObjectCreationList *ocl=(ObjectCreationList *)((const Rva004C31A8ScienceSelector*)this)->select();
 const OCLData *modData=data;
 Coord3D creation;
 switch(modData->location) {
 case 0:
  creation=TheTerrainLogic->findClosestEdgePoint(&object->pos);
  TheAI->pathfinder->AdjustToNearestValidCell(&creation);
  ObjectCreationList::create(ocl,object,&creation,location,0);
  break;
 case 1:
  creation=TheTerrainLogic->findClosestEdgePoint(location);
  TheAI->pathfinder->AdjustToNearestValidCell(&creation);
  ObjectCreationList::create(ocl,object,&creation,0,0);
  break;
 case 2:
  creation=TheTerrainLogic->findClosestEdgePoint(location);
  TheAI->pathfinder->AdjustToNearestValidCell(&creation);
  ObjectCreationList::create(ocl,object,&creation,location,0);
  break;
 case 3:
  creation=*location;
  ObjectCreationList::create(ocl,object,&creation,0,0);
  break;
 case 4:
  creation.x=location->x;creation.y=location->y;creation.z=location->z;
  ObjectCreationList::create(ocl,object,&creation,location,0,0);
  break;
 case 5:
  creation=*location;creation.z+=300.0f;
  ObjectCreationList::create(ocl,object,&creation,0,0);
  break;
 case 6:
  creation=TheTerrainLogic->findFarthestEdgePoint(location);creation.z+=300.0f;
  TheAI->pathfinder->AdjustToNearestValidCell(&creation);
  ObjectCreationList::create(ocl,object,&creation,location,0);
  break;
 case 7: {
  Waypoint *points[4];
  points[0]=TheTerrainLogic->getWaypoint(AsciiString("TopArmySpawnPoint"));
  points[1]=TheTerrainLogic->getWaypoint(AsciiString("BottomArmySpawnPoint"));
  points[2]=TheTerrainLogic->getWaypoint(AsciiString("LeftArmySpawnPoint"));
  points[3]=TheTerrainLogic->getWaypoint(AsciiString("RightArmySpawnPoint"));
  int nearest=-1;float distance=99999.0f;
  for(int i=0;i<4;++i){Waypoint *point=points[i];if(point) {
    Coord3D diff;diff.x=point->pos.x-location->x;diff.y=point->pos.y-location->y;diff.z=point->pos.z-location->z;
    float d=diff.GetLengthEstimate2D();if(d<distance){distance=d;nearest=i;}}
  }
  if(nearest>=0){creation=points[nearest]->pos;creation.z+=300.0f;ObjectCreationList::create(ocl,object,&creation,location,0);}
  break;}
 case 8: {
  creation.x=location->x;creation.y=location->y;creation.z=location->z;
  Object *secondary=0;
  if(modData->filter.isValid()) {
   Rva002614ECFilter filter(&modData->filter,object->getControllingPlayer(),true);
   secondary=ThePartitionManager->getClosestObject(location,FLT_MAX,0,&filter);
  }
  if(secondary)ObjectCreationList::create(ocl,object,&creation,&secondary->pos,0);
  else ObjectCreationList::create(ocl,object,&creation,0,0);
  break;}
 }
 _STL::vector<AsciiString> upgrades=modData->upgrades;
 for(unsigned i=0;i<upgrades.size();++i) {
  const UpgradeTemplate *up=TheUpgradeCenter->findUpgrade(upgrades[i]);
  if(!up)return;
  if(up->type==0){Player *player=object->getControllingPlayer();player->rva002AE329(up,UPGRADE_COMPLETE,0);}
 }
}

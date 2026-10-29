// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include /ICode/GameEngine/Source
// stlport
// OCLSpecialPower::doSpecialPowerAtLocation, native RVA 004C3365.
// The code is 1051 bytes through 004C3780; the nine-entry switch table
// extends the complete emitted body to 004C37A4 (1087 bytes).
// WorldBuilder 0125D230 supplies the name, module offsets and nine modes.
// Zero Hour OCLSpecialPower.cpp at BFME1 cee35b7d8ca077d7255f1c39cb69e9fd9627aa85
// supplies the semantic guide and farthest-edge case ordering. Retail decides
// the no-angle ABI, creation arguments, adjustment and upgrade behavior.
// Keeping the real length helper visible lets cl reuse the distance local's
// storage for the object filter, restoring the 8C frame without barriers.
#include <vector>
#include <float.h>
#include <math.h>
// AsciiString dtor declaration-only: ??_GAsciiString calls the rowed out-of-line copy 0x0048BA39
#define BFME_ASCII_DTOR_DECL
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "Common/PartitionRangeQueryCallView.h"
// Declaration-only: the vector<AsciiString> copy/dtor and the __uninitialized_copy<AsciiString> copy
// are emitted by their owner units (HelixContain.cpp, StlportAsciiStringVectorDtor.cpp, AsciiStringUninitializedCopy.cpp).
namespace _STL {
template <> AsciiString *__uninitialized_copy<const AsciiString *, AsciiString *>(const AsciiString *, const AsciiString *, AsciiString *, __false_type const &);
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> vector<AsciiString, allocator<AsciiString> >::vector(const vector<AsciiString, allocator<AsciiString> > &);
}
struct OCLDiffCoord:Coord3D {
 OCLDiffCoord() {}
};
inline __declspec(noinline) float Coord3D::GetLengthEstimate2D() const {
 if(fabs(x)>fabs(y)) return (float)(fabs(x)+0.25f*fabs(y));
 return (float)(fabs(y)+0.25f*fabs(x));
}
class Player;
class Upgrade;
enum UpgradeStatusType { UPGRADE_COMPLETE=2 };
class UpgradeTemplate { public: char pad[4]; int type; };
class Player { public: Upgrade *addUpgrade(const UpgradeTemplate *,UpgradeStatusType,int); };
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
class AI { public: char pad[0x10]; Pathfinder *pathfinder; Pathfinder *getPathfinder() { return pathfinder; } };
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
 static inline void create(ObjectCreationList *ocl, Object *owner, Coord3D *primary, const Coord3D *secondary,void *c,int d) { if(ocl)ocl->create(owner,primary,(void*)secondary,c,d); }
};
struct OCLData { char pad[0x8C]; int location; _STL::vector<AsciiString> upgrades; ObjectFilter filter; };
#include "../../../../Include/Common/Module.h"
#include "../../../../Include/Common/ObjectModule.h"
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
 const OCLData *modData=reinterpret_cast<const OCLData *>(getModuleData());
 Coord3D creation;
 switch(modData->location) {
 case 0:
  creation=TheTerrainLogic->findClosestEdgePoint(&getObject()->pos);
  TheAI->getPathfinder()->AdjustToNearestValidCell(&creation);
  ObjectCreationList::create(ocl,getObject(),&creation,location,0);
  break;
 case 1:
  creation=TheTerrainLogic->findClosestEdgePoint(location);
  TheAI->getPathfinder()->AdjustToNearestValidCell(&creation);
  ObjectCreationList::create(ocl,getObject(),&creation,0,0);
  break;
 case 2:
  creation=TheTerrainLogic->findClosestEdgePoint(location);
  TheAI->getPathfinder()->AdjustToNearestValidCell(&creation);
  ObjectCreationList::create(ocl,getObject(),&creation,location,0);
  break;
 case 6:
  creation=TheTerrainLogic->findFarthestEdgePoint(location);
  creation.z+=300.0f;
  TheAI->getPathfinder()->AdjustToNearestValidCell(&creation);
  ObjectCreationList::create(ocl,getObject(),&creation,location,0);
  break;
 case 3:
  creation=*location;
  ObjectCreationList::create(ocl,getObject(),&creation,0,0);
  break;
 case 4:
  creation.x=location->x;creation.y=location->y;creation.z=location->z;
  ObjectCreationList::create(ocl,getObject(),&creation,location,0,0);
  break;
 case 5:
  creation=*location;creation.z+=300.0f;
  ObjectCreationList::create(ocl,getObject(),&creation,0,0);
  break;
 case 7: {
  Waypoint *points[4];
  points[0]=TheTerrainLogic->getWaypoint(AsciiString("TopArmySpawnPoint"));
  points[1]=TheTerrainLogic->getWaypoint(AsciiString("BottomArmySpawnPoint"));
  points[2]=TheTerrainLogic->getWaypoint(AsciiString("LeftArmySpawnPoint"));
  points[3]=TheTerrainLogic->getWaypoint(AsciiString("RightArmySpawnPoint"));
  int nearest=-1;float distance=99999.0f;
  for(int i=0;i<4;++i){Waypoint *point=points[i];if(point) {
    OCLDiffCoord diff; diff.x=point->pos.x;diff.y=point->pos.y;diff.z=point->pos.z;diff.x-=location->x;diff.y-=location->y;diff.z-=location->z;
      float d=diff.GetLengthEstimate2D();if(d<distance){distance=d;nearest=i;}}
  }
  if(nearest>=0){creation=points[nearest]->pos;creation.z+=300.0f;ObjectCreationList::create(ocl,getObject(),&creation,location,0);}
  break;}
 case 8: {
  creation.x=location->x;creation.y=location->y;creation.z=location->z;
  Object *secondary=0;
  if(modData->filter.isValid()) {
   Rva002614ECFilter filter(&modData->filter,getObject()->getControllingPlayer(),true);
   secondary=ThePartitionManager->getClosestObject(location,FLT_MAX,0,&filter);
  }
  if(secondary)ObjectCreationList::create(ocl,getObject(),&creation,&secondary->pos,0);
  else ObjectCreationList::create(ocl,getObject(),&creation,0,0);
  break;}
 }
 _STL::vector<AsciiString> upgrades=modData->upgrades;
 for(unsigned i=0;i<upgrades.size();++i) {
  const UpgradeTemplate *up=TheUpgradeCenter->findUpgrade(upgrades[i]);
  if(!up)return;
  if(up->type==0){Player *player=getObject()->getControllingPlayer();player->addUpgrade(up,UPGRADE_COMPLETE,0);}
 }
}

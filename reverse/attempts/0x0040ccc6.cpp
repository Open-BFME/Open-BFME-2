// ?getSpawnPositions@ArmySummary@@QAE_NHPAUCoord3D@@0_N@Z
// partial score=0.96 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /GX /MD /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/GameLogic/System /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// stlport
#include "ArmyPlacerWaypoints.h"
#include <vector>
#define _OPERATOR_NEW_DEFINED_
#include "vector3.h"
#include <vector>
#include "ascii_string.h"
#define BFME_SNAPSHOT_NAME_SLOT 1
#include "Common/Snapshot.h"
extern "C" void __cdecl free(void*);
struct TargetRef00217D4C { void* vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct Rva004F69C3Target { unsigned char unknown0[4]; AsciiString templateName; unsigned char opaque[0xAC-8]; TargetRef00217D4C ref; };
// Target lookup2D06CA and the following byte test prove only this flag offset.
class ThingTemplate { public: unsigned char opaque[0x113]; unsigned char flags113; };
class ThingFactory { public: const ThingTemplate* findTemplate(const AsciiString&); };
extern ThingFactory* TheThingFactory;
struct Rva004F69C3 { int key; Rva004F69C3Target* value; ~Rva004F69C3(); };
namespace _STL { template<> vector<Rva004F69C3>::iterator vector<Rva004F69C3>::erase(iterator); }
// The existing 40E0EB provider destroys this same eight-byte entry range.
class Rva0040E0EB : public _STL::vector<Rva004F69C3> { public: ~Rva0040E0EB(); };
class Rva0040D8B8Listener { public: virtual void slot0(); virtual void notify(void*); };
class Rva0040D8B8List { public: void forEach(void(Rva0040D8B8Listener::*)(void*),void*); };
class Rva0040D8D6Listener {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void removed(void*,int); virtual void removing(void*,int);
};
class Rva0040D8D6List {
public: void forEach(void(Rva0040D8D6Listener::*)(void*,int),void*,int);
public: ~Rva0040D8D6List() { if(begin) free(begin); }
private: void *begin,*end,*limit; unsigned int index;
};
struct Rva0040DD3ARef {
 Rva004F69C3Target* value;
 Rva0040DD3ARef():value(0){}
 Rva0040DD3ARef(Rva004F69C3Target* p):value(p){if(value)++value->ref.references;}
 Rva0040DD3ARef(const Rva0040DD3ARef& x):value(x.value){if(value)++value->ref.references;}
 ~Rva0040DD3ARef(){if(value)ReleaseTreeHintRef00217D4C(&value->ref);}
};
// Existing 532803 provider view: twelve-byte vector of opaque four-byte
// words, with the same observed range-erasure ABI. Element purpose unknown.
class BfmeIntVecG {
public:
 void bfmeErase(int*,int*);
 __forceinline void clear() { bfmeErase(begin,end); }
 ~BfmeIntVecG() { if(begin) free(begin); }
 int *begin,*end,*limit;
};
class Rva0040CB3AIndexedField { public: int find(int key) const; };
class ArmySummary : public Snapshot, public Rva0040D8D6List {
public:
 virtual ~ArmySummary();
 virtual const char *GetSnapshotName() const;
 Rva0040DD3ARef RemoveEntry(int);
 Rva0040DD3ARef rva0040E672(int);
 void rva0040DED9();
 void rva0040DE16();
 bool getSpawnPositions(int, Coord3D*, Coord3D*, bool);
private:
 bool flag14;
 unsigned char pad15[3];
 AsciiString name18;
 int at1C;
 AsciiString name20;
 unsigned char gap[0x3C-0x24];
 int at3C;
 Rva0040E0EB entries;
 BfmeIntVecG words4C;
 unsigned char gap58[0x64-0x58];
 AsciiString name64;
};

struct Rva002B488EResult;
struct Rva002B3740Item;
class Rva002E2903Player;
class Rva003F468D;
class Rva0020E6B7RegionManager { public: Rva003F468D *rva0020E6B7(); };
class Rva002BA8F1Logic {
public:
 Rva002B488EResult *rva002B488E(int);
 Rva002B3740Item *rva002B2B2D();
 Rva002E2903Player *find(int,unsigned*);
 unsigned char unknown[0xb0];
 Rva0020E6B7RegionManager *manager;
 Rva0020E6B7RegionManager *getManager()const{return manager;}
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva0020E89C;
class Rva00318C8DOwner { public: Rva0020E89C *rva00318C8D(); };
class Player;
class PlayerList { public: Player *Rva002A7A6F(int); };
extern PlayerList *ThePlayerList;
class LivingWorldBattle { public: int rva003F4752(void*); };
struct ArmySpawnBattleSide { unsigned char bytes[28]; };
class Rva003F468D {
public: int rva003F4DAE(int);
 unsigned char unknown[0x18];
 ArmySpawnBattleSide *first,*last;
 unsigned size()const{return unsigned(last-first);}
};
class Rva002E071E { public: int rva002E0BC0(int); };
struct ArmySpawnRegion { unsigned char unknown[0x13c]; int owner; int getOwner()const{return owner;} };
class Rva0037F57E { public: Rva0037F57E(); virtual ~Rva0037F57E(); };

bool ArmySummary::getSpawnPositions(int playerId, Coord3D *spawn, Coord3D *gather, bool reinforcement)
{
 Rva002B488EResult *army=reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->rva002B488E(at1C);
 if(!army)return false;
 Rva0020E89C *armyRegion=reinterpret_cast<Rva00318C8DOwner*>(army)->rva00318C8D();
 if(!armyRegion)return false;
 Rva002B3740Item *played=reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->rva002B2B2D();
 if(!played)return false;
 Player *localPlayer=ThePlayerList->Rva002A7A6F(playerId);
 if(!localPlayer)return false;
 Rva002E2903Player *player=reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->find(playerId,0);
 if(!player)return false;
 Rva003F468D *battle=reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->getManager()->rva0020E6B7();
 if(!battle)return false;
 int side=reinterpret_cast<LivingWorldBattle*>(battle)->rva003F4752(player);
 if(side<0)return false;
 bool result=false, usedStart=false;
 Rva0037F57E storage;
 ArmyPlacer *placer=reinterpret_cast<ArmyPlacer*>(&storage);
 bool normal=battle->size()==2 && battle->rva003F4DAE(0)==1 && battle->rva003F4DAE(1)==1;
 bool atHome=reinterpret_cast<void*>(armyRegion)==played;
 if(normal) {
  int owner=reinterpret_cast<ArmySpawnRegion*>(played)->getOwner();
  if(owner==-1)result=placer->GetSpawnPointInFarthestPair(reinterpret_cast<Rva0037F90FInput*>(played),side,spawn,gather);
  else if((unsigned char)reinterpret_cast<Rva002E071E*>(player)->rva002E0BC0(owner)) {
   if(!reinforcement){result=placer->GetStartPosWaypointLocations(0,spawn,gather);usedStart=true;}
   else result=placer->GetDefenderReinforcementWaypointLocations(spawn,gather);
  } else result=placer->GetFarthestSpawnPointFromPlayerStart(reinterpret_cast<Rva0037F90FInput*>(played),0,spawn,gather);
 } else if(atHome) {
  if(!reinforcement){result=placer->GetStartPosWaypointLocations(0,spawn,gather);usedStart=true;}
  else result=placer->GetDefenderReinforcementWaypointLocations(spawn,gather);
 } else result=placer->GetWalkOnWaypointLocations(reinterpret_cast<Rva0037F7B6Record*>(armyRegion),spawn,gather);
 if(result && !reinforcement && !usedStart) {
  Vector3 direction(gather->x-spawn->x,gather->y-spawn->y,gather->z-spawn->z);
  direction.Normalize();
  *spawn=*gather;
  float newZ=spawn->z;
  float newY=spawn->y+direction.Y*10.f;
  float newX=spawn->x+direction.X*10.f;
  gather->x=newX;gather->y=newY;gather->z=newZ;
 }
 if(!result)result=placer->GetStartPosWaypointLocations(1,spawn,gather);
 return result;
}

// cl: /O1 /Oy- /G7 /arch:SSE /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// ?Rva00506CF5@@YA?AUCoord3D@@PAXPAU1@@Z
// Retail 0x00506CF5..0x00506FE9 (756 bytes, cdecl, Coord3D returned through
// the hidden pointer). AIBaseBuilder's home point: sole caller the
// AIBaseBuilder ctor 0x005070E9 (m_28 = Rva00506CF5(m_08, &m_18)).
// In skirmish (TheGameLogic +0x114 == 3) it takes the player's slot
// (rowed 0x00506C82) and returns the Player_%d_Start waypoint (rowed
// 0x00506CC3) dropped to the ground (TheTerrainLogic slot 6) or else the
// caller's point when it is set; otherwise it asks the living-world logic
// (rowed 0x002B323C) for the player's army summaries and the first
// spawn position (pinned ArmySummary::getSpawnPositions 0x0040CCC6) and
// returns the nearest of Player_1..8_Start (skipping the first when the
// current battle's participant +0x14 is another army).
// WorldBuilder twin 0x01375140 has the same callees and measures the
// distance with Vector3::Distance2 (a copy-initialised temp = p1 - p2 then
// Length2); that inline shape is what keeps retail's (x*x + y*y) + z*z
// association and register order. The returns copy result member-wise
// at each return site, so Coord3D here carries a user copy constructor.
// class-gate: allow Coord3D proved codegen view: retail copies the returned Coord3D member-wise (movss) separately at each of the three return sites through a user copy constructor; the canonical data-only header's trivial copy merges the returns into one block move (657 bytes instead of 756)
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "ascii_string.h"

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
 Coord3D(){}
 Coord3D(const Coord3D &p){x=p.x;y=p.y;z=p.z;}
	bool equals(const Coord3DBase &that) const;
	void set(const Coord3DBase *that) { x = that->x; y = that->y; z = that->z; }
};

extern Coord3DBase Gen00DD0870;

// WWMath Vector3's Distance2 and Length2 as the WorldBuilder twin calls them.
struct HomeVector3
{
	float X, Y, Z;
	HomeVector3() {}
	HomeVector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	HomeVector3(const Coord3DBase &c) { X = c.x; Y = c.y; Z = c.z; }
	float Length2() const { return X * X + Y * Y + Z * Z; }
	friend __forceinline HomeVector3 operator-(const HomeVector3 &a, const HomeVector3 &b) { return HomeVector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z); }
	static __forceinline float Distance2(const HomeVector3 &p1, const HomeVector3 &p2) { HomeVector3 temp = p1 - p2; return temp.Length2(); }
};

class Waypoint
{
public:
	const AsciiString &getName() const { return m_name; }
 const Coord3DBase &getLocation()const{return m_location;}
	Waypoint *getNext() const { return m_pNext; }
private:
	int m_00;
	int m_04;
	AsciiString m_name;		// +0x08
	Coord3DBase m_location;	// +0x0C
	int m_18;
	Waypoint *m_pNext;		// +0x1C
};

class Region3D;
class TerrainLogic
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual float getGroundHeight(float,float,Coord3D*); virtual void v07();
};

extern TerrainLogic *TheTerrainLogic;

Waypoint *Rva00506CC3FindWaypoint(const AsciiString &);
struct Rva00506C82Arg {char pad[0x50];int key;};
class GameSlot {public:char pad[0x10];int start;};
GameSlot*Rva00506C82Find(const Rva00506C82Arg*);
class GameLogic;extern GameLogic*TheGameLogic;
struct TacticGameLogicView {char pad[0x114];int mode;};
struct TacticPlayerView {char pad[0x3ac];int army;__forceinline int getArmyID()const{return army;}};
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class Rva003F468D;
class Rva0020E6B7RegionManager {public:Rva003F468D*rva0020E6B7();};
struct TacticWorldView {char pad[0xb0];Rva0020E6B7RegionManager*manager;};
struct TacticBattleParticipantView {char pad[0x14];int army;};
class LivingWorldBattle {public:void *rva003F4D09();};
class Rva0040D701ArmySummary;
class ArmySummary {public:bool getSpawnPositions(int,Coord3D*,Coord3D*,bool);};
class Rva002BA8F1Logic {public:void rva002B323C(_STL::vector<Rva0040D701ArmySummary*>*,int);};
Coord3D Rva00506CF5(void *owner,Coord3D *point) {
 Coord3D result;result.set(&Gen00DD0870);
 if(((TacticGameLogicView*)TheGameLogic)->mode==3) {
  GameSlot*slot=Rva00506C82Find((Rva00506C82Arg*)owner);
  if(slot) {
   int start=slot->start;AsciiString name;name.format("Player_%d_Start",start+1);
   Waypoint *way=Rva00506CC3FindWaypoint(name);
   if(way){result=*(const Coord3D*)&way->getLocation();result.z=TheTerrainLogic->getGroundHeight(result.x,result.y,0);return result;}
  }else if(point&&!point->equals(Gen00DD0870)){result=*point;}
 }else {
  float bestDistance=0.0f;Waypoint*best=0;
  bool found=false;
  _STL::vector<Rva0040D701ArmySummary*>armies;
  ((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B323C(&armies,((TacticPlayerView*)owner)->getArmyID());
  Coord3D position,other;
  Rva0040D701ArmySummary**end=armies.end();
  for(Rva0040D701ArmySummary**it=armies.begin();it!=end&&!found;++it) {
   int armyID=((TacticPlayerView*)owner)->getArmyID();
   if(((ArmySummary*)*it)->getSpawnPositions(armyID,&position,&other,false))found=true;
  }
  if(found){
   TacticBattleParticipantView*p=(TacticBattleParticipantView*)((LivingWorldBattle*)((TacticWorldView*)TheLivingWorldLogic)->manager->rva0020E6B7())->rva003F4D09();
   bool skipFirst=p&&((TacticPlayerView*)owner)->getArmyID()!=p->army;
   for(int i=skipFirst?1:0;i<8;++i){
    AsciiString name;name.format("Player_%d_Start",i+1);
    Waypoint*way=Rva00506CC3FindWaypoint(name);
    if(way){
     float distance=HomeVector3::Distance2(HomeVector3(way->getLocation()),HomeVector3(position));
     if(!best||distance<bestDistance){best=way;bestDistance=distance;}
    }
   }
   if(best){result=*(const Coord3D*)&best->getLocation();result.z=TheTerrainLogic->getGroundHeight(result.x,result.y,0);return result;}
  }
 }
 return result;
}

// ?Rva00506CF5@@YA?AUCoord3D@@PAXPAU1@@Z
// partial score=0.989418 date=2026-10-09
// cl: /O1 /Oy- /G7 /arch:SSE /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// The skirmish-AI object behind vtable 0x00863FAC, newed by 0x004EC430 in the
// AITactic.cpp range (its assert path is at 0x00862968; the neighbouring
// asserts at 0x005061FD.. name AITacticsGenerator.cpp). WorldBuilder and the matched
// collaborator providers identify AIBaseBuilder and its owned AIBase objects.
// The measured layout below is unchanged (Rva00506B74CopyCompare.cpp).
//
// Target evidence for the layout:
//   +0x00 base Rva00506B1B (ctor 0x00506B1B, dtor 0x00506B28, vtable
//         0x00863F9C with __purecall in slots 1 and 2)
//   +0x08 the pointer the ctor is given
//   +0x0C vector of owned pointers: slot 2 (0x005071A1) runs each through
//         dtor 0x005ADA40 plus operator delete, then erase 0x0031BD55
//   +0x18 Coord3D, +0x24 flag, +0x28 Coord3D, both points seeded from the
//         -1 triple at 0x00DD0870 (Gen00DD0870)
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "ascii_string.h"
#include "vector3.h"

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
 Coord3D(){}
 __forceinline float lengthSq()const{return x*x+y*y+z*z;}
 Coord3D(const Coord3D &p){x=p.x;y=p.y;z=p.z;}
	bool equals(const Coord3DBase &that) const;
	void set(const Coord3DBase *that) { x = that->x; y = that->y; z = that->z; }
};

extern Coord3DBase Gen00DD0870;

class Rva005AD9C0Hit
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3(void *arg);
};

// BFME2's Xfer: operator== overloads, grouped by cl at the first overload
// slot in reverse declaration order (Rva004E0513Xfer.cpp has the same view).
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Rva00506FE9Hit;

// Legacy vector spelling is an opaque pointer handle. Its existing container
// ABI is retained; only AIBase objects are constructed and accessed through it.
class Rva005ADA40;
class AIBase
{
public:
	AIBase(unsigned int index, void *owner);
	~AIBase();
	void DoXfer(Xfer *xfer);
	void loadBestFitTemplate(Coord3D *point, float angle, int more);
	void rva005AD99C(const AsciiString &name, _STL::vector<Rva00506FE9Hit *> *hits);
	void rva005ADC63();
	Rva005AD9C0Hit *rva005AD9C0(void *arg);
private:
	unsigned char m_data[0x2C];	// new'd at 0x2C by 0x005073D6
};

class Rva00506B1B
{
public:
	Rva00506B1B();
	virtual ~Rva00506B1B();
	virtual void v1() = 0;
	virtual void v2() = 0;
private:
	bool m_04;
};

// 0x00506FE9's collaborators. Object and RebuildHoleBehaviorInterface stay
// opaque; the views below carry only what that body reads.
class Object;
class RebuildHoleBehaviorInterface;

class RebuildHoleBehavior
{
public:
	static RebuildHoleBehaviorInterface *getRebuildHoleBehaviorInterfaceFromObject(Object *obj);
};

struct Rva00506FE9Template
{
	char m_pad00[0x64];
	AsciiString m_name;		// +0x64
};

class Rva00506FE9RebuildView
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual const Rva00506FE9Template *getRebuildTemplate();	// slot 3
};

struct Rva00506FE9ObjectView
{
	void *m_vptr;
	const Rva00506FE9Template *m_template;	// +0x04
	char m_pad08[0x74 - 8];
	int m_id;				// +0x74
};

class Rva00506FE9Hit
{
public:
	virtual void v0(); virtual void v1(); virtual void v2();
	virtual void v3(); virtual void v4(); virtual void v5();
	virtual void v6(void *owner, int flag);	// +0x18
	void rva0055ADBA(void *owner);
	float m_04;
	char m_pad08[0x24 - 8];
	int m_24;
};

struct Rva002A8B59Data
{
	char m_pad00[0x88];
	float m_88;
};

class Rva002A8F24
{
public:
	Rva002A8B59Data *rva002A8B59(void *owner);
};

extern Rva002A8F24 *g_00DFEEF8;

Coord3D __cdecl Rva00506CF5(void *owner, Coord3D *point);

class AIBaseBuilder : public Rva00506B1B
{
public:
	AIBaseBuilder(void *owner);
	virtual ~AIBaseBuilder();
	virtual void v1();
	virtual void v2();
	bool rva00506B74(Coord3D *out);
	void rva0050722A(Coord3D *point);
	void rva00506B96(const Coord3D *point);
	Rva005AD9C0Hit *rva00506BF7(void *arg);
	bool rva00506C39(void *arg);
	Rva005ADA40 *rva00506C64(unsigned int index);
	void postInit();
	void notifyBuildingDestroyed(Object *obj);
	void DoXfer(Xfer *xfer);
private:
	void *m_08;
	_STL::vector<Rva005ADA40 *> m_0C;
	Coord3D m_18;
	bool m_24;
	Coord3D m_28;
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

class TerrainLogic
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual float getGroundHeight(float,float,Coord3D*); virtual void v07();
	virtual void v08(); virtual void getExtent(Region3D *extent) const; virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32();
	virtual Waypoint *getFirstWaypoint();	// +0x84
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
class Rva003F468D {public:TacticBattleParticipantView*rva003F4D09();};
class Rva0040D701ArmySummary {public:bool rva0040CCC6(int,Coord3D*,Coord3D*,bool);};
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
   if((*it)->rva0040CCC6(armyID,&position,&other,false))found=true;
  }
  if(found){
   TacticBattleParticipantView*p=((TacticWorldView*)TheLivingWorldLogic)->manager->rva0020E6B7()->rva003F4D09();
   bool skipFirst=p&&((TacticPlayerView*)owner)->getArmyID()!=p->army;
   for(int i=skipFirst?1:0;i<8;++i){
    AsciiString name;name.format("Player_%d_Start",i+1);
    Waypoint*way=Rva00506CC3FindWaypoint(name);
    if(way){
     Coord3D delta;delta.x=way->getLocation().x-position.x;delta.y=way->getLocation().y-position.y;delta.z=way->getLocation().z-position.z;
     float distance=delta.lengthSq();
     if(!best||distance<bestDistance){best=way;bestDistance=distance;}
    }
   }
   if(best){result=*(const Coord3D*)&best->getLocation();result.z=TheTerrainLogic->getGroundHeight(result.x,result.y,0);return result;}
  }
 }
 return result;
}

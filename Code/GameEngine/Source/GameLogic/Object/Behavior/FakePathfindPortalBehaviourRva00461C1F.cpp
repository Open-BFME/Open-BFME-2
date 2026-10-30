// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// ?rva00461C1F@FakePathfindPortalBehaviour@@QAEXXZ
//
// Class views follow FakePathfindPortalBehaviour.cpp, this unit's TU: the
// UpdateModule base with two novtable interface bases at +0x20/+0x24
// (layout from the rowed ctor 0x461944).

#include "ascii_string.h"
#include "Coord3D.h"
struct Rva0087E650Bounds { Coord3D lo,hi; };
class GeometryInfo { public: void rva0087E650(Rva0087E650Bounds*); };
struct FakePortalOwnerView {
 char pad[0x38];Coord3D position;float angle;char pad48[0x74-0x48];unsigned id;
 char pad78[0x104-0x78];GeometryInfo *geometry;
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class Thing;
class ModuleData;
class Xfer;

class Waypoint
{
public:
	virtual ~Waypoint();
	void addLink(Waypoint *link);
	int getID() const { return m_id; }
private:
	int m_id;	// +0x04
};

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const = 0;
	void xfer(Xfer *xfer);

protected:
	const void *m_moduleData;	// +0x04
	FakePortalOwnerView *m_owner;	// +0x08
	const void *m_p0C;	// +0x0C
	const void *m_p10;	// +0x10
	unsigned char m_pad[0x20 - 0x14];
};

class __declspec(novtable) Rva00C42B50Iface
{
public:
	virtual void rva0046190A(void *arg) = 0;
};

class __declspec(novtable) Rva00C42B40Iface
{
public:
	virtual void slot0() = 0;
};

class __declspec(novtable) FakePathfindPortalBehaviour : public UpdateModule, public Rva00C42B50Iface,
	public Rva00C42B40Iface
{
public:
	FakePathfindPortalBehaviour(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual void rva0046190A(void *arg);
	void rva0046183B();
	void rva004618D4();
	Waypoint *rva00461A46(const Coord3D *point);
	void rva00461C1F();

protected:
	virtual void xfer(Xfer *xfer);

private:
	void regWaypointsWithPathfinder();

	enum { WAYPOINT_COUNT = 2 };
	Waypoint *m_28[WAYPOINT_COUNT];	// +0x28
	bool m_30;
	bool m_31;
	bool m_32;
	int m_34;
};

// Keep the MSVC float overloads local; their inlined operations stay retail-exact.
#define inline static inline
#include <math.h>
#undef inline

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05();
	virtual float getGroundHeight(float x, float y, Coord3D *normal);
	virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34();
	virtual Waypoint *getWaypointByID(int waypointID);
};

extern TerrainLogic *TheTerrainLogic;
static float s_fakePortalWaypointMargin=10.0f; // native .data RVA9C972C; descriptive name is inferred
// Native primary entry461C1F..461DB5 is independently decoded and reached
// from461DB5. Old no-boundary verdict used different bytes; current entry
// begins PUSH EBP. Geometry provider/BFME1 proves six-float bounds output.
void FakePathfindPortalBehaviour::rva00461C1F()
{
 if(m_30) return;
 float angle=m_owner->angle;
 Rva0087E650Bounds bounds;
 m_owner->geometry->rva0087E650(&bounds);
 float radius=bounds.lo.x;
 if(!(radius>0.0f)) radius=bounds.hi.x;
 struct PortalVector {
 float x,y,z;
 PortalVector(float a,float b,float c):x(a),y(b),z(c){}
 __forceinline void rotate(float ca,const float &sa) {
  float tmp_x=x;float tmp_y=y;
  x=ca*tmp_x-sa*tmp_y;
  y=sa*tmp_x+ca*tmp_y;
 }
 };
 PortalVector offset(radius+s_fakePortalWaypointMargin,0.0f,0.0f);
 float sine;
 offset.rotate((sine=sin(angle),cos(angle)),sine);
 struct PortalCoord : Coord3D { PortalCoord(const PortalVector &portalVector) {x=portalVector.x;y=portalVector.y;z=portalVector.z;} };
 PortalCoord point(offset);
 point.x+=m_owner->position.x;
 point.y+=m_owner->position.y;
 point.z=TheTerrainLogic->getGroundHeight(point.x,point.y,0);
 ((Waypoint**)m_28)[0]=rva00461A46(&point);
 point.x=0.0f-offset.x;point.y=0.0f-offset.y;point.z=0;
 point.x+=m_owner->position.x;
 point.y+=m_owner->position.y;
 point.z=TheTerrainLogic->getGroundHeight(point.x,point.y,0);
 ((Waypoint**)m_28)[1]=rva00461A46(&point);
 ((Waypoint**)m_28)[0]->addLink(((Waypoint**)m_28)[1]);
 ((Waypoint**)m_28)[1]->addLink(((Waypoint**)m_28)[0]);
 regWaypointsWithPathfinder();
 m_30=true;
}

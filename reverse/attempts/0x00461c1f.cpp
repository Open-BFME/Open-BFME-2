// ?rva00461C1F@FakePathfindPortalBehaviour@@QAEXXZ
// partial score=0.99 date=2026-10-09
// ?rva00461C1F@FakePathfindPortalBehaviour@@QAEXXZ
// partial score=0.96 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ??1FakePathfindPortalBehaviour@@UAE@XZ, retail 0x004619F2, 84 bytes
// (pinned; rowed deleting wrapper 0x00461C03). Stores
// five vtables (+0x00/+0x0C/+0x10/+0x20/+0x24), calls the helper 0x0046183B
// on this in EH state 0, then the opaque MI base dtor 0x0024A797, the only
// entry in retail's unwind map. The helper is pinned here under an address
// name from this call; its other caller 0x0046190A reaches it from the
// +0x20 interface. The +0x14..+0x1F words sit in the third base so the
// fourth and fifth vptrs land at +0x20/+0x24 (base layout as in
// Rva0024A797Derived.cpp; members after +0x28 follow the rowed ctor).
#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Waypoint { public:
 Waypoint(unsigned,AsciiString,const Coord3D*,AsciiString,AsciiString,AsciiString,bool,int,AsciiString);
 virtual ~Waypoint();
 void addLink(Waypoint*);
 char pad04[0xA8-4];bool flagA8,flagA9;char padAA[6];unsigned ownerID;char padB4[0xC0-0xB4];
};
struct FakePortalDataView { char pad[0x118];bool flag118,flag119; };
struct Rva0087E650Bounds { Coord3D lo,hi; };
class GeometryInfo { public: void rva0087E650(Rva0087E650Bounds*); };
struct FakePortalOwnerView {
 char pad[0x38];Coord3D position;float angle;char pad48[0x74-0x48];unsigned id;
 char pad78[0x104-0x78];GeometryInfo *geometry;
};
class Rva0024A797
{
public:
	virtual ~Rva0024A797();
protected:
 const FakePortalDataView *m_data;
 FakePortalOwnerView *m_owner;
};

class MiBase1
{
public:
	virtual void f1();
};

class FakePathfindPortalBehaviour_B2
{
public:
	virtual void f2();
private:
	int m_14;
	int m_18;
	int m_1C;
};

class FakePathfindPortalBehaviour_B3
{
public:
	virtual void f3();
};

class FakePathfindPortalBehaviour_B4
{
public:
	virtual void f4();
};

class FakePathfindPortalBehaviour : public Rva0024A797, public MiBase1, public FakePathfindPortalBehaviour_B2,
	public FakePathfindPortalBehaviour_B3, public FakePathfindPortalBehaviour_B4
{
public:
	virtual ~FakePathfindPortalBehaviour();
	void rva0046183B();
	void rva004618D4();
 Waypoint *rva00461A46(const Coord3D *point);
 void rva00461C1F();

private:
 void regWaypointsWithPathfinder();
	char m_28[8];
	bool m_30;
	bool m_31;
	bool m_32;
	int m_34;
};

FakePathfindPortalBehaviour::~FakePathfindPortalBehaviour()
{
	rva0046183B();
}

class AI;
extern AI *TheAI;

class Rva002E9042
{
public:
	void rva002E9042(void *arg);
};

class Rva004618D4Caller
{
public:
	void rva002E7023();
};

struct Rva004618D4AI
{
	char m_pad00[0x10];
	Rva002E9042 *m_p10;
};

// ?rva004618D4@FakePathfindPortalBehaviour@@QAEXXZ, retail 0x004618D4 (54B): forwards the two
// waypoints at +0x28/+0x2C to the TheAI+0x10 object, calls its no-argument helper through the
// local thiscall view, then clears the +0x32 flag.
void FakePathfindPortalBehaviour::rva004618D4()
{
	Rva002E9042 *obj = (*reinterpret_cast<Rva004618D4AI **>(&TheAI))->m_p10;
	obj->rva002E9042(*reinterpret_cast<void **>(m_28));
	obj = (*reinterpret_cast<Rva004618D4AI **>(&TheAI))->m_p10;
	obj->rva002E9042(*reinterpret_cast<void **>(m_28 + 4));
	reinterpret_cast<Rva004618D4Caller *>((*reinterpret_cast<Rva004618D4AI **>(&TheAI))->m_p10)->rva002E7023();
	m_32 = false;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f4@FakePathfindPortalBehaviour_B4@@UAEXXZ=??1Coord2D@@QAE@XZ")

class Rva002E6ECA { public: virtual void *destroy(unsigned); int get() const; };
typedef Rva002E6ECA Rva0046183BWaypoint;
void FakePathfindPortalBehaviour::rva0046183B()
{
 if(m_30) {
  Rva0046183BWaypoint **p=(Rva0046183BWaypoint**)m_28;
  for(int i=0;i<2;++i,++p) {
   Rva0046183BWaypoint *wp=*p;
   if(wp) {
    if((unsigned char)wp->get()) (*reinterpret_cast<Rva004618D4AI**>(&TheAI))->m_p10->rva002E9042(wp);
    ::operator delete(*p ? (*p)->destroy(0) : 0);
    *p=0;
   }
  }
  reinterpret_cast<Rva004618D4Caller*>((*reinterpret_cast<Rva004618D4AI**>(&TheAI))->m_p10)->rva002E7023();
  m_30=false;
 }
}

// Native461A46..461B1B RET4 allocatesC0 and calls proven Waypoint ctor282212.
// Five by-value strings and argument order come from that ctor provider;
// target fake-name literal and ownerB0/flagsA8/A9 establish this factory's role.
Waypoint *FakePathfindPortalBehaviour::rva00461A46(const Coord3D *point)
{
 const FakePortalDataView *data=m_data;
 Waypoint *wp=new Waypoint(0x7ffffffe,AsciiString("#fakepathfindportal_wp"),point,
  AsciiString::TheEmptyString,AsciiString::TheEmptyString,AsciiString::TheEmptyString,
  false,7,AsciiString::TheEmptyString);
 wp->ownerID=m_owner->id;
 wp->flagA8=data->flag118;
 wp->flagA9=data->flag119;
 return wp;
}

extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
class TerrainLogic { public:
 virtual void slot0();virtual void slot1();virtual void slot2();
 virtual void slot3();virtual void slot4();virtual void slot5();
 virtual float getGroundHeight(float,float,Coord3D*);
};
extern TerrainLogic *TheTerrainLogic;
static float s_fakePortalWaypointMargin=10.0f; // native .data RVA9C972C; descriptive name is inferred
// Native primary entry461C1F..461DB5 is independently decoded and reached
// from461DB5. Old no-boundary verdict used different bytes; current entry
// begins PUSH EBP. Geometry provider/BFME1 proves six-float bounds output.
// ?rva00461C1F@FakePathfindPortalBehaviour@@QAEXXZ present-unmatched
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
 offset.rotate((sine=(float)sin(angle),(float)cos(angle)),sine);
 struct PortalCoord : Coord3D { PortalCoord(const PortalVector &o) {x=o.x;y=o.y;z=o.z;} };
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

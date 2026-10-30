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
 char pad04[0xA8-4];bool flagA8,flagA9;char padAA[6];unsigned ownerID;char padB4[0xC0-0xB4];
};
struct FakePortalDataView { char pad[0x118];bool flag118,flag119; };
struct FakePortalOwnerView { char pad[0x74];unsigned id; };
class UpdateModule
{
public:
	virtual ~UpdateModule();
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

class FakePathfindPortalBehaviour : public UpdateModule, public MiBase1, public FakePathfindPortalBehaviour_B2,
	public FakePathfindPortalBehaviour_B3, public FakePathfindPortalBehaviour_B4
{
public:
	virtual ~FakePathfindPortalBehaviour();
	void rva0046183B();
	void rva004618D4();
 Waypoint *rva00461A46(const Coord3D *point);
private:
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
  Rva0046183BWaypoint **waypointSlot=(Rva0046183BWaypoint**)m_28;
  for(int i=0;i<2;++i,++waypointSlot) {
   Rva0046183BWaypoint *wp=*waypointSlot;
   if(wp) {
    if((unsigned char)wp->get()) (*reinterpret_cast<Rva004618D4AI**>(&TheAI))->m_p10->rva002E9042(wp);
    ::operator delete(*waypointSlot ? (*waypointSlot)->destroy(0) : 0);
    *waypointSlot=0;
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

// 0x004617CF (108 bytes): the Zero Hour module-finder pattern for this
// behaviour: a function-static NameKey for "FakePathfindPortalBehaviour"
// (TheNameKeyGenerator->nameToKey, 0x00148E1A), then the first module in the
// object's behaviour list (+0x244, null-terminated) whose module name key
// (slot 4) matches. Identity of the owner function is unproven.
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class BehaviorModule
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual NameKeyType getModuleNameKey() const;	// +0x10
};

struct FakePortalObjectView
{
	char pad[0x244];
	BehaviorModule **m_behaviors;	// +0x244
};

BehaviorModule *Rva004617CFFind(FakePortalObjectView *obj)
{
	static NameKeyType key = TheNameKeyGenerator->nameToKey("FakePathfindPortalBehaviour");
	for (BehaviorModule **behaviorModule = obj->m_behaviors; *behaviorModule; ++behaviorModule)
	{
		if ((*behaviorModule)->getModuleNameKey() == key)
			return *behaviorModule;
	}
	return 0;
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?f2@FakePathfindPortalBehaviour_B2@@UAEXXZ=?update@FakePathfindPortalBehaviour@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f3@FakePathfindPortalBehaviour_B3@@UAEXXZ=?rva0046190A@FakePathfindPortalBehaviour@@UAEXPAX@Z")

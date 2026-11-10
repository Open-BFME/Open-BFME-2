// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ??1FakePathfindPortalBehaviour@@UAE@XZ, retail 0x004619F2, 84 bytes
// (pinned; rowed deleting wrapper 0x00461C03). Stores
// five vtables (+0x00/+0x0C/+0x10/+0x20/+0x24), calls the helper 0x0046183B
// on this in EH state 0, then the opaque MI base dtor 0x0024A797, the only
// entry in retail's unwind map. The helper's other caller 0x0046190A
// reaches it from the +0x20 interface.
// UpdateModule owns +0x14..+0x1F; trailing interfaces land at +0x20/+0x24.
// Members after +0x28 follow the rowed constructor.
#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Include/GameLogic/Waypoint.h"
struct FakePortalDataView { char pad[0x118];bool flag118,flag119; };
struct FakePortalOwnerView { char pad[0x74];unsigned id; };

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class FakePathfindPortalBehaviour_B3
{
public:
	// +0x20 interface: retail table 0x00C42B50 slot 0 is the class's override 0x0046190A.
	virtual void rva0046190A(void *arg) = 0;
};

class FakePathfindPortalBehaviour_B4
{
public:
	virtual void f4();
};

class FakePathfindPortalBehaviour : public UpdateModule,
	public FakePathfindPortalBehaviour_B3, public FakePathfindPortalBehaviour_B4
{
public:
	virtual ~FakePathfindPortalBehaviour();
	virtual UpdateSleepTime update();
	// The +0x20 interface override (rowed at 0x0046190A in FakePathfindPortalBehaviour.cpp).
	virtual void rva0046190A(void *arg);
	void rva0046183B();
	void rva004618D4();
 Waypoint *rva00461A46(const Coord3D *point);
private:
	char m_28[8];
	bool m_30;
	bool m_31;
	bool m_32;
	int m_34;
public:
	// retail slot 4: the rowed ?getModuleNameKey@FakePathfindPortalBehaviour@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
public:
	// BehaviorModuleInterface table 0x00C42B60 (+0x0C): the receiver converted to the
	// class's own interface, the null-preserving casts retail folds across the module family.
	virtual CreateModuleInterface *getCreate();			// slot 3: retail 0x003730FC, the +0x24 create interface
	virtual DieModuleInterface *getDie();			// slot 7: retail 0x004543A9, the +0x20 die interface
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

#include "../../../../Include/Common/Rva004618D4Caller.h"

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
 const FakePortalDataView *data=reinterpret_cast<const FakePortalDataView *>(m_moduleData);
 Waypoint *wp=new Waypoint(0x7ffffffe,AsciiString("#fakepathfindportal_wp"),point,
  AsciiString::TheEmptyString,AsciiString::TheEmptyString,AsciiString::TheEmptyString,
  false,7,AsciiString::TheEmptyString);
 wp->m_fieldB0=reinterpret_cast<FakePortalOwnerView *>(m_object)->id;
 wp->m_fieldA8=data->flag118;
 wp->m_fieldA9=data->flag119;
 return wp;
}

// 0x004617CF (108 bytes): the Zero Hour module-finder pattern for this
// behaviour: a function-static NameKey for "FakePathfindPortalBehaviour"
// (TheNameKeyGenerator->nameToKey, 0x00148E1A), then the first module in the
// object's behaviour list (+0x244, null-terminated) whose module name key
// (slot 4) matches. Identity of the owner function is unproven.
enum NameKeyType { NAMEKEY_INVALID = 0 };
#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;


struct FakePortalObjectView
{
	char pad[0x244];
	BehaviorModule **m_behaviors;	// +0x244
};

BehaviorModule *findFakePathfindPortalBehaviour(FakePortalObjectView *obj)
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

// Slot 3 of FakePathfindPortalBehaviour's BehaviorModuleInterface table 0x00C42B60: retail 0x003730FC, the +0x24 create interface.
CreateModuleInterface *FakePathfindPortalBehaviour::getCreate()
{
	return reinterpret_cast<CreateModuleInterface *>(static_cast<FakePathfindPortalBehaviour_B4 *>(this));
}

// Slot 7 of FakePathfindPortalBehaviour's BehaviorModuleInterface table 0x00C42B60: retail 0x004543A9, the +0x20 die interface.
DieModuleInterface *FakePathfindPortalBehaviour::getDie()
{
	return reinterpret_cast<DieModuleInterface *>(static_cast<FakePathfindPortalBehaviour_B3 *>(this));
}

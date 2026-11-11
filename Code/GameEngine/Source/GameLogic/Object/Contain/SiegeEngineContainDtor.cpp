// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc  /D_CRTIMP=
// stlport
//
// ??1SiegeEngineContain@@UAE@XZ, retail 0x0047BF43, 207 bytes.
// SiegeEngineContain dtor over TransportContain base 0x11C with list<int> at +0x11C
// plus int at +0x120 plus bool at +0x124 plus map<int void*> at +0x128 plus list<int>
// at +0x134 for 0x138 total. Custom loop destroys contained Objects in +0x11C via
// rowed destroyObject 0x00242C09 after clearing containedBy +0x274 then member dtors
// in reverse via rowed list_base 0x004EC395 and tree dtor 0x00286852 then base dtor
// 0x00467E61. Identity via deleting dtor 0x0047C2D6 slot0 vtable 0x00C470F8 plus
// ModuleFactory SiegeEngineContain registration. Recipe per ctor TU layout with /EHs
// for list/tree EH states.
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include <map>

class Thing;
class ModuleData;
class Object;

struct Iface00 { virtual void f00(); unsigned char m_pad[8]; };
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };
struct Iface20 { virtual void f20(); };
struct Iface24 { virtual void f24(); };
#include "../../../../Include/Common/Iface28.h"
#include "../../../../Include/Common/Iface2C.h"
struct Iface30 { virtual void f30(); };
struct Iface34 { virtual void f34(); unsigned char m_pad[0xFC - 0x38]; };
struct IfaceFC { virtual void fFC(); };

class TransportContain
	: public Iface00
	, public Iface0C
	, public Iface10
	, public Iface20
	, public Iface24
	, public Iface28
	, public Iface2C
	, public Iface30
	, public Iface34
	, public IfaceFC
{
public:
	TransportContain(Thing *thing, const ModuleData *moduleData);
	virtual ~TransportContain();

private:
	unsigned char m_pad100[0x11C - 0x100];
};

class GameLogic;
extern GameLogic *TheGameLogic;

#include "../object.h"

#include "../../../Common/GameLogicObjectLookupView.h"

// map<ObjectID, int>: the tree family dtor 0x00286852 -> clear 0x00286656 ->
// erase 0x00286183 (one instantiation: the self-recursive erase is not ICF-folded;
// AITargetHeuristicEnemyStructure::findBestTarget 0x005735C6 keys it by object ID).
typedef _STL::map<ObjectID, int> ObjectIDIntMap;
class SiegeEngineContain : public TransportContain
{
public:
	SiegeEngineContain(Thing *thing, const ModuleData *moduleData);
	virtual ~SiegeEngineContain();
	virtual void f00();
	virtual void f20();
	virtual void f30();
	virtual void f34();
	void redeployOccupants();

private:
	_STL::list<int> m_list11C;
	int m_120;
	bool m_124;
	unsigned char m_pad125[3];
	ObjectIDIntMap m_map128;
	_STL::list<int> m_list134;
};

SiegeEngineContain::~SiegeEngineContain()
{
	for (_STL::list<int>::iterator it = m_list11C.begin(); it != m_list11C.end(); ) {
		Object *rider = (Object *)(*it);
		++it;
		rider->m_containedBy = 0;
		TheGameLogic->destroyObject(rider);
	}
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f0C@Iface0C@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f2C@Iface2C@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")

#include "../../../../Include/GameLogic/ContainmentListView.h"

// The shared rider-list worker (rowed at 0x00463A4D under its HordeTransportContain
// spelling) and OpenContain's slot-18 body, which this override reaches non-virtually.
class HordeTransportContain
{
public:
	void rva00463A4D(ContainmentList riders, int arg);	// 0x00463A4D
};
class OpenContain
{
	friend class SiegeEngineContain;
protected:
	virtual void redeployOccupants();		// 0x00464286
};

// Retail 0x0047C2F2..0x0047C322 (48B): the SiegeEngineContain twin of
// HordeSiegeEngineContain 0x0047D33A with the members 0x0C lower: the rider
// list at +0x11C is copied by value through 0x0036ADF9 into 0x00463A4D with
// the address at +0x128, then OpenContain's 0x00464286 runs (tail jump).
// Method name is address-derived.
void SiegeEngineContain::redeployOccupants()
{
	reinterpret_cast<HordeTransportContain *>(this)->rva00463A4D(*reinterpret_cast<ContainmentList *>(&m_list11C), (int)&m_map128);
	reinterpret_cast<OpenContain *>(this)->OpenContain::redeployOccupants();
}

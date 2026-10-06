// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
#include <map>

class Thing;
class ModuleData;
class Object;

struct Iface00 { virtual void f00(); unsigned char m_pad[8]; };
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };
struct Iface20 { virtual void f20(); };
struct Iface24 { virtual void f24(); };
struct Iface28 { virtual void f28(); };
struct Iface2C { virtual void f2C(); };
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

class Object
{
public:
	unsigned char m_pad274[0x274];
	Object *m_containedBy;
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

class SiegeEngineContain : public TransportContain
{
public:
	SiegeEngineContain(Thing *thing, const ModuleData *moduleData);
	virtual ~SiegeEngineContain();
	virtual void f00();
	virtual void f20();
	virtual void f30();
	virtual void f34();

private:
	_STL::list<int> m_list11C;
	int m_120;
	bool m_124;
	unsigned char m_pad125[3];
	_STL::map<int, void *> m_map128;
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

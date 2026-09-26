// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0SiegeEngineContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x0047C21E 184B.
// SiegeEngineContain behavior ctor over the pinned TransportContain base
// (0x00468559 thing plus data). Transport is OpenContain-derived with ten
// vptrs at +0/+0xC/+0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34/+0xFC for
// 0x11C total (rowed friend_new 0x0024B861 news 0x11C). Derived adds
// list<int> at +0x11C plus int at +0x120 plus bool at +0x124 plus
// map<int void*> at +0x128 plus list<int> at +0x134 for 0x138 total (rowed
// friend_new 0x0024BBB4 news 0x138). The ten stores are the compiler's own
// derived vptr installs (four slots differ from the base). Scalars zero in
// the body. Identity from ModuleFactory SiegeEngineContain registration
// plus sole raw callers friend_new 0x0024BBB4 and RiderChangeContain ctor
// 0x0047E273. BFME1 donor SiegeEngineContainCtorThunk.cpp gives the
// list-map-list plus int-bool concept with shifted offsets. Row supersedes
// ctor pin.
#include <list>
#include <map>

class Thing;
class ModuleData;

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
	~TransportContain();

private:
	unsigned char m_pad100[0x11C - 0x100];
};

class SiegeEngineContain : public TransportContain
{
public:
	SiegeEngineContain(Thing *thing, const ModuleData *moduleData);
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

// ?f00@SiegeEngineContain@@UAEXXZ present-unmatched
void SiegeEngineContain::f00() {}
// ?f20@SiegeEngineContain@@UAEXXZ present-unmatched
void SiegeEngineContain::f20() {}
// ?f30@SiegeEngineContain@@UAEXXZ present-unmatched
void SiegeEngineContain::f30() {}
// ?f34@SiegeEngineContain@@UAEXXZ present-unmatched
void SiegeEngineContain::f34() {}

SiegeEngineContain::SiegeEngineContain(Thing *thing, const ModuleData *moduleData)
	: TransportContain(thing, moduleData)
	, m_list11C()
	, m_map128()
	, m_list134()
{
	m_120 = 0;
	m_124 = false;
}

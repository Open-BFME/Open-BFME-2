// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0OpenContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004649F8, 386 bytes.
// OpenContain behavior ctor over the rowed UpdateModule base (0x253390,
// thing plus data). Substantial reconstruction from retail plus the BFME1
// rider-map concept (BFME1 OpenContain tracks riders in 12-byte maps; the
// element spellings here match the rowed bodies, so the member types are
// proven even though the offsets differ from BFME1 and the names below are
// TU-local descriptive, not donor-proven).
//
// Layout (retail-measured): UpdateModule base 0x20, six secondary interface
// vptrs at +0x20..+0x34 (installed inline by their implicit ctors, then
// re-stored by the derived class, DieModule precedent), int at +0x38,
// map<int,void*> at +0x3C/+0x48/+0x5C/+0xF0 (rowed 0x33C432 spelling),
// list<int> at +0x54/+0x74 (rowed 0x4EC36C spelling, 1-byte stack allocator
// temp idiom, FloodUpdate precedent), bulk-zero member at +0x84 (rowed
// Rva0042526Member 0x42526, 0x4C memset), three floats at +0xD0, bytes and
// ints to +0xEC. The full 0xFC matches the rowed CaveContain factory news.
//
// Schedule (all probe-proven): the init list runs the five dtor members in
// retail call order (+0x3C/+0x48/+0x54/+0x5C/+0x74, EH states 1-5) with the
// trivial +0x84 member last and no state; the +0xF0 map is constructed
// explicitly in the body over raw storage (an init-list entry would arm a
// sixth state retail never has); the float pointer is declared immediately
// before its stores (an early declaration folds to direct movss, adjacency
// keeps the lea+indexed form, AssaultTransport precedent); the tail reads a
// ModuleData+0x84 flag byte into +0xDE with a null guard. The construct-
// then-memset order at +0x84 is genuine retail. Zero new pins (all callees
// rowed). Row supersedes the ctor pin.
#include <map>
#include <list>
#include <string.h>

class Thing;
class ModuleData;
class Object;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	void setWakeFrame(Object *obj, unsigned int frame);
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

struct ContainIface20 { virtual void containIface20() = 0; };
struct ContainIface24 { virtual void containIface24() = 0; };
struct ContainIface28 { virtual void containIface28() = 0; };
struct ContainIface2C { virtual void containIface2C() = 0; };
struct ContainIface30 { virtual void containIface30() = 0; };
struct ContainIface34 { virtual void containIface34() = 0; };

class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	unsigned char m_pad[0x4C];
};

class OpenContain : public UpdateModule, public ContainIface20, public ContainIface24, public ContainIface28, public ContainIface2C, public ContainIface30, public ContainIface34
{
public:
	OpenContain(Thing *thing, const ModuleData *moduleData);
	virtual ~OpenContain();
private:
	int m_bfme38;
	_STL::map<int, void *> m_riderMapA;
	_STL::map<int, void *> m_riderMapB;
	_STL::list<int> m_riderIdListA;
	int m_bfme58;
	_STL::map<int, void *> m_riderMapC;
	int m_bfme68;
	int m_bfme6C;
	int m_bfme70;
	_STL::list<int> m_riderIdListB;
	int m_bfme78;
	int m_bfme7C;
	int m_bfme80;
	Rva0042526Member m_store84;
	float m_bfmeD0;
	float m_bfmeD4;
	float m_bfmeD8;
	unsigned char m_bfmeDC;
	unsigned char m_bfmeDD;
	unsigned char m_bfmeDE;
	unsigned char m_bfmeDF;
	unsigned char m_bfmeE0;
	unsigned char m_bfmeE1;
	unsigned char m_padE2[2];
	int m_bfmeE4;
	int m_bfmeE8;
	int m_bfmeEC;
	unsigned char m_riderMapDraw[0x0C];
};

// ??0OpenContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x004649F8
OpenContain::OpenContain(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
	, m_bfme38(0)
	, m_riderMapA()
	, m_riderMapB()
	, m_riderIdListA()
	, m_riderMapC()
	, m_riderIdListB()
	, m_store84()
{
	(((_STL::map<int, void *> *)(void *)m_riderMapDraw))->_STL::map<int, void *>::map<int, void *>();
	m_bfme78 = 0;
	m_bfme7C = 0;
	m_bfme80 = 0;
	m_bfme58 = 0;
	m_bfme68 = 0;
	m_bfme70 = 0;
	m_bfmeDF = 0;
	m_bfmeE0 = 0;
	m_bfmeE1 = 1;
	float *floatCells = &m_bfmeD0;
	floatCells[0] = 0.0f;
	floatCells[1] = 0.0f;
	floatCells[2] = 0.0f;
	m_bfmeDC = 0;
	memset(&m_store84, 0, 0x4C);
	m_bfme6C = 1;
	m_bfmeDD = 1;
	m_bfmeE4 = 0;
	m_bfmeEC = 0;
	m_bfmeE8 = 0;
	m_bfmeDE = m_moduleData ? *(const unsigned char *)((const char *)m_moduleData + 0x84) : 0;
}

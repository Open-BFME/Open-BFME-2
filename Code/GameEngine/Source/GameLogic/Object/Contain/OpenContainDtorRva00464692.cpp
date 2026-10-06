// cl: /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ??1OpenContain@@UAE@XZ @0x00464692 (227B). Identity from its audited
// deleting-dtor caller 0x00464B7A and OpenContain vtable/string evidence.
// The 0x54 list loop, Object+0x274 store, and GameLogic call are target-proven.
// Member offsets follow the byte-matched constructor at 0x004649F8; destructor
// callees at +0x3C, +0x5C, and +0xF0 refine the donor's generic map labels.
#include <list>
#include <map>

class Thing;
class ModuleData;
class Object;
class GameLogic;
extern GameLogic *TheGameLogic;

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

struct Rva00462D08Mapped { unsigned int m_bits; };
struct Rva00462D35Mapped { unsigned int m_bits; };
typedef _STL::map<int, Rva00462D08Mapped> Rva00462D08Map;
typedef _STL::map<int, Rva00462D35Mapped> Rva00462D35Map;

// The existing row at 0x00464391 names this destructor. The 12-byte view keeps
// the constructor-measured member extent; its map-like identity remains unknown.
class Rva00463782
{
public:
	unsigned int m_header;
	int m_flag;
	int m_extent;
	~Rva00463782();
};

class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	unsigned char m_pad[0x4C];
};

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

class OpenContain
	: public UpdateModule
	, public ContainIface20
	, public ContainIface24
	, public ContainIface28
	, public ContainIface2C
	, public ContainIface30
	, public ContainIface34
{
public:
	OpenContain(Thing *thing, const ModuleData *moduleData);
	virtual ~OpenContain();
private:
	int m_bfme38;
	Rva00463782 m_riderMapA;
	_STL::map<int, void *> m_riderMapB;
	_STL::list<int> m_riderIdListA;
	int m_bfme58;
	Rva00462D08Map m_riderMapC;
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
	Rva00462D35Map m_riderMapDraw;
};

OpenContain::~OpenContain()
{
	for (_STL::list<int>::iterator it = m_riderIdListA.begin(); it != m_riderIdListA.end(); ) {
		Object *rider = (Object *)(*it);
		++it;
		rider->m_containedBy = 0;
		TheGameLogic->destroyObject(rider);
	}

}

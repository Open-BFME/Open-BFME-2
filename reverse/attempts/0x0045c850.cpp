// ??0BezierProjectileBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.92 date=2026-09-26
// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
// stlport
// ??0BezierProjectileBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x0045C850 265B
// BezierProjectileBehavior ctor over rowed UpdateModule base 0x253390 with two
// extra interface bases at +0x20/+0x24 (implicit vtables give the five stores
// before the vector, base vtables provide the early c40818 pair, derived
// vtables the real five; Topple double-store shape with vector present so body
// stores cannot precede the member ctor). Vector<Coord3D> flight path at +0x44
// (base via Coord3D pin 0x211E58, cleared via Gen_p12pod erase row 0x2A133B
// same 12B stride), freelist member at +0x7c via rowed init 0x29FB3B with
// ebp+0xF context, zero tail plus 1.0f scale plus setWakeFrame FOREVER.
// Evidence: pin name, factory literal in friend_new 0x24B148, MissileUpdate
// caller 0x4A75C6, BFME1 CalcFlightPath layout (+0x44 vector, +0x50/+0x5C,
// +0x68 speed, +0x6C segs, +0x78 alt, +0x84 scale).
#include <vector>

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Gen_p12pod
{
	int a[3];
};

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

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
	void setWakeFrame(Object *object, UpdateSleepTime wakeDelay);
	Object *getObject() const { return m_object; }
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class Rva0045C850Iface20
{
public:
	Rva0045C850Iface20() {}
	virtual void rva0045C850Slot20();
};

class Rva0045C850Iface24
{
public:
	Rva0045C850Iface24() {}
	virtual void rva0045C850Slot24();
};

class Rva0029FB3BMember
{
public:
	void *init(void *context);

private:
	void *m_head;
};

class BezierProjectileBehavior : public UpdateModule, public Rva0045C850Iface20, public Rva0045C850Iface24
{
public:
	BezierProjectileBehavior(Thing *thing, const ModuleData *moduleData);

private:
	int m_28;
	float m_2C;
	float m_30;
	float m_34;
	int m_38;
	int m_3C;
	int m_40;
	_STL::vector<Coord3D> m_flightPath;
	Coord3D m_start;
	Coord3D m_end;
	float m_speed;
	int m_segments;
	int m_70;
	int m_74;
	int m_altCurve;
	Rva0029FB3BMember m_7C;
	unsigned char m_80;
	float m_heightScale;
};

// ??0BezierProjectileBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
BezierProjectileBehavior::BezierProjectileBehavior(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	int zero = 0;
	float fzero = 0.0f;
	Rva0029FB3BMember *member = (Rva0029FB3BMember *)((char *)this + 0x7C);
	void *context = (void *)((char *)&moduleData + 3);
	member->init(context);
	m_28 = zero;
	m_2C = fzero;
	m_30 = fzero;
	m_34 = fzero;
	m_38 = zero;
	m_3C = zero;
	m_40 = zero;
	_STL::vector<Gen_p12pod> *eraseView = reinterpret_cast<_STL::vector<Gen_p12pod> *>(&m_flightPath);
	eraseView->clear();
	m_speed = fzero;
	m_segments = zero;
	m_start.x = fzero;
	m_start.y = fzero;
	m_start.z = fzero;
	m_end.x = fzero;
	m_end.y = fzero;
	m_end.z = fzero;
	m_70 = zero;
	m_74 = zero;
	m_80 = 0;
	m_altCurve = zero;
	m_heightScale = 1.0f;
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

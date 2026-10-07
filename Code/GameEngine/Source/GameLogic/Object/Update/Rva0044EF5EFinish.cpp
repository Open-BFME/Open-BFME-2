// ??0Rva0044EF5E@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.97 date=2026-10-01
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0Rva0044EF5E@@QAE@PAVThing@@PBVModuleData@@@Z @0x0044EF5E 246B
// SpecialAbilityUpdate base ctor (LINK BONUS name; 10 files wait for it).
// Evidence: friend_new 0x0024A847 news 0x88 with this 2-arg ctor as its sole
// raw caller; derived ArrowStorm 0x004909D7 and 27 other ctors call it as base;
// xfer 0x0044F996 plus dtor 0x00451F45 prove the 0x88-byte layout with
// list<int> at +0x64; setWakeFrame tail via rowed 0x0044DF71 with FOREVER.
// Recipe: ProductionUpdateCtor rowed UpdateModule base plus list plus EH plus
// DetachableRider setWakeFrame tail plus Slaved float/int zero locals.
#include <list>

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
	void *m_object;
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
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *object, UpdateSleepTime delay);

private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class Rva0044EF5EIface20
{
public:
	Rva0044EF5EIface20() {}
	virtual void rva0044EF5ESlot20() = 0;
};

class Rva0044EF5E : public UpdateModule, public Rva0044EF5EIface20
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	// The complete destructor is the verified SpecialAbilityUpdate owner.
	virtual ~Rva0044EF5E();

private:
	int m_24;
	unsigned int m_28;
	unsigned int m_2C;
	unsigned int m_30;
	unsigned int m_34;
	unsigned int m_38;
	unsigned int m_3C;
	unsigned int m_40;
	struct V44 { float x,y,z; V44():x(0.0f),y(0.0f),z(0.0f){} } m_44;
	struct V44 m_50;
	int m_5C;
	int m_60;
	_STL::list<int> m_64;
	unsigned int m_68;
	unsigned int m_6C;
	float m_70;
	bool m_74;
	unsigned int m_78;
	bool m_7C;
	bool m_7D;
	bool m_7E;
	bool m_7F;
	bool m_80;
	bool m_81;
	bool m_82;
	bool m_83;
	unsigned int m_84;
};

Rva0044EF5E::Rva0044EF5E(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
	, m_24(0)
	, m_28(0)
	, m_2C(0)
	, m_30(0)
	, m_34(1)
	, m_38(1)
	, m_3C(0)
	, m_40(0)
	, m_5C(0)
	, m_60(0)
{
	float fzero = 0.0f;
	int zero = 0;
	m_68 = zero;
	m_6C = zero;
	m_70 = fzero;
	m_74 = false;
	m_78 = zero;
	m_7C = false;
	m_7D = false;
	m_7E = false;
	m_7F = false;
	m_80 = false;
	m_81 = true;
	m_82 = false;
	m_83 = false;
	m_84 = zero;
	setWakeFrame((Object *)m_object, UPDATE_SLEEP_FOREVER);
}

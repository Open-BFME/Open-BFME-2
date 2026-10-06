// cl: /Ireference/shims/bfmelist /O1 /DNDEBUG /MD /GX /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?loadPostProcess@GettingBuiltBehavior@@MAEXXZ, retail 0x004542AD, 77 bytes. Slot 1
// of vtable 0x008404FC (class of rowed ctor 0x004542FA). Base loadPostProcess via
// pinned 0x0058B03E first then secondary +0x20 slot 2 then work-list at +0x40 walked
// for pathfind re-add via rowed 0x002E718A with TheGameLogic findObjectByID row
// 0x00049DC5 and TheAI pathfinder at +0x10; Object status bit at +0x438.
// ?rva0045427E@GettingBuiltBehavior@@QAEXXZ @0x0045427E 47B: dtor helper using
// m_object +0x7c ID via findObjectByID row plus m_b3C gate plus Object::kill
// row 0x002984D4 with DamageType 8 and DeathType 0x16; sole caller is dtor 0x0045448F.

#include <list>

struct BfmePod20 { int a[5]; };

class Thing;
class ModuleData;
class Object;
enum DamageType { DamageType_Unknown = 0 };
enum DeathType { DeathType_Unknown = 0 };

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
	virtual void loadPostProcess();
	void setWakeFrame(Object *obj, unsigned int frame);
	Object *getObject(void) const { return m_object; }
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class GettingBuiltBehaviorSecondary
{
public:
	virtual void sec00();
	virtual void sec04();
	virtual void sec08();
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	void kill(DamageType damageType, DeathType deathType);
	char m_pad00[0x7c];
	int m_7c;
	char m_pad80[0x438 - 0x80];
	unsigned char m_438;
};

class Pathfinder
{
public:
	void unused();
};

class BFMEPathfinderMapShim
{
public:
	void rva002E718A(Object *object);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad[0x10];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

class GettingBuiltBehavior : public UpdateModule, public GettingBuiltBehaviorSecondary
{
public:
	GettingBuiltBehavior(Thing *thing, const ModuleData *moduleData);
	void rva0045427E();
protected:
	virtual void loadPostProcess();
private:
	const Object *getObject(void) const { return m_object; }
	int m_x24;
	float m_f28;
	int m_x2C;
	unsigned char m_b30;
	unsigned char m_b31;
	unsigned char m_b32;
	unsigned char m_b33;
	unsigned char m_b34;
	unsigned char m_b35;
	unsigned char m_b36;
	int m_x38;
	unsigned char m_b3C;
	unsigned char m_b3D;
	unsigned char m_b3E;
	_STL::list<BfmePod20, _STL::allocator<BfmePod20> > m_workList;
};

void GettingBuiltBehavior::loadPostProcess()
{
	UpdateModule::loadPostProcess();
	reinterpret_cast<GettingBuiltBehaviorSecondary*>((char*)this + 0x20)->sec08();
	for (_STL::list<BfmePod20, _STL::allocator<BfmePod20> >::iterator it = m_workList.begin(); it != m_workList.end(); ++it)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)(*it).a[0]);
		if (obj && (obj->m_438 & 1))
		{
			BFMEPathfinderMapShim *shim = reinterpret_cast<BFMEPathfinderMapShim*>(TheAI->pathfinder());
			shim->rva002E718A(obj);
		}
	}
}

void GettingBuiltBehavior::rva0045427E()
{
	Object *obj = m_object;
	if (!obj)
		return;
	Object *found = TheGameLogic->findObjectByID((ObjectID)obj->m_7c);
	if (!found)
		return;
	if (!m_b3C)
		return;
	found->kill((DamageType)8, (DeathType)0x16);
}

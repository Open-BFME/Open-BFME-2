// cl: /Ireference/shims/bfmelist /O1 /DNDEBUG /MD /GX /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0GettingBuiltBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004542FA, 169 bytes. Behavior-side ctor completing the GettingBuilt
// file-unit (ModuleData factory rowed at 0x24A9D5; behavior factory rowed
// at 0x24A99D news 0x44 with this pinned 2-arg ctor; poolkey rowed at
// 0x4543EB).
//
// No Zero Hour donor (BFME-new behavior). Retail-measured shape, mirroring
// PoisonedBehaviorCtor.cpp (UpdateModule 0x20 base plus inline-ctor fourth
// interface base carrying the +0x20 slot, /GX, /arch:SSE):
// - UpdateModule base resolves via its row at 0x00253390; setWakeFrame via
//   the established UpdateModule pin at 0x0044DF71 (called here with 1).
// - The +0x40 member is a 4-byte STLport list head whose default
//   construction calls the rowed BfmePod20 _List_base ctor at 0x00453ADD
//   with a stack allocator temp; the 20-byte element is an unidentified
//   payload, so BfmePod20 stands in per the pod-list placeholder
//   convention. +0x40 plus 4 is exactly the 0x44 factory news size.
// - Scalar members ride the init-list in declaration order (with a
//   non-trivial list member present they emit post-vptr mov-form stores,
//   not the pre-vptr and/or of the all-trivial probe); the +0x30 byte quad,
//   the +0x28 float and the repeated +0x3E zero are body assignments after
//   the list call, interleaved with the setWakeFrame setup in retail order.

#include <list>

struct BfmePod20 { int a[5]; };

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
	Object *getObject(void) const { return m_object; }
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class GettingBuiltBehaviorInterface
{
public:
	GettingBuiltBehaviorInterface() {}
	virtual void slot();
};

class GettingBuiltBehavior : public UpdateModule, public GettingBuiltBehaviorInterface
{
public:
	GettingBuiltBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~GettingBuiltBehavior();
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

// ??0GettingBuiltBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x004542FA
GettingBuiltBehavior::GettingBuiltBehavior(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData),
	m_x24(1),
	m_x2C(0),
	m_b34(0),
	m_b35(0),
	m_b36(0),
	m_x38(0),
	m_b3C(0),
	m_b3D(1),
	m_b3E(0)
{
	m_b30 = 0;
	m_f28 = 0.0f;
	m_b31 = 0;
	m_b32 = 0;
	m_b33 = 0;
	m_b3E = 0;
	setWakeFrame(const_cast<Object*>(getObject()), 1);
}

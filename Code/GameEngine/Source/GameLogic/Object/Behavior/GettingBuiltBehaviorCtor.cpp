// cl: /Ireference/shims/bfmelist /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

#include "../../../../../../reference/open-bfme-1/game/GameEngine/Include/GameLogic/Module/UpdateSleepTime.h"





// Retail table 0x00C40434 (+0x10) slot 0 is the rowed override 0x00454DF9.



class Rva004530ED;

class GettingBuiltBehaviorInterface
{
public:
	GettingBuiltBehaviorInterface();
	// Retail vtable 0x00C40020 holds _purecall in all 27 slots. Eighteen take the
	// signature of the rowed GettingBuiltBehavior override retail's table
	// 0x00C403C8 holds there; the other nine (0, 1, 6, 11, 13 to 17) are rowed
	// under other classes and stay anonymous.
	virtual void slot() = 0;
	virtual void slot1() = 0;
	virtual void rva00454430() = 0;
	virtual void rva00453905(Object *other) = 0;
	virtual void rva00453652(bool) = 0;
	virtual void rva004535B7() = 0;
	virtual void slot6() = 0;
	virtual bool rva0045314E(Object *obj) = 0;
	virtual bool rva004533B2() = 0;
	virtual bool rva004533A7() = 0;
	virtual void rva004543D5(bool value) = 0;
	virtual void slot11() = 0;
	virtual float rva0045342F(Object *obj) = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void rva00453B20(Object *obj) = 0;
	virtual bool rva004540F5() = 0;
	virtual float rva00453FE7(Object *obj) = 0;
	virtual void rva00453F31(int a1) = 0;
	virtual bool rva004531E4(Object *obj) = 0;
	virtual bool rva0045362B(int id) = 0;
	virtual int rva00453B7B(int, Rva004530ED *) = 0;
	virtual bool rva00453E5C() = 0;
	virtual void rva00453BF1() = 0;
};
// ??0GettingBuiltBehaviorInterface@@QAE@XZ @0x00453111 9B: the default constructor, storing the
// class's own vtable (VA 0x00C40020) and returning this.
GettingBuiltBehaviorInterface::GettingBuiltBehaviorInterface()
{
}

class GettingBuiltBehavior : public UpdateModule, public GettingBuiltBehaviorInterface
{
public:
	GettingBuiltBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~GettingBuiltBehavior();
	virtual UpdateSleepTime update();
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
public:
	// retail slot 4: the rowed ?getModuleNameKey@GettingBuiltBehavior@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
	// Primary table 0x00C404FC, slots 5 and 8: the rowed onObjectCreated 0x004534F5
	// and onDelete 0x00454501.
	virtual void onObjectCreated();
	virtual void onDelete();
	// Interface table 0x00C403C8: the eighteen rowed overrides.
	virtual void rva00454430();
	virtual void rva00453905(Object *other);
	virtual void rva00453652(bool);
	virtual void rva004535B7();
	virtual bool rva0045314E(Object *obj);
	virtual bool rva004533B2();
	virtual bool rva004533A7();
	virtual void rva004543D5(bool value);
	virtual float rva0045342F(Object *obj);
	virtual void rva00453B20(Object *obj);
	virtual bool rva004540F5();
	virtual float rva00453FE7(Object *obj);
	virtual void rva00453F31(int a1);
	virtual bool rva004531E4(Object *obj);
	virtual bool rva0045362B(int id);
	virtual int rva00453B7B(int, Rva004530ED *);
	virtual bool rva00453E5C();
	virtual void rva00453BF1();
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
	// Primary table 0x00C404FC, slot 1: the rowed loadPostProcess 0x004542AD.
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
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
	setWakeFrame(const_cast<Object*>(getObject()), UPDATE_SLEEP_NONE);
}

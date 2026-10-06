// cl: /Ireference/shims/bfmelist /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1GettingBuiltBehavior@@UAE@XZ, retail 0x0045448F, 114 bytes. Behavior-side
// destructor completing the GettingBuilt file-unit (ctor rowed at 0x004542FA,
// helper rowed at 0x0045427E, poolkey at 0x004543EB, deleting dtor at
// 0x0045477E slot 0 of vtable 0x00C404FC).
//
// Retail: 4 vptr restores (+0 0xC404FC, +0x0C 0xC40440, +0x10 0xC40434,
// +0x20 0xC403C8), helper call 0x0045427E, TheAudio (0x00DFE6E8) slot 0x6c
// removeAudioEvent with +0x24 handle then store 1, list at +0x40 via rowed
// 0x004EC395, base 0x0024A797. Layout follows rowed ctor plus LoadPostProcess
// secondary (3 slots, sec08 at +0x20) and FoundationAIUpdateSlot14 TheAudio
// idiom; CastleMemberBehaviorDtor audio-plus-store precedent.

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

typedef unsigned int AudioHandle;

class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
};

extern AudioManager *TheAudio;

class GettingBuiltBehavior : public UpdateModule, public GettingBuiltBehaviorSecondary
{
public:
	GettingBuiltBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~GettingBuiltBehavior();
	void rva0045427E();
private:
	unsigned int m_audio24;
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

GettingBuiltBehavior::~GettingBuiltBehavior()
{
	rva0045427E();
	if (TheAudio != 0)
	{
		TheAudio->removeAudioEvent(m_audio24);
		m_audio24 = 1;
	}
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorModuleOtherAnchor@BehaviorModuleOther@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

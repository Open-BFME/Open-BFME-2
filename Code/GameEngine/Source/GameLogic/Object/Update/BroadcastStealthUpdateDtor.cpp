// cl: /DNDEBUG /MD /EHsc
//
// ??1BroadcastStealthUpdate@@UAE@XZ, retail 0x004A3555, 88 bytes (pinned;
// rowed deleting wrapper 0x004A35AD). Stores four vtables (+0x00/+0x0C/
// +0x10/+0x20), calls the helper 0x004A33EE on this, releases the pool
// member at +0x28 through the pinned PoolMember::Rva00268902 0x00268902,
// then runs the opaque MI base dtor 0x0024A797. Retail's unwind map holds
// the base (state 0) and the +0x28 member (state 1, through 0x00268AFF, a
// jmp to 0x00268902), so the release is that member's inline destructor.
// Retail stores no state between the helper call and the release, so the
// release is declared non-throwing here. The helper is pinned under an
// address name from this call (second caller 0x004A35DE).
// UpdateModule carries its own three vptrs (+0x00/+0x0C/+0x10), as the rowed
// ctor 0x004A342E and UpdateModule::~UpdateModule 0x0024A797 show, so this
// unit's vftable names agree with the ctor's: the +0x10 UpdateModuleInterface
// one (0x00C52358) is ??_7BroadcastStealthUpdate@@6BUpdateModule@@@.
#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();
private:
	int m_14;
	int m_18;
	int m_1C;
};

class BroadcastStealthUpdate_B3
{
public:
	virtual void f3();
};

class PoolMember
{
public:
	~PoolMember() { Rva00268902(); }
	void Rva00268902() throw();
private:
	void *m_ptr;
};

class BroadcastStealthUpdate : public UpdateModule, public BroadcastStealthUpdate_B3
{
public:
	virtual UpdateSleepTime update(); // UpdateModuleInterface slot 0, the rowed override
	virtual ~BroadcastStealthUpdate();
	void rva004A33EE();
private:
	int m_24;
	PoolMember m_28;
};

BroadcastStealthUpdate::~BroadcastStealthUpdate()
{
	rva004A33EE();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f3@BroadcastStealthUpdate_B3@@UAEXXZ=?Is_Valid@RegistryClass@@QAE_NXZ")

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?getBody@BehaviorModuleInterface@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

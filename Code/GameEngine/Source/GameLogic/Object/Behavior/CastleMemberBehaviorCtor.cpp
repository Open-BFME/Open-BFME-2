// cl: /O1 /DNDEBUG /MD
//
// ??0CastleMemberBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00395B66, 73 bytes.
// CastleMemberBehavior behavior ctor over the rowed BehaviorModule base
// (0x253330, thing plus data): forwards both args to the base, stores the
// first +0x10 slot value, zeroes +0x14/+0x18/+0x1C and the bytes at
// +0x24/+0x25, then re-stores the primary vtable slot and the +0x0C/+0x10
// secondary slots (address-of TU-local dummies, DIR32-masked) and stores 1
// at +0x20. The double +0x10 store uses the ToggleMounted union-plus-barrier
// shape so retail keeps both. The rowed instance factory 0x24AAEE
// (news 0x28) is the sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_slotFirst;
static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Opaque BehaviorModule base; ctor resolves to its row. The explicit
// m_vtable member stands in for the inherited vptr so body order is source
// order.
class BehaviorModule
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
};

class CastleMemberBehavior : public BehaviorModule
{
public:
	CastleMemberBehavior(Thing *thing, const ModuleData *moduleData);

private:
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	unsigned char m_24;
	unsigned char m_25;
	unsigned char m_pad26[0x28 - 0x26];
};

// ??0CastleMemberBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x395B66
CastleMemberBehavior::CastleMemberBehavior(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData)
{
	*(const void **)((char *)this + 0x10) = &s_slotFirst;
	_ReadWriteBarrier();
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_24 = 0;
	m_25 = 0;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_20 = 1;
}

// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// ??0BroadcastStealthUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004A342E, 146 bytes. BFME 2 module without a ZH counterpart. Target
// evidence: the body runs the rowed UpdateModule ctor 0x00253390 and the
// rowed UpgradeMux ctor 0x004CE2A3 on +0x20, stores the four vtables the
// rowed dtor 0x004A3555 restores (0x00852364 primary, whose slot 0 is the
// rowed ??_GBroadcastStealthUpdate 0x004A35AD and slot 3 the rowed xfer
// 0x004A3752; 0x00852358 the UpdateModuleInterface one holding the rowed
// update 0x004A35C9; 0x00852310 at +0x20 the UpgradeMux one), then builds
// the +0x28 ID list (the one update fills) through the rowed list-base
// ctor 0x0029FB3B with a stack allocator. The module sleeps forever when
// the module data's +0x2C string (released by the rowed module-data dtor
// 0x00256097) is non-empty, else wakes at once.
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

// BFME2's Snapshot puts GetSnapshotName where Zero Hour spells crc (primary slot 2).
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class UpgradeMux
{
public:
	UpgradeMux();
	virtual Bool isAlreadyUpgraded() const;
protected:
	Bool m_upgradeExecuted; // +0x04
};

class PoolMember
{
public:
	~PoolMember() { Rva00268902(); }
	void Rva00268902() throw();
private:
	void *m_ptr; // +0x00
};

// The ID list's base; its allocator-taking ctor is rowed at 0x0029FB3B.
struct Rva0029FB3BAlloc
{
	Rva0029FB3BAlloc() {}
};

#include "../../../../Include/GameLogic/Module/Rva0029FB3BMember.h"

// The list itself, default-constructed as STLport's list() does.
class ObjectIDList : public Rva0029FB3BMember
{
public:
	explicit ObjectIDList(const Rva0029FB3BAlloc &alloc = Rva0029FB3BAlloc()) : Rva0029FB3BMember(alloc) {}
};

class BroadcastStealthUpdateModuleData
{
public:
	unsigned char m_pad00[0x2C];
	AsciiString m_2c; // +0x2C
};

class BroadcastStealthUpdate : public UpdateModule, public UpgradeMux
{
public:
	virtual UpdateSleepTime update(); // UpdateModuleInterface slot 0, the rowed override
	BroadcastStealthUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~BroadcastStealthUpdate();
private:
	const BroadcastStealthUpdateModuleData *getBroadcastStealthUpdateModuleData() const { return (const BroadcastStealthUpdateModuleData *)m_moduleData; }

	ObjectIDList m_ids; // +0x28
public:
	// retail slot 4: the rowed ?getModuleNameKey@BroadcastStealthUpdate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

BroadcastStealthUpdate::BroadcastStealthUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	if (getBroadcastStealthUpdateModuleData()->m_2c.getLength() > 0)
		setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
	else
		setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}

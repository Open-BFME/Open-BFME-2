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


#include "../../../../Include/GameLogic/Module/UpgradeMux.h"
#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"

enum ObjectID;

// Four-byte STLport list storage: construction and teardown use the existing
// out-of-line member providers at 0x0029FB3B and 0x00268902.
struct Rva0029FB3BAlloc
{
	Rva0029FB3BAlloc() {}
};

#include "../../../../Include/GameLogic/Module/Rva0029FB3BMember.h"

struct BridgeBehaviorObjectIDNode
{
	BridgeBehaviorObjectIDNode *m_next;
	BridgeBehaviorObjectIDNode *m_previous;
	ObjectID m_value;
};

// Keep the teardown bound to the rowed 29-byte cleanup owner. The older
// Rva0029FB3BMember destructor spelling has a divergent COMDAT elsewhere.
class PoolMember
{
public:
	void Rva00268902() throw();
};

class BridgeBehaviorObjectIDList
{
public:
	explicit BridgeBehaviorObjectIDList(const Rva0029FB3BAlloc &alloc = Rva0029FB3BAlloc())
	{
		reinterpret_cast<Rva0029FB3BMember *>(this)->init(const_cast<Rva0029FB3BAlloc *>(&alloc));
	}
	~BridgeBehaviorObjectIDList()
	{
		reinterpret_cast<PoolMember *>(this)->Rva00268902();
	}
	BridgeBehaviorObjectIDNode *node() const
	{
		return static_cast<BridgeBehaviorObjectIDNode *>(m_head);
	}
	UnsignedInt size() const
	{
		UnsignedInt count = 0;
		for (BridgeBehaviorObjectIDNode *it = node()->m_next; it != node(); it = it->m_next)
			++count;
		return count;
	}
private:
	void *m_head;
};

struct BroadcastStealthUpdateModuleData
{
	unsigned char m_pad00[0x08];
	BfmeFixedStorage0004543D m_08;	// +0x08 the kinds
	float m_24;			// +0x24 the radius
	UpdateSleepTime m_28;		// +0x28 the delay
	AsciiString m_2c;		// +0x2C tested by the constructor
	unsigned char m_pad30[0x140 - 0x30];
	unsigned m_140;			// +0x140 the flags to keep
};

class BroadcastStealthUpdate : public UpdateModule, public UpgradeMux
{
public:
	BroadcastStealthUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~BroadcastStealthUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	void rva004A33EE(); // 0x004A33EE
protected:
	virtual void xfer(Xfer *xfer);
private:
	const BroadcastStealthUpdateModuleData *getBroadcastStealthUpdateModuleData() const
	{
		return (const BroadcastStealthUpdateModuleData *)m_moduleData;
	}
	BridgeBehaviorObjectIDList m_28; // +0x28
};

BroadcastStealthUpdate::BroadcastStealthUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	if (getBroadcastStealthUpdateModuleData()->m_2c.getLength() > 0)
		setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
	else
		setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}

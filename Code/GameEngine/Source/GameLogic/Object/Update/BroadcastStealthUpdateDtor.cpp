// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ??1BroadcastStealthUpdate@@UAE@XZ, retail 0x004A3555, 88 bytes (pinned;
// rowed deleting wrapper 0x004A35AD). Stores four vtables (+0x00/+0x0C/
// +0x10/+0x20), calls the helper 0x004A33EE on this, releases the ID-list
// member at +0x28 through the rowed PoolMember cleanup at 0x00268902,
// then runs UpdateModule's dtor 0x0024A797. Retail's unwind map holds
// the base (state 0) and the +0x28 member (state 1, through 0x00268AFF, a
// jmp to 0x00268902), so the release is that member's inline destructor.
// Retail stores no state between the helper call and the release, so the
// release is declared non-throwing here. The helper is pinned under an
// address name from this call (second caller 0x004A35DE).
// UpdateModule carries its own three vptrs (+0x00/+0x0C/+0x10), as the rowed
// ctor 0x004A342E and UpdateModule::~UpdateModule 0x0024A797 show, so this
// unit's vftable names agree with the ctor's: the +0x10 UpdateModuleInterface
// one (0x00C52358) is ??_7BroadcastStealthUpdate@@6BUpdateModule@@@.
// BFME2's Snapshot puts GetSnapshotName where Zero Hour spells crc (primary slot 2).
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


#include "../../../../Include/GameLogic/Module/UpgradeMux.h"
#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"
#include "ascii_string.h"

typedef unsigned int UnsignedInt;

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

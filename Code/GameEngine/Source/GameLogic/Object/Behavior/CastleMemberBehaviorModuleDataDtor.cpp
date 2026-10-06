// cl: /DNDEBUG /MD /GX /Ireference/shims/moduledata
//
// ??1CastleMemberBehaviorModuleData@@UAE@XZ, retail 0x00395B2C, 58 bytes.
// Virtual dtor over vtable 0x00C1A380 (slot 0 deleting dtor at 0x00396007
// calls this body). Destroys the BeingBuiltSound holder at +0x14 through the
// rowed Release_Ref at 0x00050ED3 when non-null (single tracked member, state
// 0 via and [ebp-4],0), then restores the Snapshot base vtable 0x00BBB554.
// Layout from the rowed ctor 0x00395B03 (vtable 0xC1A380, INI table 0x00C1A310:
// CampDestroyedOwnerEvaEvent at +0x08 defaults 9, CampDestroyedAllyEvaEvent
// at +0x0C defaults 0xA, CampDestroyedAttackerEvaEvent at +0x10 defaults 8,
// BeingBuiltSound at +0x14 null, StoreUpgradePrice at +0x18 false,
// CountsForEvaCastleBreached at +0x19 false; factory 0x0024AB26 news 0x1C).
// Shape follows Bloodthirsty/Flammable ModuleData dtors (shared Snapshot
// base dtor, empty derived body, entry derived store kept so no novtable).

#include "Common/Snapshot.h"

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct BeingBuiltSoundHolder
{
	~BeingBuiltSoundHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	OpaqueRefCounted *m_ptr;
};

class CastleMemberBehaviorModuleData : public Snapshot
{
public:
	virtual ~CastleMemberBehaviorModuleData();

private:
	int m_unused04; // +0x04
	int m_campDestroyedOwnerEvaEvent; // +0x08
	int m_campDestroyedAllyEvaEvent; // +0x0C
	int m_campDestroyedAttackerEvaEvent; // +0x10
	BeingBuiltSoundHolder m_beingBuiltSound; // +0x14
	bool m_storeUpgradePrice; // +0x18
	bool m_countsForEvaCastleBreached; // +0x19
	char m_pad1A[0x1C - 0x1A];
};

CastleMemberBehaviorModuleData::~CastleMemberBehaviorModuleData()
{
}

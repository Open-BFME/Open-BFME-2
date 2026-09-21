// cl: /O1 /DNDEBUG /MD
//
// ??0CastleMemberBehaviorModuleData@@QAE@XZ, retail 0x00395B03, 41 bytes.
// Frameless store-only ctor over table 0xC1A310 (CampDestroyedOwnerEvaEvent
// at +8 defaults to 9, CampDestroyedAllyEvaEvent at +C to 0xA,
// CampDestroyedAttackerEvaEvent at +10 to 8, BeingBuiltSound at +14 zero,
// StoreUpgradePrice at +18 false, CountsForEvaCastleBreached at +19 false).
// Identity is the table plus the rowed CastleMemberBehavior pool key 0x3959B5
// in the same cluster plus factory 0x24AB26 news 0x1C sole caller plus proc
// 0x395AF2 rowed. Shape follows SlaveWatcher trivial-ctor precedent: flat
// TU-local class with explicit void*m_vtable (no virtuals, no vtable
// emission) plus plain-data members; body assignments in retail order.
// Vtable 0x00C1A380 is unique image-wide (single installing site).

class CastleMemberBehaviorModuleData
{
public:
	CastleMemberBehaviorModuleData();

private:
	const void *m_vtable; // +0x00
	unsigned int m_unused04; // +0x04
	int m_campDestroyedOwnerEvaEvent; // +0x08
	int m_campDestroyedAllyEvaEvent; // +0x0C
	int m_campDestroyedAttackerEvaEvent; // +0x10
	int m_beingBuiltSound; // +0x14
	bool m_storeUpgradePrice; // +0x18
	bool m_countsForEvaCastleBreached; // +0x19
};

// ??0CastleMemberBehaviorModuleData@@QAE@XZ @0x395B03
CastleMemberBehaviorModuleData::CastleMemberBehaviorModuleData()
{
	m_vtable = reinterpret_cast<const void *>(0x00C1A380);
	m_campDestroyedOwnerEvaEvent = 9;
	m_campDestroyedAllyEvaEvent = 0xA;
	m_campDestroyedAttackerEvaEvent = 8;
	m_beingBuiltSound = 0;
	m_storeUpgradePrice = false;
	m_countsForEvaCastleBreached = false;
}

// cl: /DNDEBUG /MD /EHsc

// ??0DemoTrapUpdateModuleData@@QAE@XZ at retail 0x0049597A (55 bytes).
// The module-data half of DemoTrapUpdate: vtable immediate 0x00C4ED70 modelled
// as an explicit first member (OCLUpdateModuleDataCtor precedent, so no vtable
// is emitted and no dtor row is owed), an uninitialised word at +0x04 retail
// never stores, the detonation weapon key at +0x08, a 0x1C zero block at +0x0C
// constructed through the shared memset helper pinned at 0x24C7B3 (it memsets
// 0x1C via the CRT memset import thunk at 0x6291AE; the pin claims only the
// address), then the table-backed slots: ManualModeWeaponSlot +0x28,
// DetonationWeaponSlot +0x2C, ProximityModeWeaponSlot +0x30, the
// TriggerDetonationRange real at +0x34, ScanRate at +0x38 and the three mode
// flags at +0x3C/+0x3D/+0x3E. Field identity is retail's own INI table at
// 0x00C4EEC8 (landed buildFieldParse row) joined to the Zero Hour
// DemoTrapUpdate donor (DefaultProximityMode, DetonationWeaponSlot,
// ProximityModeWeaponSlot, ManualModeWeaponSlot, TriggerDetonationRange,
// DetonateWhenKilled). Body order is load-bearing and follows retail.
extern "C" const void *const vtbl_00C4ED70[];  // folded, 9 classes; via ??_7BeaconClientUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4ED70=??_7BeaconClientUpdateModuleData@@6B@")

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();
	unsigned char m_data[0x1C];
};

class DemoTrapUpdateModuleData
{
public:
	DemoTrapUpdateModuleData();

private:
	const void *m_vtable;
	unsigned int m_unused04;
	unsigned int m_detonationWeapon;			// +0x08
	Rva0024C7B3Member m_zeroBlock;			// +0x0C
	unsigned int m_manualModeWeaponSlot;		// +0x28
	unsigned int m_detonationWeaponSlot;		// +0x2C
	unsigned int m_proximityModeWeaponSlot;		// +0x30
	float m_triggerDetonationRange;			// +0x34
	unsigned int m_scanRate;				// +0x38
	bool m_defaultsToProximityMode;			// +0x3C
	bool m_autoDetonationWithFriends;		// +0x3D
	bool m_detonateWhenKilled;				// +0x3E
};

DemoTrapUpdateModuleData::DemoTrapUpdateModuleData()
	: m_vtable( reinterpret_cast<const void *>(((unsigned int)vtbl_00C4ED70)) )
{
	m_defaultsToProximityMode = false;
	m_autoDetonationWithFriends = false;
	m_manualModeWeaponSlot = 0;
	m_detonationWeaponSlot = 0;
	m_proximityModeWeaponSlot = 0;
	m_scanRate = 0;
	m_detonationWeapon = 0;
	m_detonateWhenKilled = false;
	m_triggerDetonationRange = 0.0f;
}

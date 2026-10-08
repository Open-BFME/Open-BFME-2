// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0CrateCollideModuleData@@QAE@XZ, retail 0x004BC657, 107 bytes.
// The module-data half of CrateCollide: vtable immediate 0x00C5A660 modelled
// as an explicit first member (DemoTrapUpdateModuleDataCtor precedent, so no
// vtable is emitted and no dtor row is owed), an uninitialised word at +0x04
// retail never stores, the RequiredKindOf set at +0x08 plus the
// ForbiddenKindOf set at +0x24 both constructed through the shared memset
// helper pinned at 0x24C7B3 (Rva0024C7B3Member precedent), the owner and
// pickup flags at +0x40/+0x41/+0x42, PickupScience at +0x44 defaulting to -1,
// the ExecuteFX slot at +0x48, the ExecuteAnimation string at +0x4C copied
// from a zeroed static through the AsciiString copy ctor pinned at 0x365F0,
// the ExecuteAnimationTime and ZRise reals at +0x50/+0x54 defaulting to 0.0f
// and ExecuteAnimationFades at +0x58 defaulting to true. Field identity is
// retail's own INI table at 0x00C5A7A8 (landed buildFieldParse row) joined to
// the BFME1 field_names vote (PickupScience is CrateCollideModuleData's
// member) and the Zero Hour CrateCollide donor family. Everything lives in
// the init list in declaration order: init-list (-1) emits the leading or
// form under /O1 and the scheduler keeps the retail store order. The empty
// UpdateModuleData base (inline-empty ctor plus declared-only dtor, Topple
// precedent) is load-bearing for the EH frame: it produces the prolog plus
// the single state-0 store with no transitions; a standalone class compiles
// frameless here. The string global is an extern (DIR32-masked, no pin).

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

private:
	unsigned char m_data[0x1C];
};

#include "ascii_string.h"


extern const void *const g_00C5A660[];

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class CrateCollideModuleData : public UpdateModuleData
{
public:
	CrateCollideModuleData();

private:
	const void *m_vtable;				// +0x00
	unsigned int m_unused04;			// +0x04
	Rva0024C7B3Member m_requiredKindOf;		// +0x08
	Rva0024C7B3Member m_forbiddenKindOf;		// +0x24
	bool m_forbidOwnerPlayer;			// +0x40
	bool m_buildingPickup;				// +0x41
	bool m_humanOnly;				// +0x42
	int m_pickupScience;				// +0x44
	void *m_executeFX;				// +0x48
	AsciiString m_executeAnimation;			// +0x4C
	float m_executeAnimationTime;			// +0x50
	float m_executeAnimationZRise;			// +0x54
	bool m_executeAnimationFades;			// +0x58
};

CrateCollideModuleData::CrateCollideModuleData()
	: m_vtable((const void *)g_00C5A660)
	, m_forbidOwnerPlayer(false)
	, m_buildingPickup(false)
	, m_humanOnly(false)
	, m_pickupScience(-1)
	, m_executeFX(0)
	, m_executeAnimation(AsciiString::TheEmptyString)
	, m_executeAnimationTime(0.0f)
	, m_executeAnimationZRise(0.0f)
	, m_executeAnimationFades(true)
{
}

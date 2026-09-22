// cl: /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
//
// ??0RespawnUpdateModuleData@@QAE@XZ, retail 0x004C14DF (110 bytes).
// SupplyTruck-based respawn data: the pinned SupplyTruck base ctor runs
// first against this (the base is an empty EH shim, so no displacement),
// the compiler installs this TU's vtable through the ??_7 pin at
// 0x00C5BA00, the +0x64 PermanentlyKilledByFilter member builds through
// the opaque 0x3623E5 pin (AODCrushCollideModuleDataCtor precedent: the
// pin claims only the address), two 28B FixedStorage temps are
// copy-constructed in place from the prototype at 0x00DFEFA4 through the
// rowed BfmeFixedStorage0004543D copy ctor, the filter consumes both
// by value through the 0x362087 pin (ret 0x38 pops both temps), and
// CanRespawn at +0x68 is set to 1. The RespawnUpdate friend TU proves the
// field identities (filter at +0x64, CanRespawn at +0x68, factory news
// 0x6C); the ModuleFactory pin note proves the base, vtable and factory.
// AODCrushCollideModuleDataCtor precedent: virtual class with a
// declared-only virtual dtor emits the vtable store mid-init, and an empty
// base with a declared-only dtor brackets EH state 0 with no code.

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);

private:
	int m_x;
};

// Virtual base plus virtual derived with declared-only dtors (no code):
// the base contributes the vptr at +0 so the base call takes this with no
// displacement, and the derived vtable store lands mid-init through the
// ??_7 pin (DominateEnemySpecialPowerModuleDataCtor precedent, which arms
// the same two EH states over the same 0xDFEFA4 temps).
class SupplyTruckAIUpdateModuleData
{
public:
	SupplyTruckAIUpdateModuleData();
	virtual ~SupplyTruckAIUpdateModuleData();

private:
	unsigned char m_pad[0x64 - 4]; // +0x04..+0x63, real SupplyTruck base
};

class RespawnUpdateModuleData : public SupplyTruckAIUpdateModuleData
{
public:
	RespawnUpdateModuleData();
	virtual ~RespawnUpdateModuleData();

private:
	Rva003623E5Member m_permanentlyKilledByFilter; // +0x64
	unsigned char m_canRespawn; // +0x68
	unsigned char m_tail[3]; // +0x69..+0x6B, factory news 0x6C
};

// ??0RespawnUpdateModuleData@@QAE@XZ @0x4C14DF
RespawnUpdateModuleData::RespawnUpdateModuleData()
{
	m_permanentlyKilledByFilter.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
	m_canRespawn = 1;
}

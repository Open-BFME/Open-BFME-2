// cl: /O1 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0CloudBreakSpecialPowerModuleData@@QAE@XZ, retail 0x004C479A, 61 bytes.
// Frameless small ctor: runs the pinned opaque intermediate base ctor at
// 0x4930A0, loads CloudBreakRadius at +0x7C from the shared 10.0f constant
// at 0x00BC2428, installs vtable 0x00C5D468, zeroes CloudBreakFX at +0x80
// and SunbeamObject at +0x84 (compact and forms), then loads ObjectSpacing
// at +0x88 from the shared 100.0f constant at 0x00BC292C (see the rowed
// buildFieldParse proc holding the four-field table 0x00C5D378, and the
// rowed CloudBreakSpecialPower pool key closing this cluster). Size 0x8C
// matches the rowed 0x251E58 factory news. The TU-local base keeps an
// explicit vtable slot plus pad to 0x7C (Darkness precedent, so no vtable
// is emitted); both absolute floats stay extern so they keep the movss form
// (Rain precedent), each materialized into a named local first. Scheduling:
// the _ReadWriteBarrier pins the and-stores below the vtable store
// (UpgradeDie precedent); the loads stay in place (no cross-store
// hoisting); the +0x84 zero sources before +0x80 to match retail. Row
// supersedes the ctor pin.

// Retail VA 0x00C5D468 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void vfn_00065212();
extern "C" void vfn_000B3FD0();
extern "C" void vfn_000B69A1();
extern "C" void vfn_000D43D0();
extern "C" void vfn_0047A699();
extern "C" void vfn_0047A69C();
extern "C" void vfn_004C47D7();
extern "C" void vfn_0050B5C6();
#pragma comment(linker, "/alternatename:_vfn_00065212=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:_vfn_000B3FD0=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_000B69A1=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:_vfn_000D43D0=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A699=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:_vfn_0047A69C=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:_vfn_004C47D7=??_GCloudBreakSpecialPowerModuleData@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B5C6=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" const void *const vtbl_00C5D468[] = {
	(const void *)&vfn_004C47D7,
	(const void *)&vfn_000B3FD0,
	(const void *)&vfn_00065212,
	(const void *)&vfn_0047A69C,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_000B69A1,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_0050B5C6
};

class Rva004930A0
{
public:
	Rva004930A0();

	void *m_vtable; // +0
	unsigned char m_pad[0x7C - 4]; // +4..0x7B
};

extern float g_cloudBreakRadiusDefault; // 0x00BC2428, 10.0f
extern float g_objectSpacingDefault; // 0x00BC292C, 100.0f

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class CloudBreakSpecialPowerModuleData : public Rva004930A0
{
public:
	CloudBreakSpecialPowerModuleData();

private:
	float m_cloudBreakRadius; // +0x7C
	void *m_cloudBreakFX; // +0x80
	void *m_sunbeamObject; // +0x84
	float m_objectSpacing; // +0x88
};

// ??0CloudBreakSpecialPowerModuleData@@QAE@XZ @0x4C479A
CloudBreakSpecialPowerModuleData::CloudBreakSpecialPowerModuleData()
	: Rva004930A0()
{
	float radius = g_cloudBreakRadiusDefault;
	m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00C5D468));
	_ReadWriteBarrier();
	m_sunbeamObject = 0;
	m_cloudBreakFX = 0;
	m_cloudBreakRadius = radius;
	float spacing = g_objectSpacingDefault;
	m_objectSpacing = spacing;
}

// ?g_objectSpacingDefault@@3MA: matched references place it at VA 0xbc292c; also referenced as _kF7C.
float g_objectSpacingDefault = 1e+02f;
#pragma comment(linker, "/alternatename:_kF7C=?g_objectSpacingDefault@@3MA")
// ?g_cloudBreakRadiusDefault@@3MA: the global at VA 0xbc2428 is ?g_Va00BC2428@@3MA.
#pragma comment(linker, "/alternatename:?g_cloudBreakRadiusDefault@@3MA=?g_Va00BC2428@@3MA")

// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0CloudBreakSpecialPowerModuleData@@QAE@XZ, retail 0x004C479A, 61 bytes.
// Frameless small ctor: runs the pinned opaque intermediate base ctor at
// 0x4930A0, loads CloudBreakRadius at +0x7C from the shared 10.0f constant
// at 0x00BC2428, installs vtable 0x00C5D468, zeroes CloudBreakFX at +0x80
// and SunbeamObject at +0x84 (compact and forms), then loads ObjectSpacing
// at +0x88 from the shared 100.0f constant at 0x00BC292C (see the rowed
// buildFieldParse proc holding the four-field table 0x00C5D378, and the
// rowed CloudBreakSpecialPower pool key closing this cluster). Size 0x8C
// matches the rowed 0x251E58 factory news. The class is novtable, so the
// only vptr store is the data table's below and no vtable is emitted; both
// absolute floats stay extern so they keep the movss form
// (Rain precedent), each materialized into a named local first. Scheduling:
// the _ReadWriteBarrier pins the and-stores below the vtable store
// (UpgradeDie precedent); the loads stay in place (no cross-store
// hoisting); the +0x84 zero sources before +0x80 to match retail. Row
// supersedes the ctor pin.

// matches the rowed 0x251E58 factory news. The TU-local base keeps an
// explicit vtable slot plus pad to 0x7C (Darkness precedent, so no vtable
// is emitted); both absolute floats stay extern so they keep the movss form
// Retail VA 0x00C5D468 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")();
extern "C" void __identifier("??1Coord2D@@QAE@XZ")();
extern "C" void __identifier("?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")();
extern "C" void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
extern "C" void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
extern "C" void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
extern "C" void __identifier("??_GCloudBreakSpecialPowerModuleData@@UAEPAXI@Z")();
extern "C" void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
extern "C" const void *const vtbl_00C5D468[] = {
	(const void *)&__identifier("??_GCloudBreakSpecialPowerModuleData@@UAEPAXI@Z"),
	(const void *)&__identifier("??1Coord2D@@QAE@XZ"),
	(const void *)&__identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ"),
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
};

typedef float Real;
class FXList;
class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_pad[0x7C - 4];
};

extern float g_cloudBreakRadiusDefault; // 0x00BC2428, 10.0f
extern float g_objectSpacingDefault; // 0x00BC292C, 100.0f

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class __declspec(novtable) CloudBreakSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	CloudBreakSpecialPowerModuleData();

	float m_cloudBreakRadius; // +0x7C
	const FXList *m_fx; // +0x80
	unsigned char m_objectName[4]; // +0x84
	Real m_spacing; // +0x88
};

// ??0CloudBreakSpecialPowerModuleData@@QAE@XZ @0x4C479A
CloudBreakSpecialPowerModuleData::CloudBreakSpecialPowerModuleData()
	: SpecialPowerModuleData()
{
	float radius = g_cloudBreakRadiusDefault;
	*(unsigned int *)this = ((unsigned int)vtbl_00C5D468);
	_ReadWriteBarrier();
	*(int *)m_objectName = 0;
	m_fx = 0;
	m_cloudBreakRadius = radius;
	float spacing = g_objectSpacingDefault;
	m_spacing = spacing;
}

// ?g_objectSpacingDefault@@3MA: matched references place it at VA 0xbc292c; also referenced as _kF7C.
float g_objectSpacingDefault = 1e+02f;
#pragma comment(linker, "/alternatename:_kF7C=?g_objectSpacingDefault@@3MA")
// ?g_cloudBreakRadiusDefault@@3MA: the global at VA 0xbc2428 is ?g_Va00BC2428@@3MA.
#pragma comment(linker, "/alternatename:?g_cloudBreakRadiusDefault@@3MA=?g_Va00BC2428@@3MA")

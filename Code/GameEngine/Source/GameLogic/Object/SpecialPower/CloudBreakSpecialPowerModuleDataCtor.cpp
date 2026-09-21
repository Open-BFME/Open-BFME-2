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
	m_vtable = reinterpret_cast<void *>(0x00C5D468);
	_ReadWriteBarrier();
	m_sunbeamObject = 0;
	m_cloudBreakFX = 0;
	m_cloudBreakRadius = radius;
	float spacing = g_objectSpacingDefault;
	m_objectSpacing = spacing;
}

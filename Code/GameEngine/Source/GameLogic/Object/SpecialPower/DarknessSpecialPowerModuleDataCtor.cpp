// cl: /O1 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0DarknessSpecialPowerModuleData@@QAE@XZ, retail 0x004C4F63, 38 bytes.
// Frameless small ctor: runs the pinned opaque intermediate base ctor at
// 0x4930A0, nulls DarknessFX at +0x80, installs vtable 0x00C5E7A8 (folded
// with the GrabPassenger ModuleData vtable) and loads DarknessRadius at
// +0x7C from the shared 10.0f constant at 0x00BC2428 (see the pinned
// buildFieldParse proc holding DarknessRadius plus DarknessFX). The TU-local
// base keeps an explicit vtable slot plus pad to 0x7C (ReflectDamage
// precedent, so no vtable is emitted); the absolute float stays extern so it
// keeps the movss form (Rain precedent), materialized into a named local
// first so the load hoists above the stores. Size 0x84 matches the rowed
// 0x251FFC factory news. Row supersedes the ctor pin.

class Rva004930A0
{
public:
	Rva004930A0();

	void *m_vtable; // +0
	unsigned char m_pad[0x7C - 4]; // +4..0x7B
};

extern float g_darknessRadiusDefault; // 0x00BC2428, 10.0f

class DarknessSpecialPowerModuleData : public Rva004930A0
{
public:
	DarknessSpecialPowerModuleData();

private:
	float m_darknessRadius; // +0x7C
	void *m_darknessFX; // +0x80
};

// ??0DarknessSpecialPowerModuleData@@QAE@XZ @0x4C4F63
DarknessSpecialPowerModuleData::DarknessSpecialPowerModuleData()
	: Rva004930A0()
{
	float radius = g_darknessRadiusDefault;
	m_darknessFX = 0;
	m_vtable = reinterpret_cast<void *>(0x00C5E7A8);
	m_darknessRadius = radius;
}

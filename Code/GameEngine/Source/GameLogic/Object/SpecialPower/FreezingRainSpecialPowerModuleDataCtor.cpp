// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0FreezingRainSpecialPowerModuleData@@QAE@XZ, retail 0x004C4D71, 45 bytes.
// Frameless small ctor: runs the pinned opaque intermediate base ctor at
// 0x4930A0, nulls FreezingRainFX at +0x80, zeroes BurnRateModifier at +0x84,
// installs vtable 0x00C5E7A8 (folded across the weather ModuleData) and loads
// FreezingRainRadius at +0x7C from the shared 10.0f constant at 0x00BC2428
// (see the pinned buildFieldParse proc holding FreezingRainRadius plus
// FreezingRainFX plus BurnRateModifier). The TU-local base keeps an explicit
// vtable slot plus pad to 0x7C (ReflectDamage precedent, so no vtable is
// emitted); the absolute float stays extern so it keeps the movss form,
// materialized into a named local first so the load hoists above the stores
// (Darkness precedent). Size 0x88 matches the rowed 0x251F70 factory news.
// Row supersedes the ctor pin.

extern "C" const void *const vtbl_00C5E7A8[];  // folded, 2 classes; via ??_7CombineHordeSpecialPowerModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C5E7A8=??_7CombineHordeSpecialPowerModuleData@@6B@")

class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();

	void *m_vtable; // +0
	unsigned char m_pad[0x7C - 4]; // +4..0x7B
};


class FreezingRainSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	FreezingRainSpecialPowerModuleData();

private:
	float m_freezingRainRadius; // +0x7C
	void *m_freezingRainFX; // +0x80
	int m_burnRateModifier; // +0x84
};

// ??0FreezingRainSpecialPowerModuleData@@QAE@XZ @0x4C4D71
FreezingRainSpecialPowerModuleData::FreezingRainSpecialPowerModuleData()
	: SpecialPowerModuleData()
{
	float radius = 10.0f;
	m_freezingRainFX = 0;
	m_burnRateModifier = 0;
	m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00C5E7A8));
	m_freezingRainRadius = radius;
}

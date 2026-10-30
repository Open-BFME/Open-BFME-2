// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0FreezingRainSpecialPowerModuleData@@QAE@XZ, retail 0x004C4D71, 45 bytes.
// Frameless small ctor: runs the pinned opaque intermediate base ctor at
// 0x4930A0, nulls FreezingRainFX at +0x80, zeroes BurnRateModifier at +0x84,
// installs vtable 0x00C5E7A8 (folded across the weather ModuleData) and loads
// FreezingRainRadius at +0x7C from the shared 10.0f constant at 0x00BC2428
// (see the pinned buildFieldParse proc holding FreezingRainRadius plus
// FreezingRainFX plus BurnRateModifier). The base has a virtual destructor
// and size 0x7C; the 10.0f radius uses the shared movss constant load,
// materialized into a named local first so the load hoists above the stores
// (Darkness precedent). Size 0x88 matches the rowed 0x251F70 factory news.
// Row supersedes the ctor pin.


class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_pad[0x7C - 4];
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
	m_freezingRainRadius = radius;
}

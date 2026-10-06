// cl: /DNDEBUG /MD
//
// ??0GloriousChargeUpdateModuleData@@QAE@XZ, retail 0x004AD4F2 (43 bytes).
// Frameless Update-side ModuleData for the glorious charge: runs the pinned
// SpecialAbilityUpdateModuleData base ctor (0x44EB54), installs the explicit vtable 0xC5F778,
// zeroes the SpeechDuration and UpdateInterval words and sets the
// BonusRadius float matching the rowed chained proc's table 0x008550C8
// (BonusRadius at +0xC8, SpeechDuration at +0xCC, UpdateInterval at +0xD0).
// Flat classes throughout (no declared dtors anywhere) keep the body
// frameless; /O1 keeps the integer zeros as the compact and form and
// /arch:SSE keeps the float zero as xorps plus movss. The
// GloriousChargeUpdate pool key at 0x4AD5CE sits in the same cluster; the
// ctor ends where the rowed proc at 0x4AD51D begins and the ModuleData
// factory at 0x24F61B (news 0xD4) is the only raw caller. Supersedes the
// 0x4AD4F2 ctor pin (row proves the body).

extern "C" const void *const vtbl_00C5F778[];  // folded, 3 classes; via ??_7EvacuateGarrisonSpecialPowerModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C5F778=??_7EvacuateGarrisonSpecialPowerModuleData@@6B@")

class SpecialAbilityUpdateModuleData
{
public:
	SpecialAbilityUpdateModuleData();

private:
	unsigned char m_pad[0xC8];
};

class GloriousChargeUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	GloriousChargeUpdateModuleData();

private:
	float m_bonusRadius; // +0xC8
	int m_speechDuration; // +0xCC
	int m_updateInterval; // +0xD0
};

// ??0GloriousChargeUpdateModuleData@@QAE@XZ @0x4AD4F2
GloriousChargeUpdateModuleData::GloriousChargeUpdateModuleData()
	: SpecialAbilityUpdateModuleData()
{
	*(unsigned int *)this = ((unsigned int)vtbl_00C5F778);
	m_bonusRadius = 0.0f;
	m_speechDuration = 0;
	m_updateInterval = 0;
}

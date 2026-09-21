// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0PassiveAreaEffectBehaviorModuleData@@QAE@XZ, retail 0x00484DF4,
// 153 bytes. ModuleData-side ctor in the PassiveAreaEffect file-unit:
// EffectRadius at +8 defaults to the 200.0 pool float, HealPercentPerSecond
// at +C is 0.0, PingDelay at +10 is 15, the ModifierName vector at +14
// builds through the AsciiString Vector_base alias (0x211E58) and is
// cleared, the AllowFilter member at +20 builds through the pinned 0x3623E5
// ctor, UpgradeRequired at +24 and NonStackable at +28 are zero, the
// AntiCategories member at +2C builds through the pinned 0x3B31AD
// construct and is memcoded, AntiFX at +30 and HealFX at +34 are zero.
// Table 0xC4A388 carries all ten fields at these offsets; factory 0x24C724
// news 0x38 with this ctor as sole caller. Shape follows CrateCollide
// (empty UpdateModuleData base with declared-only dtor driving the EH
// frame, explicit vtable first member, all-init-list) over AODCrush
// (0x3623E5 filter member) and SpawnBehavior (vector<AsciiString> member
// plus clear).

#include <vector>
#include <string.h>

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();

	unsigned char m_data[4];
};

class Rva003B31ADMember
{
public:
	Rva003B31ADMember();

private:
	int m_handle;
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class PassiveAreaEffectBehaviorModuleData : public UpdateModuleData
{
public:
	PassiveAreaEffectBehaviorModuleData();

private:
	const void *m_vtable; // +0x00
	unsigned int m_unused04; // +0x04, unstored gap
	float m_effectRadius; // +0x08
	float m_healPercentPerSecond; // +0x0C
	int m_pingDelay; // +0x10
	_STL::vector<AsciiString> m_modifierName; // +0x14
	Rva003623E5Member m_allowFilter; // +0x20
	AsciiString m_upgradeRequired; // +0x24, inline-zeroed string (silent EH state)
	bool m_nonStackable; // +0x28
	unsigned char m_pad29[3];
	Rva003B31ADMember m_antiCategories; // +0x2C
	int m_antiFX; // +0x30
	int m_healFX; // +0x34
};

// ??0PassiveAreaEffectBehaviorModuleData@@QAE@XZ @0x484DF4
PassiveAreaEffectBehaviorModuleData::PassiveAreaEffectBehaviorModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C4A490))
	, m_effectRadius(200.0f)
	, m_healPercentPerSecond(0.0f)
	, m_pingDelay(15)
	, m_upgradeRequired()
	, m_nonStackable(false)
	, m_antiFX(0)
	, m_healFX(0)
{
	m_modifierName.clear();
	memset(&m_antiCategories, 0, 4);
}

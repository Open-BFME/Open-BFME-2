// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0AttributeModifierAuraUpdateModuleData@@QAE@XZ, retail 0x0049BBD5,
// 206 bytes. Aura-side ModuleData for attribute-modifier auras. Identity is
// the own table at 0x00C50DC8 (BonusName at +0x8 plus RefreshDelay at +0x18
// plus Range at +0x1C plus AllowPowerWhenAttacking at +0x20 plus TargetEnemy
// at +0x21 plus ObjectFilter at +0x24 plus StartsActive at +0x138 plus
// RequiredConditions at +0x13C plus AntiCategory at +0x140) matching every
// store below, plus the rowed AttributeModifierAuraUpdate pool key at
// 0x49B5DC in the same cluster, plus the chained buildFieldParse at
// 0x49BBB3 and the ModuleData factory at 0x24E65C which news 0x154.
// Shape follows GrantUpgradeCreateModuleDataCtor (explicit vtable first
// member plus empty base plus null-plus-set string) plus ChinookAIUpdate
// (Rva0025342CMember construct at +0x28) plus BattlePlanUpdate (BfmeE16
// vector at +0xC via 0x211E58) plus AnimationSteering (opaque 0x3623E5 pin
// for the +0x24 filter). The +0x140 AntiCategory head constructs through
// the pinned 0x3B31AD construct (4B zeroing member) then memsets the same
// 4 bytes; the trailing +0x144 to +0x150 zeros are explicit stores.

#include <vector>
#include <cstring>

struct BfmeE16 { float x, y, z, w; };

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	~StringBase();
	void set(const char *str);

private:
	void *m_data;
};

typedef StringBase<char> AsciiString;

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();

private:
	char m_data[4];
};

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();

private:
	unsigned char m_pad[0x110];
};

class Rva003B31ADMember
{
public:
	Rva003B31ADMember *construct();

private:
	int m_value;
};

class UpdateBase
{
public:
	UpdateBase() {}
	~UpdateBase();
};

class AttributeModifierAuraUpdateModuleData : public UpdateBase
{
public:
	AttributeModifierAuraUpdateModuleData();
	~AttributeModifierAuraUpdateModuleData();

private:
	const void *m_vtable;
	unsigned int m_unused04;
	AsciiString m_bonusName; // +0x08
	_STL::vector<BfmeE16> m_vec0C; // +0x0C
	int m_refreshDelay; // +0x18
	float m_range; // +0x1C
	bool m_allowPower; // +0x20
	bool m_targetEnemy; // +0x21
	unsigned char m_pad22[2];
	Rva003623E5Member m_filter24; // +0x24
	Rva0025342CMember m_member28; // +0x28
	bool m_startsActive; // +0x138
	unsigned char m_pad139[3];
	int m_requiredConditions; // +0x13C
	Rva003B31ADMember m_antiFirst; // +0x140
	int m_anti144; // +0x144
	bool m_anti148; // +0x148
	bool m_anti149; // +0x149
	bool m_anti14A; // +0x14A
	bool m_anti14B; // +0x14B
	bool m_anti14C; // +0x14C
	unsigned char m_pad14D[3];
	int m_anti150; // +0x150
};

// ??0AttributeModifierAuraUpdateModuleData@@QAE@XZ @0x49BBD5
AttributeModifierAuraUpdateModuleData::AttributeModifierAuraUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C50EE8))
	, m_bonusName()
	, m_vec0C()
{
	m_member28.construct();
	m_antiFirst.construct();
	m_bonusName.set("");
	m_refreshDelay = 1;
	m_range = 0.0f;
	m_allowPower = true;
	m_targetEnemy = false;
	m_startsActive = false;
	m_requiredConditions = 0;
	memset(&m_antiFirst, 0, 4);
	m_anti144 = 0;
	m_anti148 = false;
	m_anti149 = false;
	m_anti14A = false;
	m_anti14B = false;
	m_anti14C = false;
	m_anti150 = 0;
}

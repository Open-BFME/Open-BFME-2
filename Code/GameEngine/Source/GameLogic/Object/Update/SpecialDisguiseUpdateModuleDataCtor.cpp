// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0SpecialDisguiseUpdateModuleData@@QAE@XZ, retail 0x004B0255, 61 bytes.
// Disguise module data ctor over the pinned Rva0044EB54 base (0x44EB54,
// 0xC8 bytes): installs vtable 0x00C563F8 explicitly (novtable, no compiler
// emission), clears DisguiseAsTemplate/EnemyPerspective/DisguiseFX at
// +0xD0/+0xD4/+0xD8, clears TriggerInstantlyOnCreate at +0xC8 and
// ForceMountedWhenDisguising at +0xDC, and zeroes OpacityTarget at +0xCC
// via xorps float zero (/arch:SSE emits retail movss). Table 0x00BEF8B8
// proves the six fields at identical offsets; factory 0x24F9D8 (news 0xE0,
// sole caller) proves the class size. Row supersedes the ctor pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class __declspec(novtable) Rva0044EB54
{
public:
	Rva0044EB54();
	virtual ~Rva0044EB54();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x00 vptr (novtable: no compiler install here).
	// Remainder is opaque (0xC4 bytes); only the 0xC8 size matters.
	unsigned char m_opaque[0xC4];
};

class __declspec(novtable) SpecialDisguiseUpdateModuleData : public Rva0044EB54
{
public:
	SpecialDisguiseUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0xC8 TriggerInstantlyOnCreate (table offset).
	bool m_triggerInstantlyOnCreate;
	// +0xC9 pad.
	unsigned char m_padC9[3];
	// +0xCC OpacityTarget (table offset).
	float m_opacityTarget;
	// +0xD0 DisguiseAsTemplate (table offset).
	int m_disguiseAsTemplate;
	// +0xD4 DisguisedAsTemplate_EnemyPerspective (table offset).
	int m_disguisedAsEnemy;
	// +0xD8 DisguiseFX (table offset).
	int m_disguiseFX;
	// +0xDC ForceMountedWhenDisguising (table offset).
	bool m_forceMounted;
	// +0xDD pad to the 0xE0 factory size.
	unsigned char m_padDD[3];
};

// ??0SpecialDisguiseUpdateModuleData@@QAE@XZ @0x004B0255
SpecialDisguiseUpdateModuleData::SpecialDisguiseUpdateModuleData()
	: Rva0044EB54()
{
	int *disguiseAsTemplate = &m_disguiseAsTemplate;
	*(unsigned int *)this = 0x00C563F8;
	*disguiseAsTemplate = 0;
	m_disguisedAsEnemy = 0;
	m_triggerInstantlyOnCreate = false;
	m_disguiseFX = 0;
	m_forceMounted = false;
	m_opacityTarget = 0.0f;
}

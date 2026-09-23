// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0ArrowStormUpdateModuleData@@QAE@XZ, retail 0x00490639, 64 bytes.
// ModuleData ctor over the pinned Rva0044EB54 base (0x44EB54, 0xC8 bytes
// per the ToggleHidden row): installs vtable 0x00C4D5A0 explicitly
// (novtable, no compiler emission), clears WeaponTemplate at +0xC8
// (and-RMW stays first per the ScaleWall precedent), zeroes TargetRadius
// at +0xCC via xorps float zero (/arch:SSE emits retail movss), sets
// ShotsPerTarget/ShotsPerBurst/MaxShots at +0xD0/+0xD4/+0xD8 to 1, and
// clears CanShootEmptyGround at +0xDC. Table 0x00BEEE08 proves the six
// fields at identical offsets; factory 0x24D601 (news 0xE0, sole caller)
// proves the class size. Row supersedes the ctor pin.

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

class __declspec(novtable) ArrowStormUpdateModuleData : public Rva0044EB54
{
public:
	ArrowStormUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0xC8 WeaponTemplate (table offset).
	int m_weaponTemplate;
	// +0xCC TargetRadius (table offset).
	float m_targetRadius;
	// +0xD0 ShotsPerTarget (table offset).
	int m_shotsPerTarget;
	// +0xD4 ShotsPerBurst (table offset).
	int m_shotsPerBurst;
	// +0xD8 MaxShots (table offset).
	int m_maxShots;
	// +0xDC CanShootEmptyGround (table offset).
	bool m_canShootEmptyGround;
	// +0xDD pad to the 0xE0 factory size.
	unsigned char m_padDD[3];
};

// ??0ArrowStormUpdateModuleData@@QAE@XZ @0x00490639
ArrowStormUpdateModuleData::ArrowStormUpdateModuleData()
	: Rva0044EB54()
{
	int *weaponTemplate = &m_weaponTemplate;
	*(unsigned int *)this = 0x00C4D5A0;
	*weaponTemplate &= 0;
	m_shotsPerTarget = 1;
	m_shotsPerBurst = 1;
	m_maxShots = 1;
	m_targetRadius = 0.0f;
	m_canShootEmptyGround = false;
}

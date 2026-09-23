// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0TeleportSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x00492E43, 54 bytes.
// ModuleData ctor over the pinned Rva0044EB54 base (0x44EB54, 0xC8 bytes
// per the ArrowStorm row): installs vtable 0x00C4E208 explicitly
// (novtable, no compiler emission), zeroes BusyForDuration at +0xC8,
// DestinationWeaponName at +0xCC and SourceWeaponName at +0xD0, and sets
// MaxDistance at +0xD4 to -1.0f (pools to 0x00BBB9AC via /arch:SSE movss).
// Table 0x00BEF150 proves the four fields at identical offsets; factory
// 0x24DC00 (news 0xD8, sole caller) proves the class size. Row supersedes
// the ctor pin.

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

class __declspec(novtable) TeleportSpecialAbilityUpdateModuleData : public Rva0044EB54
{
public:
	TeleportSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0xC8 BusyForDuration (table offset).
	int m_busyForDuration;
	// +0xCC DestinationWeaponName (table offset).
	int m_destinationWeaponName;
	// +0xD0 SourceWeaponName (table offset).
	int m_sourceWeaponName;
	// +0xD4 MaxDistance (table offset).
	float m_maxDistance;
};

// ??0TeleportSpecialAbilityUpdateModuleData@@QAE@XZ @0x00492E43
TeleportSpecialAbilityUpdateModuleData::TeleportSpecialAbilityUpdateModuleData()
	: Rva0044EB54()
{
	m_busyForDuration = 0;
	*(unsigned int *)this = 0x00C4E208;
	int *destinationWeaponName = &m_destinationWeaponName;
	int *sourceWeaponName = &m_sourceWeaponName;
	*destinationWeaponName = 0;
	*sourceWeaponName = 0;
	m_maxDistance = -1.0f;
}

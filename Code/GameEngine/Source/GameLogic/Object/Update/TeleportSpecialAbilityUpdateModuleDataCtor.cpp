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

// Retail VA 0x00C4E208 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void vfn_00065212();
extern "C" void vfn_000B3FD0();
extern "C" void vfn_000B69A1();
extern "C" void vfn_000D43D0();
extern "C" void vfn_0047A699();
extern "C" void vfn_0047A69C();
extern "C" void vfn_00492EFD();
extern "C" void vfn_0050B5C6();
#pragma comment(linker, "/alternatename:_vfn_00065212=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:_vfn_000B3FD0=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_000B69A1=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:_vfn_000D43D0=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A699=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:_vfn_0047A69C=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:_vfn_00492EFD=??_GTeleportSpecialAbilityUpdateModuleData@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B5C6=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" const void *const vtbl_00C4E208[] = {
	(const void *)&vfn_00492EFD,
	(const void *)&vfn_000B3FD0,
	(const void *)&vfn_00065212,
	(const void *)&vfn_0047A69C,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_000B69A1,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_0050B5C6
};

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
	*(unsigned int *)this = ((unsigned int)vtbl_00C4E208);
	int *destinationWeaponName = &m_destinationWeaponName;
	int *sourceWeaponName = &m_sourceWeaponName;
	*destinationWeaponName = 0;
	*sourceWeaponName = 0;
	m_maxDistance = -1.0f;
}

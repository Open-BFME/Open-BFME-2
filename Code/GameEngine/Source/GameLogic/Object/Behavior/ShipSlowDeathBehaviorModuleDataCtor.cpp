// cl: /O1 /DNDEBUG /MD
//
// ??0ShipSlowDeathBehaviorModuleData@@QAE@XZ, retail 0x0045E961, 18 bytes.
// ModuleData ctor over the pinned SlowDeathBehaviorModuleData base
// (0x45E386): installs vtable 0x00C42E98 explicitly (novtable; no new
// members initialized here). Class size 0x190 proven by the
// ShipSlowDeathBehavior data factory (news 0x190, sole caller at 0x24B34C).
// Row supersedes the ctor pin.

// Retail VA 0x00C42E98 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void vfn_00065212();
extern "C" void vfn_000B3FD0();
extern "C" void vfn_000B69A1();
extern "C" void vfn_000D43D0();
extern "C" void vfn_0045E98E();
extern "C" void vfn_0047A699();
extern "C" void vfn_0047A69C();
extern "C" void vfn_0050B5C6();
#pragma comment(linker, "/alternatename:_vfn_00065212=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:_vfn_000B3FD0=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_000B69A1=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:_vfn_000D43D0=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:_vfn_0045E98E=??_GShipSlowDeathBehaviorModuleData@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A699=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:_vfn_0047A69C=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B5C6=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" const void *const vtbl_00C42E98[] = {
	(const void *)&vfn_0045E98E,
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
extern const int g_emptyFieldParseTable[4];

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class __declspec(novtable) SlowDeathBehaviorModuleData
{
public:
	SlowDeathBehaviorModuleData();
	virtual ~SlowDeathBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x00 vptr (novtable: no compiler install here).
	// Remainder is opaque (0x18C bytes); only the 0x190 size matters.
	unsigned char m_opaque[0x18C];
};

class __declspec(novtable) ShipSlowDeathBehaviorModuleData : public SlowDeathBehaviorModuleData
{
public:
	ShipSlowDeathBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ??0ShipSlowDeathBehaviorModuleData@@QAE@XZ @0x0045E961
ShipSlowDeathBehaviorModuleData::ShipSlowDeathBehaviorModuleData()
	: SlowDeathBehaviorModuleData()
{
	*(unsigned int *)this = ((unsigned int)vtbl_00C42E98);
}

// ?buildFieldParse@ShipSlowDeathBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0045E973
void ShipSlowDeathBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SlowDeathBehaviorModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable), 0);
}

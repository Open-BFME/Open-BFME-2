// cl: /O1 /DNDEBUG /MD
//
// ??0ShipSlowDeathBehaviorModuleData@@QAE@XZ, retail 0x0045E961, 18 bytes.
// ModuleData ctor over the pinned SlowDeathBehaviorModuleData base
// (0x45E386): installs vtable 0x00C42E98 explicitly (novtable; no new
// members initialized here). Class size 0x190 proven by the
// ShipSlowDeathBehavior data factory (news 0x190, sole caller at 0x24B34C).
// Row supersedes the ctor pin.

class MultiIniFieldParse;
struct FieldParse;

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
	*(unsigned int *)this = 0x00C42E98;
}

// ?buildFieldParse@ShipSlowDeathBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0045E973
void ShipSlowDeathBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SlowDeathBehaviorModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C6BB18), 0);
}

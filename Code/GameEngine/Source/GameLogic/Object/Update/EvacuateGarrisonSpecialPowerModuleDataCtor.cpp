// cl: /O1 /MD /DNDEBUG
// ??0EvacuateGarrisonSpecialPowerModuleData@@QAE@XZ at retail 0x004CDFD9.
// Default ctor over the second intermediate base 0x0044EB54 (pinned opaque
// as SpecialAbilityUpdateModuleData, 0xC8 bytes). No trailing members (factory size 0xC8).
// Target identity: ModuleFactory registers the data factories 0x2531B0
// (EvacuateGarrisonSpecialPower) and 0x25327A (UnleashSpecialPower); both new
// 0xC8 with this one folded ctor (vtable 0x00C5F778). Named after the
// lower-address registration. Do NOT declare an explicit vptr member.
struct FieldParse
{
	const char *m_token;
	void *m_parse;
	const void *m_userData;
	int m_offset;
};

// Both retail parse procs reference the existing empty table at VA 0x00C6BB18.
extern const int g_emptyFieldParseTable[4];

class MultiIniFieldParse
{
public:
	void add(const FieldParse *f, unsigned int extraOffset);
};

class SpecialAbilityUpdateModuleData
{
public:
	SpecialAbilityUpdateModuleData();
	virtual ~SpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &p);

protected:
	unsigned char m_pad[0xC8 - 4];
};

class EvacuateGarrisonSpecialPowerModuleData : public SpecialAbilityUpdateModuleData
{
public:
	EvacuateGarrisonSpecialPowerModuleData();
	virtual ~EvacuateGarrisonSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &p);
};

class UnleashSpecialPowerModuleData : public SpecialAbilityUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};

EvacuateGarrisonSpecialPowerModuleData::EvacuateGarrisonSpecialPowerModuleData()
	: SpecialAbilityUpdateModuleData()
{
}

// ??1EvacuateGarrisonSpecialPowerModuleData@@UAE@XZ present-unmatched
EvacuateGarrisonSpecialPowerModuleData::~EvacuateGarrisonSpecialPowerModuleData()
{
}

// Target registration: factory 0x002531B0 passes this proc at VA 0x008CDBE1
// for EvacuateGarrisonSpecialPower; the body extends the shared base parser
// with an empty table and no member offsets.
// ?buildFieldParse@EvacuateGarrisonSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004CDBE1
void EvacuateGarrisonSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &multiIniFieldParse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(multiIniFieldParse);
	multiIniFieldParse.add(reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable), 0);
}

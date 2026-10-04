// cl: /O1 /DNDEBUG /MD
//
// ??0ToggleHiddenSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x004AE155,
// 25 bytes. ModuleData ctor over the pinned Rva0044EB54 base (0x44EB54):
// installs vtable 0x00C5F778 explicitly (novtable) and zeroes the +0xC8
// flag. Class size 0xCC proven by the ToggleHiddenSpecialAbilityUpdate data
// factory (news 0xCC, sole caller at 0x24F793); base size 0xC8 inferred from
// the flag position. Row supersedes the ctor pin.

extern "C" const void *const vtbl_00C5F778[];  // folded, 3 classes; via ??_7EvacuateGarrisonSpecialPowerModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C5F778=??_7EvacuateGarrisonSpecialPowerModuleData@@6B@")

class MultiIniFieldParse;
class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00BEF7E4 (.rdata): 1 field records and a zero sentinel.
extern const FieldParse g_00BEF7E4[] = {
	{ "ShowPalantirTimer", &INI::parseBool, 0, 0xC8 },
	{ 0, 0, 0, 0 }
};

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

class __declspec(novtable) ToggleHiddenSpecialAbilityUpdateModuleData : public Rva0044EB54
{
public:
	ToggleHiddenSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0xC8 flag (false).
	bool m_flagC8;
	char m_padC9[3]; // to the rowed 0xCC instance size
};

// ??0ToggleHiddenSpecialAbilityUpdateModuleData@@QAE@XZ @0x004AE155
ToggleHiddenSpecialAbilityUpdateModuleData::ToggleHiddenSpecialAbilityUpdateModuleData()
	: Rva0044EB54()
{
	*(unsigned int *)this = ((unsigned int)vtbl_00C5F778);
	m_flagC8 = false;
}

// ?buildFieldParse@ToggleHiddenSpecialAbilityUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0024F719
void ToggleHiddenSpecialAbilityUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(g_00BEF7E4, 0);
}

// cl: /O1 /DNDEBUG /MD
//
// ??0ScaleWallSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x00494DB1,
// 25 bytes. ModuleData ctor over the pinned Rva0044EB54 base (0x44EB54):
// clears the +0xC8 word (and-RMW) and installs vtable 0x00C5F778
// explicitly (novtable; shares the ToggleHidden vtable). Class size 0xCC
// proven by the ScaleWallSpecialAbilityUpdate data factory (news 0xCC, sole
// caller at 0x24DDEC); base size 0xC8 inferred from the +0xC8 position. Row
// supersedes the ctor pin.

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
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00BEF1B4 (.rdata): 1 field records and a zero sentinel.
extern const FieldParse g_00BEF1B4[] = {
	{ "DelayAtFootOfWall", &INI::parseDurationUnsignedInt, 0, 0xC8 },
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

class __declspec(novtable) ScaleWallSpecialAbilityUpdateModuleData : public Rva0044EB54
{
public:
	ScaleWallSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0xC8 cleared word (ends at the rowed 0xCC instance size).
	unsigned int m_wordC8;
};

// ??0ScaleWallSpecialAbilityUpdateModuleData@@QAE@XZ @0x00494DB1
ScaleWallSpecialAbilityUpdateModuleData::ScaleWallSpecialAbilityUpdateModuleData()
	: Rva0044EB54()
{
	m_wordC8 &= 0;
	*(unsigned int *)this = ((unsigned int)vtbl_00C5F778);
}

// ?buildFieldParse@ScaleWallSpecialAbilityUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0024DD72
void ScaleWallSpecialAbilityUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(g_00BEF1B4, 0);
}

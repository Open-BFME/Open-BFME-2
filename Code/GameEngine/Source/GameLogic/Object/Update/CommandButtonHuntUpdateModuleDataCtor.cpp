// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0CommandButtonHuntUpdateModuleData@@QAE@XZ, retail 0x0049529F, 31 bytes.
// Root ModuleData ctor (no base call): installs vtable 0x00C4ED70
// explicitly, copies the +8 word from global 0x00DBA4E4 (DIR32-masked
// absolute load) and stores the 99999.0f-style 9999.0f cap at +0x0C
// (literal pool VA 0xC0215C; /arch:SSE emits retail movss). The float local
// sources the literal load ahead of the vtable install (Enraged precedent).
// Class size 0x10 proven by the CommandButtonHuntUpdate data factory
// (news 0x10, sole caller at 0x24DFA8). Row supersedes the ctor pin.

// Global word copied into +8 (absolute VA 0x00DBA4E4, DIR32-masked).
extern "C" const void *const vtbl_00C4ED70[];  // folded, 9 classes; via ??_7BeaconClientUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4ED70=??_7BeaconClientUpdateModuleData@@6B@")

extern int g_Va00DBA4E4;

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
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00C4ECC0 (.rdata): 2 field records and a zero sentinel.
extern const FieldParse g_00C4ECC0[] = {
	{ "ScanRate", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "ScanRange", &INI::parseReal, 0, 0xC },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class CommandButtonHuntUpdateModuleData
{
public:
	CommandButtonHuntUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x00 vtable (installed explicitly below; no base, no virtuals here).
	const void *m_vtable;
	// +0x04 opaque pad (untouched by this ctor).
	unsigned int m_pad04;
	// +0x08 word from the global.
	int m_08;
	// +0x0C cap value.
	float m_cap;
};

// ??0CommandButtonHuntUpdateModuleData@@QAE@XZ @0x0049529F
CommandButtonHuntUpdateModuleData::CommandButtonHuntUpdateModuleData()
{
	float cap = 9999.0f;
	*(unsigned int *)this = ((unsigned int)vtbl_00C4ED70);
	m_08 = g_Va00DBA4E4;
	m_cap = cap;
}

// ?buildFieldParse@CommandButtonHuntUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004952BE
void CommandButtonHuntUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_00C4ECC0, 0);
}

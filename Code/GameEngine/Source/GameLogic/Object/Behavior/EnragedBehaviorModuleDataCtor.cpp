// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0EnragedBehaviorModuleData@@QAE@XZ, retail 0x00458F7C, 22 bytes.
// Root ModuleData ctor (no base call): installs vtable 0x00C4ED70
// explicitly and stores the 99999.0f cap at +8 (literal pool VA 0xBC93FC;
// /arch:SSE emits retail movss). The float local sources the literal load
// ahead of the vtable install. Class size 0x0C proven by the EnragedBehavior
// data factory (news 0x0C, sole caller at 0x24ADE2). Row supersedes the
// ctor pin.

extern "C" const void *const vtbl_00C4ED70[];  // folded, 9 classes; via ??_7BeaconClientUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4ED70=??_7BeaconClientUpdateModuleData@@6B@")

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
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00C40F90 (.rdata): 1 field records and a zero sentinel.
extern const FieldParse g_00C40F90[] = {
	{ "EnragedLifeTimer", &INI::parseReal, 0, 0x8 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class EnragedBehaviorModuleData
{
public:
	EnragedBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x00 vtable (installed explicitly below; no base, no virtuals here).
	const void *m_vtable;
	// +0x04 opaque pad (untouched by this ctor).
	unsigned int m_pad04;
	// +0x08 cap value.
	float m_cap;
};

// ??0EnragedBehaviorModuleData@@QAE@XZ @0x00458F7C
EnragedBehaviorModuleData::EnragedBehaviorModuleData()
{
	float cap = 99999.0f;
	*(unsigned int *)this = ((unsigned int)vtbl_00C4ED70);
	m_cap = cap;
}

// ?buildFieldParse@EnragedBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00458F92
void EnragedBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_00C40F90, 0);
}

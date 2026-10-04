// cl: /O1 /DNDEBUG /MD
//
// ??0W3DBuffDrawModuleData@@QAE@XZ, retail 0x000CEE4C, 17 bytes.
// Root ModuleData ctor (no base call): installs vtable 0x00BCD270
// explicitly, clears the +8 word (and-RMW) and zeroes the +0x0C flag.
// A barrier pins the and-RMW below the vtable install (bare and-RMW hoists
// above the plain mov). Class size 0x10 proven by the rowed W3DBuffDraw data
// factory 0x64C94 (news 0x10, sole caller). Row supersedes the ctor pin.

extern "C" const void *const vtbl_00BCD270[];  // ??_7W3DBuffDrawModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BCD270=??_7W3DBuffDrawModuleData@@6B@")

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

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
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00BCD2F4 (.rdata): 2 field records and a zero sentinel.
extern const FieldParse g_00BCD2F4[] = {
	{ "ModelName", &INI::parseAsciiString, 0, 0x8 },
	{ "PreDraw", &INI::parseBool, 0, 0xC },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class W3DBuffDrawModuleData
{
public:
	W3DBuffDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x00 vtable (installed explicitly below; no base, no virtuals here).
	const void *m_vtable;
	// +0x04 opaque pad (untouched by this ctor).
	unsigned int m_pad04;
	// +0x08 cleared word.
	unsigned int m_08;
	// +0x0C flag (false).
	bool m_0C;
	char m_pad0D[3]; // to the rowed 0x10 instance size
};

// ??0W3DBuffDrawModuleData@@QAE@XZ @0x000CEE4C
W3DBuffDrawModuleData::W3DBuffDrawModuleData()
{
	*(unsigned int *)this = ((unsigned int)vtbl_00BCD270);
	_ReadWriteBarrier();
	m_08 &= 0;
	m_0C = false;
}

// ?buildFieldParse@W3DBuffDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x000CEE93
void W3DBuffDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_00BCD2F4, 0);
}

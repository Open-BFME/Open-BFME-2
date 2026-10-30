// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// ??0W3DBuffDrawModuleData@@QAE@XZ, retail 0x000CEE4C, 17 bytes.
// Root ModuleData ctor (no base call): installs vtable 0x00BCD270
// before initializing the AsciiString at +8 and the flag at +0x0C.
// Class size 0x10 proven by the rowed W3DBuffDraw data
// factory 0x64C94 (news 0x10, sole caller). Row supersedes the ctor pin.

#include "ascii_string.h"

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

class W3DBuffDrawModuleDataBase
{
public:
	virtual ~W3DBuffDrawModuleDataBase() {}

private:
	unsigned int m_word;
};

class W3DBuffDrawModuleData : public W3DBuffDrawModuleDataBase
{
public:
	W3DBuffDrawModuleData();
	virtual ~W3DBuffDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	AsciiString m_modelName; // +08
	bool m_flag; // +0C
	char m_pad0D[3];
};

// ??0W3DBuffDrawModuleData@@QAE@XZ @0x000CEE4C
W3DBuffDrawModuleData::W3DBuffDrawModuleData()
	: m_flag(false)
{
}

// ?buildFieldParse@W3DBuffDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x000CEE93
void W3DBuffDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_00BCD2F4, 0);
}

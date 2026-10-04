// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /Ireference/shims/moduledata
//
// W3DPropDrawModuleData file-unit: parse proc and constructor.
//
// ??0W3DPropDrawModuleData@@QAE@XZ, retail 0x000CEF2B, 17 bytes (pinned;
// called by the data factory 0x00064D1D). Stores vtable 0x00BCD420, nulls
// m_modelName at +0x08 and sets the byte at +0x0C to 1; the rowed dtor next
// door (0x000CEF3C, W3DPropDrawModuleDataDtor.cpp) uses the same vtable and
// string slot. The Snapshot base constructor is inline and its vtable store
// is overwritten.
//
// ?buildFieldParse@W3DPropDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x000CEF72, 17 bytes. Single-table parse proc (table 0x00BCD4A8)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.

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

// Retail VA 0x00BCD4A8 (.rdata): 2 field records and a zero sentinel.
extern const FieldParse g_00BCD4A8[] = {
	{ "ModelName", &INI::parseAsciiString, 0, 0x8 },
	{ "DistanceFog", &INI::parseBool, 0, 0xC },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

#include "ascii_string.h"

#include "Common/Snapshot.h"

class W3DPropDrawModuleData : public Snapshot
{
public:
	W3DPropDrawModuleData();
	virtual ~W3DPropDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
private:
	int m_04;
	AsciiString m_modelName;
	bool m_0C;
};

// ??0W3DPropDrawModuleData@@QAE@XZ @0x000CEF2B
W3DPropDrawModuleData::W3DPropDrawModuleData() : m_0C(true)
{
}

// ?buildFieldParse@W3DPropDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x000CEF72
void W3DPropDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_00BCD4A8, 0);
}

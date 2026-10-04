// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// W3DProjectileStreamDrawModuleData file-unit (parse first; the ctor at
// 0xD11D2 remains pinned for a follow-up).
//
// ?buildFieldParse@W3DProjectileStreamDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x000D125C, 17 bytes. Single-table parse proc (table 0x00BCDFB0)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.
//
// ??0W3DProjectileStreamDrawModuleData@@QAE@XZ, retail 0x000D11D2, 84 bytes.
// MD ctor: vtable 0x00BCDF18 plus Texture string at +0x08 (inline-zero plus
// set of the empty literal through the 0x55F5 fold, null-plus-set idiom)
// plus Width at +0x0C, TileFactor at +0x10 and ScrollRate at +0x14 as float
// zeros plus MaxSegments at +0x18 as zero. The empty UpdateModuleData base
// (inline-empty ctor plus declared-only dtor) advances EH state 0 with no
// emitted code; the string member (inline ctor plus declared-only dtor)
// arms state 1. Field identity is the own table at 0x00BCDFB0. The rowed
// factory at 0x650E8 news 0x1C. Row supersedes the ctor pin.

extern "C" const void *const vtbl_00BCDF18[];  // ??_7W3DProjectileStreamDrawModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BCDF18=??_7W3DProjectileStreamDrawModuleData@@6B@")

#include "ascii_string.h"

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();
};

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
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00BCDFB0 (.rdata): 5 field records and a zero sentinel.
extern const FieldParse g_00BCDFB0[] = {
	{ "Texture", &INI::parseAsciiString, 0, 0x8 },
	{ "Width", &INI::parseReal, 0, 0xC },
	{ "TileFactor", &INI::parseReal, 0, 0x10 },
	{ "ScrollRate", &INI::parseReal, 0, 0x14 },
	{ "MaxSegments", &INI::parseInt, 0, 0x18 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class W3DProjectileStreamDrawModuleData : public UpdateModuleData
{
public:
	W3DProjectileStreamDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	const void *m_vtable;
	unsigned int m_unused04;
	AsciiString m_texture; // +0x08
	float m_width; // +0x0C
	float m_tileFactor; // +0x10
	float m_scrollRate; // +0x14
	int m_maxSegments; // +0x18
};

// ?buildFieldParse@W3DProjectileStreamDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x000D125C
void W3DProjectileStreamDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_00BCDFB0, 0);
}

// ??0W3DProjectileStreamDrawModuleData@@QAE@XZ @0x000D11D2
W3DProjectileStreamDrawModuleData::W3DProjectileStreamDrawModuleData()
	: m_vtable(reinterpret_cast<const void *>(((unsigned int)vtbl_00BCDF18)))
	, m_texture()
{
	m_texture.set("");
	m_maxSegments = 0;
	m_width = 0.0f;
	m_tileFactor = 0.0f;
	m_scrollRate = 0.0f;
}

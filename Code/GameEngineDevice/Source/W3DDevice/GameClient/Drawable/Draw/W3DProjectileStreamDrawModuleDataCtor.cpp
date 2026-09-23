// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
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

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
	void set(const char *str);

private:
	void *m_data;
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();
};

class MultiIniFieldParse;
struct FieldParse;

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
	parse.add(reinterpret_cast<const FieldParse *>(0x00BCDFB0), 0);
}

// ??0W3DProjectileStreamDrawModuleData@@QAE@XZ @0x000D11D2
W3DProjectileStreamDrawModuleData::W3DProjectileStreamDrawModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00BCDF18))
	, m_texture()
{
	m_texture.set("");
	m_maxSegments = 0;
	m_width = 0.0f;
	m_tileFactor = 0.0f;
	m_scrollRate = 0.0f;
}

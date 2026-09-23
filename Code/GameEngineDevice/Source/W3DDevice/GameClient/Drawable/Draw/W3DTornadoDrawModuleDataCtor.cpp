// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// W3DTornadoDrawModuleData file-unit (parse + ctor).
//
// ?buildFieldParse@W3DTornadoDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x000D16A3, 17 bytes. Single-table parse proc (table 0x00BCE150)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.
//
// ??0W3DTornadoDrawModuleData@@QAE@XZ, retail 0x000D16B4, 67 bytes.
// Tornado draw ModuleData ctor: RadiusDecalTemplate member at +8 builds
// through the pinned 0x330E5D ctor (BFME1 RadiusDecal.h donor class),
// DecalCount at +0x3C clears and DecalMaxRadius at +0x40 loads from the
// 0x00BCE190 pool. Table 0x00BCE150 proves the three fields at identical
// offsets; factory 0x65171 (news 0x44, sole caller) proves the class size.
// Row supersedes the ctor pin.

class MultiIniFieldParse;
struct FieldParse;

extern const float g_Va00BCE190;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();

private:
	unsigned char m_data[0x34];
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class W3DTornadoDrawModuleData : public UpdateModuleData
{
public:
	W3DTornadoDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x00 vtable (init-list store lands between the implicit base call
	// and the implicit member call per the GiantBird precedent).
	const void *m_vtable;
	// +0x04 unstored gap.
	unsigned int m_unused04;
	// +0x08 DecalTemplate (table offset, via pinned 0x330E5D).
	RadiusDecalTemplate m_decalTemplate;
	// +0x3C DecalCount (table offset).
	int m_decalCount;
	// +0x40 DecalMaxRadius (table offset).
	float m_decalMaxRadius;
};

// ??0W3DTornadoDrawModuleData@@QAE@XZ @0x000D16B4
W3DTornadoDrawModuleData::W3DTornadoDrawModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00BCE198))
{
	m_decalCount &= 0;
	m_decalMaxRadius = g_Va00BCE190;
}

// ?buildFieldParse@W3DTornadoDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x000D16A3
void W3DTornadoDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00BCE150), 0);
}

// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// W3DBoatWakeModelDrawModuleData file-unit (parse + ctor).
//
// ?buildFieldParse@W3DBoatWakeModelDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x000D0CF7, 17 bytes. Single-table parse proc (table 0x00BCDEE4)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.
//
// ??0W3DBoatWakeModelDrawModuleData@@QAE@XZ, retail 0x000D0CD8, 31 bytes.
// Root ModuleData ctor (no base call): installs vtable 0x00BCDE68
// explicitly, clears the +8 word and zeroes three floats at
// +0x0C/+0x10/+0x14 via xorps float zero (/arch:SSE emits retail
// xorps+movss). Class size 0x18 proven by the W3DBoatWakeModelDraw data
// factory (news 0x18, sole caller at 0x65080). Row supersedes the ctor pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class W3DBoatWakeModelDrawModuleData
{
public:
	W3DBoatWakeModelDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x00 vtable (installed explicitly below; no base, no virtuals here).
	const void *m_vtable;
	// +0x04 opaque pad (untouched by this ctor).
	unsigned int m_pad04;
	// +0x08 cleared word (ModelName offset per table 0xBCDEE4).
	unsigned int m_modelName;
	// +0x0C/+0x10/+0x14 float zeros (Offset table region).
	float m_offsetX;
	float m_offsetY;
	float m_offsetZ;
};

// ??0W3DBoatWakeModelDrawModuleData@@QAE@XZ @0x000D0CD8
W3DBoatWakeModelDrawModuleData::W3DBoatWakeModelDrawModuleData()
{
	unsigned int *modelName = &m_modelName;
	*(unsigned int *)this = 0x00BCDE68;
	*modelName &= 0;
	m_offsetX = 0.0f;
	m_offsetY = 0.0f;
	m_offsetZ = 0.0f;
}

// ?buildFieldParse@W3DBoatWakeModelDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x000D0CF7
void W3DBoatWakeModelDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00BCDEE4), 0);
}

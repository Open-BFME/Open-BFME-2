// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0W3DSailModelDrawModuleData@@QAE@XZ, retail 0x000D0737, 61 bytes.
// ModuleData ctor over the pinned W3DModelDrawModuleData base (0xC8EEF):
// zeroes +0x188 (xmm0-homed fzero), stores the 0.25f cap at +0x18C
// (literal pool VA 0xBBB8D4), installs vtable 0x00BC6870 explicitly
// (novtable) and stores the 0.05f cap at +0x190 (literal pool VA 0xBC7838).
// /arch:SSE emits retail xorps+movss; literal loads hoist early while plain
// stores keep program order (Enraged precedent). Class size 0x194 proven by
// the W3DSailModelDraw data factory (news 0x194, sole caller at 0x64FF7).
// Row supersedes the ctor pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class __declspec(novtable) W3DModelDrawModuleData
{
public:
	W3DModelDrawModuleData();
	virtual ~W3DModelDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x00 vptr (novtable: no compiler install here).
	// Remainder is opaque (0x184 bytes); only the 0x188 size matters.
	unsigned char m_opaque[0x184];
};

class __declspec(novtable) W3DSailModelDrawModuleData : public W3DModelDrawModuleData
{
public:
	W3DSailModelDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x188 float zero.
	float m_zero188;
	// +0x18C 0.25f cap.
	float m_cap18C;
	// +0x190 0.05f cap (ends at the rowed 0x194 instance size).
	float m_cap190;
};

// ??0W3DSailModelDrawModuleData@@QAE@XZ @0x000D0737
W3DSailModelDrawModuleData::W3DSailModelDrawModuleData()
	: W3DModelDrawModuleData()
{
	float fzero = 0.0f;
	float cap25 = 0.25f;
	float cap05 = 0.05f;
	m_zero188 = fzero;
	m_cap18C = cap25;
	*(unsigned int *)this = 0x00BC6870;
	m_cap190 = cap05;
}

// ?buildFieldParse@W3DSailModelDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x000D0774
void W3DSailModelDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	W3DModelDrawModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BCDC20), 0);
}

// ??0ClearanceTestingSlowDeathBehaviorModuleData@@QAE@XZ
// partial score=0.98 date=2026-09-21
// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
//
// ??0ClearanceTestingSlowDeathBehaviorModuleData@@QAE@XZ retail 0x00483E25
// 160 bytes. 157/160 banked 0.98: all calls and stores exact with sizes
// equal. Sole wall is xorps-vs-C-load order (retail xorps then movss xmm1
// from 0xC49E90; this body loads then xors). Needs pinned base 0x45E386 and
// pinned GeometryInfo 5-arg 0x50B74 plus rowed factory 0x24C545 and rowed
// proc 0x483C1A and poolkey 0x483CF4. Refuted: source order x6 and const and
// take position and split zero-init and b-local placement. The b-local
// (late float b from 0xBCE3B8 reused for +0x1FC and +0x204) and the
// sourced-before pointer take (lea-run zeros at +0x1EC) and EBO base with
// declared-only dtor (single EH state) and explicit m_vtable first (lands
// between base call and member call) are all load-bearing. Retry only with
// a new xorps-scheduling lever.

class SlowDeathBehaviorModuleData
{
public:
	SlowDeathBehaviorModuleData();
	~SlowDeathBehaviorModuleData();
};

enum GeometryType
{
	GEOMETRY_TYPE_NONE = 0
};

class GeometryInfo
{
public:
	GeometryInfo(GeometryType type, bool flag, float a, float b, float c);
	unsigned char m_data[0x5C];
};

extern const float g_bfmeClearA;
extern const float g_bfmeClearB;
extern const float g_bfmeClearC;

class ClearanceTestingSlowDeathBehaviorModuleData : public SlowDeathBehaviorModuleData
{
public:
	ClearanceTestingSlowDeathBehaviorModuleData();

private:
	const void *m_vtable;
	unsigned char m_pad[0x190 - 4];
	GeometryInfo m_geometry;
	float m_offset[3];
	float m_1F8;
	float m_1FC;
	float m_200;
	float m_204;
};

// ??0ClearanceTestingSlowDeathBehaviorModuleData@@QAE@XZ @0x483E25
ClearanceTestingSlowDeathBehaviorModuleData::ClearanceTestingSlowDeathBehaviorModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C49E98))
	, m_geometry(GEOMETRY_TYPE_NONE, false, 1.0f, 1.0f, 1.0f)
{
	float *offset = m_offset;
	float c = g_bfmeClearC;
	offset[0] = 0.0f;
	offset[1] = 0.0f;
	offset[2] = 0.0f;
	m_1F8 = g_bfmeClearA;
	float b = g_bfmeClearB;
	m_1FC = b;
	m_200 = c;
	m_204 = b;
}

// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
//
// ??0ClearanceTestingSlowDeathBehaviorModuleData@@QAE@XZ, retail 0x00483E25,
// 160 bytes. SlowDeath ModuleData ctor over the ClearanceTesting table.
// Identity is the rowed poolkey 0x483CF4 in cluster plus rowed proc 0x483C1A
// plus factory 0x24C545 (news 0x208, sole caller). Shape: EBO SlowDeath base
// (declared-only ctor resolving to the pin at 0x45E386, declared-only dtor
// for a single EH state) plus explicit void*m_vtable first (lands between
// the base call and the member call) plus 5-arg GeometryInfo member through
// the pin at 0x50B74 plus sourced-before pointer take for the lea-run zeros
// at +0x1EC plus late b-local reused for +0x1FC and +0x204.

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
	float c = -20.0f;
	offset[0] = 0.0f;
	offset[1] = 0.0f;
	offset[2] = 0.0f;
	m_1F8 = g_bfmeClearA;
	float b = g_bfmeClearB;
	m_1FC = b;
	m_200 = c;
	m_204 = b;
}

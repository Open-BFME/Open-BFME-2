// cl: /GX /MD /DNDEBUG
// ?rva0047FFFE@ShareExperienceBehavior@@QAEMPAVCoord3D@@PAUPos0047FFFE@@@Z @ 0x0047FFFE 149B
// Unlock: ShareExperience distance falloff between ModuleData radii. Evidence:
// contiguous gap after ??1ShareExperienceBehaviorModuleData 0x0047FFCE and before
// caller 0x00480093; ecx+4 is ModuleData with floats +8/+0xC matching ctor TU
// 0x0047FE90 (m_r8/m_rC); second param carries pos at +0x38/+0x3C/+0x40;
// callees all rowed (Coord3D::GetLength 0x00005A26); float refs g_Va00BBB8D8 / BfmeZeroRange.
extern float g_Va00BBB8D8;
// BfmeZeroRange is float 0.0 at 0x00BBAEAC (data_ledger literal); use 0.0f literal so the TU links.

class Coord3D
{
public:
	float GetLength() const;
	float x;
	float y;
	float z;
};

struct Pos0047FFFE
{
	unsigned char pad[0x38];
	float x;
	float y;
	float z;
};

class ShareExperienceBehaviorModuleData
{
public:
	unsigned char m_pad[8];
	float m_08;
	float m_0C;
};

class ShareExperienceBehavior
{
public:
	void *m_vtbl;
	ShareExperienceBehaviorModuleData *m_moduleData;
	float rva0047FFFE(Coord3D *a, Pos0047FFFE *b);
};

float ShareExperienceBehavior::rva0047FFFE(Coord3D *a, Pos0047FFFE *b)
{
	ShareExperienceBehaviorModuleData *md = m_moduleData;
	if (md->m_0C == g_Va00BBB8D8)
	{
		Coord3D diff;
		diff.x = b->x;
		diff.y = b->y;
		diff.z = b->z;
		diff.x -= a->x;
		diff.y -= a->y;
		diff.z -= a->z;
		float len = diff.GetLength();
		float f = g_Va00BBB8D8 - len / md->m_08;
		if (f >= 0.0f)
			return f;
		return 0.0f;
	}
	return g_Va00BBB8D8;
}

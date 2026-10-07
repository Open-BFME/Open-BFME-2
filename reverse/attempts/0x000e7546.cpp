// ?rva000E7546@Rva000E7546@@QAE_NHPAURva000E7546Pos@@PAMPAURva000E7546Pair@@2@Z
// partial score=0.91 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva000E7546@Rva000E7546@@QAE_NHPAURva000E7546Pos@@PAMPAURva000E7546Pair@@2@Z
// @0x000E7546 175B. Best compile is 174B. /G7 keeps imul by 0xA0 and the
// byte-pointer base keeps the 0x1998 displacements. The miss is register
// coalescing: index lives in edx so the base is `add edx, ecx` (2B) instead
// of retail `lea edx, [eax+ecx]` (3B). /O2 strength-reduces the imul. /Og- spills.

struct Rva000E7546Pos
{
	float m_x;
	int m_y;
	int m_z;
};

struct Rva000E7546Pair
{
	int m_a;
	int m_b;
};

struct Rva000E7546Rec
{
	float m_x;
	int m_y;
	int m_z;
	float m_scale;
	char m_pad10[0x40 - 0x10];
	int m_key;
	unsigned char m_flag;
	char m_tail[0xA0 - 0x45];
};

struct Rva000E7546Side
{
	int m_gate;
	char m_pad04[0x2C - 0x04];
	int m_a;
	int m_b;
	char m_pad34[0x3C - 0x34];
	int m_c;
	int m_d;
	unsigned char m_flag;
	char m_tail[0x5C - 0x45];
};

struct Rva000E7546Stride
{
	char raw[0xA0];
};

class Rva000E7546
{
public:
	bool rva000E7546(int index, Rva000E7546Pos *pos, float *scale,
		Rva000E7546Pair *first, Rva000E7546Pair *second);

	char m_pad[0x1958];
	Rva000E7546Rec m_rec[2000];
	int m_count;
	char m_gap[0x14];
	Rva000E7546Side m_side[1];
};

bool Rva000E7546::rva000E7546(int index, Rva000E7546Pos *pos, float *scale,
	Rva000E7546Pair *first, Rva000E7546Pair *second)
{
	if (index >= m_count)
		return false;
	Rva000E7546Stride *row = ((Rva000E7546Stride *)this) + index;
	int key = *(int *)((unsigned char *)row + 0x1998);
	if (key < 0 || ((unsigned char *)row)[0x199C] == 0)
		return false;
	unsigned char *side = (unsigned char *)this + key * 0x5C;
	if (*(int *)(side + 0x4FB70) == 0 || side[0x4FBB4] == 0)
		return false;
	int *xyz = (int *)((unsigned char *)row + 0x1958);
	pos->m_x = *(float *)xyz;
	pos->m_y = xyz[1];
	pos->m_z = xyz[2];
	*scale = *(float *)((unsigned char *)row + 0x1964) * 10.0f;
	first->m_a = *(int *)(side + 0x4FB9C);
	first->m_b = *(int *)(side + 0x4FBA0);
	second->m_a = *(int *)(side + 0x4FBAC);
	second->m_b = *(int *)(side + 0x4FBB0);
	return true;
}

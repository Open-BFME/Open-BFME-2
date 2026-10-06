// cl: /MD
// Built from the banked attempt reverse/attempts/0x005876d5.cpp; fix: the floats
// read through g_00BC5CD4, g_00BC6258, g_00BE2B94, g_00C6FF34, g_Va00BC2428 are compiler literals holding the retail
// values, not extern globals, which is what gives retail's operand order.
// ??0Rva005876D5@@QAE@XZ @0x005876D5 125B: constructor. Floats +0x04..+0x14
// from float globals, pointer +0x00 from g_00C6FF28, member +0x18 built by
// the rowed ??0Rva0042526Member@@QAE@XZ in declaration order, ints +0x64/+0x68
// as double of g_Va00DBA4E4 and +0x6C as triple, then OR 0x40 into the
// member flags at +0x40. Member view keeps the rowed 0x4C size with the
// ORed dword at +0x28. The +0x00 store is modeled as a plain data pointer;
// if the class proves polymorphic it wants a vtable instead.
// Evidence: caller 0x00469204; member TU Rva0042526MemberCtor.cpp;
// g+g spelling from TransportAIUpdateModuleDataCtor.cpp; g_Va00DBA4E4
// declared extern int like the cold getters. Neighbours 0x005875DC
// 0x0058814C.

extern int g_00C6FF28;
// g_00C6FF28: matched references place it at VA 0xc6ff28 (retail .rdata value 9992018).
int g_00C6FF28 = 9992018;
extern int g_Va00DBA4E4;

class Rva0042526Member
{
public:
	Rva0042526Member();

public:
	unsigned char m_pad18[0x28];
	int m_flags28;
	unsigned char m_pad2C[0x4C - 0x2C];
};

class Rva005876D5
{
public:
	Rva005876D5();

private:
	int *m_p00;
	float m_f04;
	float m_f08;
	float m_f0C;
	float m_f10;
	float m_f14;
	Rva0042526Member m_m18;
	int m_i64;
	int m_i68;
	int m_i6C;
};

Rva005876D5::Rva005876D5()
	: m_f04(10.0f)
	, m_f08(-0.17000000178813934f)
	, m_f0C(60.0f)
	, m_f10(90.0f)
	, m_p00(&g_00C6FF28)
	, m_f14(140.0f)
	, m_i64(g_Va00DBA4E4 + g_Va00DBA4E4)
	, m_i68(g_Va00DBA4E4 + g_Va00DBA4E4)
	, m_i6C(g_Va00DBA4E4 * 3)
{
	Rva0042526Member &m = m_m18;
	m.m_flags28 |= 0x40;
}

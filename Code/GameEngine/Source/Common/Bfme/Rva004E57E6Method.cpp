// cl: /DNDEBUG /MD
// ?rva004E57E6@Rva004E57E6@@QAEXPAURva004E57E6Pair@@M@Z @0x004E57E6 (29B)
// __thiscall setter: copies pair->m_0 to +0x28, pair->m_4 to +0x2c, float to +0x30.
// Evidence: unlock lane, callee-free, caller 0x0029B187 passes pair ptr plus float
// with this = [ecx+0x7f4]; unblocks 0x0029B187. movss idiom -> /arch:SSE.
struct Rva004E57E6Pair {
	int m_0;
	int m_4;
};

class Rva004E57E6 {
	char m_pad[0x28];
	int m_28;
	int m_2c;
	float m_30;
public:
	void rva004E57E6(Rva004E57E6Pair *p, float f);
	void rva004E5803();
};

extern int g_00DD00A8;
// g_00DD00A8: matched references place it at VA 0xdd00a8 (retail .data initial value 1017118720).
int g_00DD00A8 = 1017118720;
extern int g_00DD00AC;
// g_00DD00AC: matched references place it at VA 0xdd00ac (retail .data initial value 1042721451).
int g_00DD00AC = 1042721451;
extern float g_00C623C8;
// g_00C623C8: matched references place it at VA 0xc623c8 (retail .rdata value 0.9609375f).
float g_00C623C8 = 0.9609375f;

void Rva004E57E6::rva004E57E6(Rva004E57E6Pair *p, float f)
{
	m_28 = p->m_0;
	m_2c = p->m_4;
	m_30 = f;
}
// ?rva004E5803@Rva004E57E6@@QAEXXZ @0x004E5803 (30B)
// __thiscall loads defaults from globals into +0x28/+0x2c/+0x30, same layout as 0x004E57E6.
// Evidence: unlock lane, adjacent to 0x004E57E6, same offsets and /arch:SSE movss idiom; unblocks 0x0029B1A1.
void Rva004E57E6::rva004E5803()
{
	int t0 = g_00DD00A8;
	float tf = g_00C623C8;
	m_28 = t0;
	m_2c = g_00DD00AC;
	m_30 = tf;
}

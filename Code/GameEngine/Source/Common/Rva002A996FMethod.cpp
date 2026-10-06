// cl: /MD
//
// ??0Rva002A996F@@QAE@XZ retail 0x002A996F 37B
// Zeroes +0 +4 +8 as float 0 plus +0xC as int 0 then +0x10 from FLT_MAX
// global 0x00BBB8E0 via rowed g_Va00BBB8E0. Caller 0x002AB22A unblocks it.
// Evidence: retail xorps plus movss zeros plus and [eax+0xC] 0 plus movss load.
extern float g_Va00BBB8E0;
// g_Va00BBB8E0: matched references place it at VA 0xbbb8e0 (retail .rdata value 3.4028235e+38f).
float g_Va00BBB8E0 = 3.4028235e+38f;

class Rva002A996F
{
public:
	Rva002A996F();
private:
	float m_00;
	float m_04;
	float m_08;
	int m_0C;
	float m_10;
};

Rva002A996F::Rva002A996F()
{
	m_0C = 0;
	m_00 = 0.0f;
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_10 = g_Va00BBB8E0;
}

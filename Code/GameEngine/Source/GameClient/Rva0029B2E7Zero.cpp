// cl: /MD
// ?rva0029B2E7@Rva0029B2E7@@QAEXXZ @0x0029B2E7 44B.
// Zeroes byte at +0 and floats at +4 +8 +C +10 +14 +18 +1C.
// Caller at 0x0029B502.
class Rva0029B2E7
{
public:
	Rva0029B2E7 *rva0029B2E7();
	unsigned char m_0; // +0x00
	char m_pad01[0x3];
	float m_4; // +0x04
	float m_8; // +0x08
	float m_C; // +0x0C
	float m_10; // +0x10
	float m_14; // +0x14
	float m_18; // +0x18
	float m_1C; // +0x1C
};
Rva0029B2E7 *Rva0029B2E7::rva0029B2E7()
{
	Rva0029B2E7 *p = this;
	p->m_0 = 0;
	p->m_4 = 0.0f;
	p->m_8 = 0.0f;
	p->m_C = 0.0f;
	p->m_1C = 0.0f;
	p->m_18 = 0.0f;
	p->m_14 = 0.0f;
	p->m_10 = 0.0f;
	return p;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0BfmeElemVVD@@QAE@XZ=?rva0029B2E7@Rva0029B2E7@@QAEPAV1@XZ")

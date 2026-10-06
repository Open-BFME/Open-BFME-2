// cl: /MD
// ?rva0029B2E7@Rva0029B2E7@@QAEXXZ @0x0029B2E7 44B.
// Zeroes byte at +0 and floats at +4 +8 +C +10 +14 +18 +1C.
// Caller at 0x0029B502.
class Rva0029B2E7 {
public:
	Rva0029B2E7 *rva0029B2E7();
private:
	unsigned char m_0;
	char m_pad1[3];
	float m_4;
	float m_8;
	float m_C;
	float m_10;
	float m_14;
	float m_18;
	float m_1C;
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

// ?rva0053841C@Rva0053841C@@QAEXPBURva0053841CArg@@@Z
// partial score=0.92 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva0053841C@Rva0053841C@@QAEXPBURva0053841CArg@@@Z, retail 0x0053841C, 239 bytes.
// Float4 range transform: for each 0x10 record, two dot-product pairs with
// the 8-float argument, then flag +0x20 set. Caller 0x0030BC9E; no calls.
struct Rva0053841CArg
{
	float m_00;
	float m_04;
	float m_08;
	float m_0C;
	float m_10;
	float m_14;
	float m_18;
	float m_1C;
};

struct Rva0053841CRec
{
	float x;
	float y;
	float z;
	float w;
};

class Rva0053841C
{
public:
	void rva0053841C(const Rva0053841CArg *arg);
private:
	Rva0053841CRec *m_begin;
	Rva0053841CRec *m_end;
	char m_pad08[0x18];
	bool m_20;
};

void Rva0053841C::rva0053841C(const Rva0053841CArg *arg)
{
	Rva0053841CRec *p = m_begin;
	Rva0053841CRec *end = m_end;
	float zero = 0.0f;
	for (; p != end; ++p) {
		float ex = p->x;
		float ey = p->y;
		float ex2 = ex;
		float nx = arg->m_00 * ex + arg->m_04 * ey + arg->m_08 * zero + arg->m_0C;
		float ny = arg->m_10 * ex2 + arg->m_14 * ey + arg->m_18 * zero + arg->m_1C;
		p->y = ny;
		p->x = nx;
		float ez = p->z;
		float ew = p->w;
		float ez2 = ez;
		float nz = arg->m_00 * ez + arg->m_04 * ew + arg->m_08 * zero + arg->m_0C;
		float nw = arg->m_10 * ez2 + arg->m_14 * ew + arg->m_18 * zero + arg->m_1C;
		p->z = nz;
		p->w = nw;
	}
	m_20 = true;
}

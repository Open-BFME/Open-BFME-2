// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0040C9A4@Rva0040C985@@QAEMXZ, retail 0x0040C9A4, 80 bytes.
//
// Same-class neighbour of Rva0040C985Init.cpp (class layout and TheGameLogic
// extern copied from it).  Rva0040C985 tracks a frame window [m_38, m_34] and
// this body returns the elapsed fraction, clamped to 1.0:
//   denom = m_34 - m_38, forced to 1 when non-positive;
//   num   = TheGameLogic->m_40 - m_38 as unsigned (the fild/fadd 2^32 fold);
//   f     = (float)num / (float)denom, and the result is 1.0 when f > 1.0.
//
// Measured byte evidence: the comparison literal must be the DOUBLE `1.0`
// (this is what emits `fld st(0); fld1; fxch st(1); fcomip st,st(1)` rather
// than `fcom`+`fnstsw`), the clamp must be the early return `return 1.0f;`
// (an assignment `f = 1.0f;` instead makes /arch:SSE materialise the
// constant through xmm0 and adds 10 bytes), and /arch:SSE is required for
// fcomip.  Those three choices reproduce all 80 bytes exactly.
class Rva00DFE78C { public: char m_pad[0x40]; int m_40; };
class GameLogic;
extern GameLogic *TheGameLogic;
class Rva0040C985 { public: void rva0040C985(int x); float rva0040C9A4();
private: char m_pad[0x24]; int m_24; int m_28; int m_2C; int m_30; int m_34; int m_38; };
float Rva0040C985::rva0040C9A4()
{
	int denom = m_34 - m_38;
	if (denom <= 0)
		denom = 1;
	unsigned num = (unsigned)(((Rva00DFE78C *)TheGameLogic)->m_40 - m_38);
	float fd = (float)denom;
	float fn = (float)num;
	float f = fn / fd;
	if (1.0 < f)
		return 1.0f;
	return f;
}

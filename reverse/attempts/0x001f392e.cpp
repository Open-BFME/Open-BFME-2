// ?rva001F392E@Rva001F392E@@QAEXM@Z
// partial score=0.7539 date=2026-10-06
// ?rva001F392E@Rva001F392E@@QAEXM@Z
// partial score=0.88 date=2026-09-29
// ?rva001F392E@Rva001F392E@@QAEXM@Z
// partial score=0.88 date=2026-09-29
// cl: /O1 /MD /arch:SSE
//
// ?rva001F392E@Rva001F392E@@QAEXM@Z, retail 0x001F392E, 247 bytes.
// Rotation-shaped body on the same +0xBC..+0x1A0 region as Rva001F38C1Slot:
// sine via msvcr71 sin then cosine via cos (both double CRT calls through
// the rowed ji_ thunks, narrowed to float locals), then three XY pairs
// (+0xC0/+0xC4, +0xD0/+0xD4, +0xE0/+0xE4) each rotated as
// x' = x*c + y*s, y' = y*c - x*s in SSE, then the +0x1A0 flag cleared.
// Caller is the unclaimed 0x001E19E8 body, so the owner is unknown and the
// name is an honest address. Precedent is BfmeCalcBWF.cpp (plain
// extern "C" double sin/cos declarations give E8-to-thunk calls); unlike
// that body retail here keeps the two separate CRT calls, so no __asm.

// (CRT prototype from the standard header)
// (CRT prototype from the standard header)

#include <math.h>
class Rva001F392E
{
public:
	void rva001F392E(float angle);
private:
	char m_pad00[0xC0];
	float m_C0;
	float m_C4;
	char m_padC8[0xD0 - 0xC8];
	float m_D0;
	float m_D4;
	char m_padD8[0xE0 - 0xD8];
	float m_E0;
	float m_E4;
	char m_padE8[0x1A0 - 0xE8];
	unsigned char m_flag;
};

// ?rva001F392E@Rva001F392E@@QAEXM@Z present-unmatched
void Rva001F392E::rva001F392E(float angle)
{
	float s = (float)sin(angle);
	float c = (float)cos(angle);
	float x = m_C0;
	float y = m_C4;
	m_C0 = x * c + y * s;
	m_C4 = y * c - x * s;
	x = m_D0;
	y = m_D4;
	m_D0 = x * c + y * s;
	m_D4 = y * c - x * s;
	x = m_E0;
	y = m_E4;
	m_E0 = x * c + y * s;
	m_E4 = y * c - x * s;
	m_flag = 0;
}

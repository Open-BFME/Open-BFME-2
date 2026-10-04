// cl: /O1 /arch:SSE /DNDEBUG /MD
// ?rva005D4867@Rva005D4867@@QAEXPBD@Z @0x005D4867 87B
// String-driven setter: parse the text with the CRT atof (import slot
// 0x00BBA550), clamp it to [0, 1 - the float at +0x18], store it at +0x20
// and hand it to slot 1 of the object at +0. The caller at 0x005D4D55
// binds this function's address into a member-callback record rather than
// calling it. Retail compares with fcompi, which MSVC 7.1 emits only under
// /arch:SSE, and computes the upper bound only on the non-negative path,
// hence the explicit if/else rather than a clamp helper. Names are
// address-derived.
#include <stdlib.h>
class Rva005D4867Target
{
public:
	virtual void slot00();
	virtual void slot01(float value);
};
class Rva005D4867
{
public:
	void rva005D4867(const char *text);
	Rva005D4867Target *m_target;	// +0x00
	char m_pad04[0x18 - 4];
	float m_18;
	char m_pad1C[4];
	float m_20;
};
static inline float bfmeClamp(float value, float lo, float hi)
{
	if (value < lo)
		return lo;
	if (value > hi)
		return hi;
	return value;
}
void Rva005D4867::rva005D4867(const char *text)
{
	float value = (float)atof(text);
	if (value < 0.0f)
		value = 0.0f;
	else if (value > 1.0f - m_18)
		value = 1.0f - m_18;
	m_20 = value;
	m_target->slot01(value);
}

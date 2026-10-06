// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva00330D3E@RadiusDecalTemplate@@QAEMI@Z @0x00330D3E 83B
// Unlock lane: lerp between +0x20/+0x24 over count +0x28 with clamp to max.
// (max-min)/count step, t=(index-1)*step+min, if t>max return max.
// Callers 0x00330E3E 0x003312B3.
#include "ascii_string.h"
class RadiusDecalTemplate
{
public:
	float rva00330D3E(unsigned int index);
private:
	AsciiString m_name; // +0x00
	AsciiString m_secondName; // +0x04
	int m_shadowType; // +0x08
	float m_minOpacity; // +0x0C
	float m_maxOpacity; // +0x10
	float m_opacityThrobTime; // +0x14
	unsigned int m_color; // +0x18
	bool m_onlyVisibleToOwningPlayer; // +0x1C
	float m_unmodelled20; // +0x20
	float m_unmodelled24; // +0x24
	unsigned int m_unmodelled28; // +0x28
	float m_unmodelled2C; // +0x2C
	float m_unmodelled30; // +0x30
};

float RadiusDecalTemplate::rva00330D3E(unsigned int index)
{
	float step = (m_unmodelled24 - m_unmodelled20) / (float)m_unmodelled28;
	unsigned int i = index - 1;
	float t = (float)i * step + m_unmodelled20;
	if (t > m_unmodelled24)
		t = m_unmodelled24;
	return t;
}

// Clean BFME1 RadiusDecalOpacityRamp.cpp at revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76; O1/G7/MD and O1/G7/SSE/MD.
// Target 0x00330E2D: two pointer guards, frame -> 0x00330D3E, float stores
// at result+0x58/+0x5C and RET4. The direct adjusting tailcall at 0x000B318D
// supplies this+0x1D0; neighbouring setters use the same subobject.
// This proves the accessed 8B and 96B prefixes, not original owner/type names
// or complete layouts. No Ghidra entry is recorded for this small wrapper.
class Rva00330E2DOutput
{
public:
	char m_pad00[0x58];
	float m_first;
	float m_second;
};

class Rva00330E2DFrameOpacity
{
public:
	RadiusDecalTemplate *m_ramp;
	Rva00330E2DOutput *m_result;
	void rva00330E2D(unsigned int frame);
};

void Rva00330E2DFrameOpacity::rva00330E2D(unsigned int frame)
{
	Rva00330E2DOutput *result = m_result;
	if (result != 0)
	{
		RadiusDecalTemplate *ramp = m_ramp;
		if (ramp != 0)
			result->m_second = result->m_first = ramp->rva00330D3E(frame);
	}
}

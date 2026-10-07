// ?bfmeDoBLD@BfmeSinkBLD@@QAEXPAXH@Z
// partial score=0.95 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /O1 /arch:SSE /G7
// ?bfmeDoBLD@BfmeSinkBLD@@QAEXPAXH@Z @0x002D4341 95B
// Target evidence: function name is pinned; it calls hasOverrideWindow three times,
// updates the object at this+0x10 offsets +0x14C/+0x150, then uses its +0x78 object.
#include "ascii_string.h"

class RadarWindowOverrideSource
{
public:
	bool hasOverrideWindow() const throw();
	void rva002D4240(bool enabled) throw();
private:
	char m_pad00[0x10];
};

class Rva005C96A9
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8)
#undef V
	virtual void vf9();
	void rva00524D01(const AsciiString &value, int flags);
};

struct BfmeSinkBLDState
{
	char m_pad00[0x78];
	Rva005C96A9 *m_object78;
	char m_pad7C[0x14C - 0x7C];
	int m_value14C;
	bool m_flag150;
};

class BfmeSinkBLD : public RadarWindowOverrideSource
{
public:
	void bfmeDoBLD(void *text, int value);
private:
	BfmeSinkBLDState *m_state;
};

void BfmeSinkBLD::bfmeDoBLD(void *text, int value)
{
	if (!hasOverrideWindow())
		return;

	m_state->m_flag150 = !hasOverrideWindow();
	m_state->m_value14C = value;
	if (!hasOverrideWindow())
		rva002D4240(false);

	m_state->m_object78->vf9();
	m_state->m_object78->rva00524D01(*(const AsciiString *)text, 0x40);
}

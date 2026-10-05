// ?rva00067EA3@Rva00067EA3@@QAEXMMMMH@Z
// partial score=0.95 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /Oi- /arch:SSE
// ?rva00067EA3@Rva00067EA3@@QAEXMMMMH@Z, retail 0x00067EA3, 298 bytes.
// Unlock lane: searches 500-entry array at +0xE0 (28B entries) for an entry
// within estimate (arg4*0.25f float pool at 0x007BB8D4) on x/y/w plus same
// int kind; if found clears its active byte and returns, else appends (evict
// oldest via (head+1)%500 when full). fabs via import 0x00629210.
// Evidence: callers at 0x0004C7E8/0x000924BB/0x00098A35, rowed fabs callee,
// count/head/flag at +0x3790/+0x3794/+0x3798.

extern "C" double __cdecl fabs(double v);

struct Entry00067EA3
{
	float unk00;
	float x;
	float y;
	float z;
	float w;
	int kind;
	unsigned char active;
	char pad[3];
};

class Rva00067EA3
{
public:
	void rva00067EA3(float a, float b, float c, float d, int e);
private:
	unsigned char m_pad[0xE0];
	Entry00067EA3 m_entries[500];
	int m_count;
	int m_flag3794;
	int m_head;
};

// ?rva00067EA3@Rva00067EA3@@QAEXMMMMH@Z present-unmatched
void Rva00067EA3::rva00067EA3(float a, float b, float c, float d, int e)
{
	float estimate = d * 0.25f;
	for (int i = 0; i < m_count; ++i)
	{
		Entry00067EA3 *en = &m_entries[i];
		if (!(fabs(a - en->x) < estimate))
			continue;
		if (!(fabs(b - en->y) < estimate))
			continue;
		if (!(fabs(d - en->w) < estimate))
			continue;
		if (en->kind != e)
			continue;
		m_entries[i].active = 0;
		return;
	}
	int slot = m_count;
	if (slot >= 500)
	{
		slot = m_head;
		int next = (slot + 1) % 500;
		--m_count;
		m_head = next;
	}
	m_entries[slot].x = a;
	m_entries[slot].y = b;
	m_entries[slot].z = c;
	m_entries[slot].w = d;
	m_entries[slot].kind = e;
	m_entries[slot].active = 0;
	++m_count;
	m_flag3794 = 0;
}

// ?rva00568939@Rva00568920@@QAEXH@Z
// partial score=0.95 date=2026-10-05
// cl: /O1
// ?rva00568920@Rva00568920@@QBE_NXZ @0x00568920 25B: all-nonzero test over
// four dwords at +0x2C. Returns false on first zero else true. Same +0x2C
// 4-entry layout as indexed getter 0x005686C1. Caller at 0x00568939 tests al.
// Prev stlport advance and next rb-tree copy share page.
//
// ?rva00568939@Rva00568920@@QAEXH@Z @0x00568939 88B: keyed notify. The
// check above first; then scan the +0x14/+0x18 range (0x14 stride) for key
// at +0xC; on a found element with a clear +0x10 flag, run every non-null
// +0x2C slot through the pinned 0x005C836F(float at +8, key) and set the
// flag. Lives in this TU because the check call keeps this in ecx across
// the call, which MSVC only emits for a same-TU (visible) callee.
class Rva005C836F
{
public:
	void rva005C836F(float f, int key);
};

struct Rva00568939Elem
{
	char m_00[8];
	float m_08;
	int m_0c;
	bool m_10;
	char m_pad11[3];
};

class Rva00568920
{
public:
	bool rva00568920() const;
	void rva00568939(int key);
private:
	char m_pad[0x14];
	Rva00568939Elem *m_begin14;
	Rva00568939Elem *m_end18;
	char m_pad1C[0x10];
	Rva005C836F *m_slots2C[4];
};
bool Rva00568920::rva00568920() const
{
	for (int i = 0; i < 4; ++i)
		if (m_slots2C[i] == 0)
			return false;
	return true;
}

void Rva00568920::rva00568939(int key)
{
	if (!rva00568920())
		return;
	for (Rva00568939Elem *e = m_begin14; e != m_end18; ++e) {
		if (e->m_0c != key)
			continue;
		if (e->m_10)
			return;
		Rva005C836F **slot = m_slots2C;
		for (int left = 4; left != 0; --left, ++slot) {
			if (*slot != 0) {
				float f = (float)e->m_08;
				(*slot)->rva005C836F(f, key);
			}
		}
		e->m_10 = true;
		return;
	}
}

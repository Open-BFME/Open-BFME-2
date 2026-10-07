// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00568920@Rva00568920@@QBE_NXZ @0x00568920 25B: all-nonzero test over
// four dwords at +0x2C. Returns false on first zero else true. Same +0x2C
// 4-entry layout as indexed getter 0x005686C1. Caller at 0x00568939 tests al.
// Prev stlport advance and next rb-tree copy share page.
//
// ?rva00568939@Rva00568920@@QAEXH@Z @0x00568939 88B: keyed notify. The
// check above first (same TU: the call keeps this in ecx across it, which
// MSVC only emits for a visible callee); then scan +0x14/+0x18 elements
// stride 0x14 for key at +0xC; on a found element with clear +0x10, run every
// non-null +0x2C slot through the verified HostClass005C815B::method_005C836F(int,float) at 0x005C836F and set
// the flag. The union keeps the rowed check's int view beside the slots.
class HostClass005C815B
{
public:
	void method_005C836F(int key, float value);
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
	union
	{
		int m_vals[4];
		HostClass005C815B *m_slots[4];
	};
};
bool Rva00568920::rva00568920() const
{
	for (int i = 0; i < 4; ++i)
		if (m_vals[i] == 0)
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
		HostClass005C815B **slot = m_slots;
		for (int left = 4; left != 0; --left, ++slot) {
			if (*slot != 0) {
				float f = e->m_08;
				(*slot)->method_005C836F(key, f);
			}
		}
		e->m_10 = true;
		return;
	}
}

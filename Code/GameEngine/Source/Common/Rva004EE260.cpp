// cl: /MD
// ?rva004EE260@Rva004EE260@@QAEXHPAVRva003F498A@@PAX@Z, retail 0x004EE260, 219 bytes.
// Chain via 0x003F486C: same time-less head as 0x004EE0C6 (rva003F486C then
// rva003F4798 into +0xD4/+0xD8) plus a pair-vector scan counting into
// +0x88/+0x8C/+0x9C/+0xA0/+0xA4. Evidence: rowed 0x003F486C 0x003F4798;
// prev Rva004EE037Div /O1 /MD; ret 0xC three args first unused.
class Rva003F498A
{
public:
	bool rva003F486C(int id);
	int rva003F4798(int outerIdx, int id);
};

struct Rva004EE260Base
{
	char m_pad[0x30];
	int m_id;
};

struct Rva004EE260B
{
	char m_pad[0xB4];
	int m_b4;
};

struct Rva004EE260C
{
	char m_pad[0x113];
	unsigned char m_113;
};

struct Rva004EE260Obj
{
	char m_pad0[8];
	Rva004EE260B *m_b;
	char m_pad1[0x2C - 0xC];
	Rva004EE260C *m_c;
	int m_idx;
};

struct Rva004EE260Pair
{
	Rva004EE260Obj *m_first;
	Rva004EE260Obj *m_second;
};

struct Rva004EE260Q
{
	Rva004EE260Base *m_base;
	char m_pad[0x3C - 4];
	Rva004EE260Pair *m_begin;
	Rva004EE260Pair *m_end;
};

class Rva004EE260
{
public:
	void rva004EE260(int unused, Rva003F498A *p, void *qraw);
private:
	char m_pad00[0x88];
	int m_88;
	int m_8C;
	char m_pad90[0x9C - 0x90];
	int m_9C;
	int m_A0;
	int m_A4;
	char m_padA8[0xD4 - 0xA8];
	int m_D4;
	int m_D8;
	char m_padDC[0xE8 - 0xDC];
	int m_E8;
};

void Rva004EE260::rva004EE260(int unused, Rva003F498A *p, void *qraw)
{
	(void)unused;
	if (p->rva003F486C(m_E8)) {
		int tmp38 = *(int *)((char *)p + 0x38);
		int v = p->rva003F4798(tmp38, m_E8);
		if (v == -1)
			++m_D8;
		else
			++m_D4;
	}
	Rva004EE260Q *q = (Rva004EE260Q *)qraw;
	Rva004EE260Pair *end = q->m_end;
	Rva004EE260Pair *begin = q->m_begin;
	if (begin == end)
		return;
	int id = m_E8;
	for (; begin != end; ++begin) {
		Rva004EE260Obj *second = begin->m_second;
		int idx2 = second->m_idx;
		if (q->m_base[idx2].m_id == id) {
			Rva004EE260B *b = second->m_b;
			if (b->m_b4 != 0)
				++m_88;
			else {
				Rva004EE260C *c = second->m_c;
				if (c && (c->m_113 & 4))
					++m_A0;
				else
					++m_9C;
			}
		}
		else {
			Rva004EE260Obj *first = begin->m_first;
			int idx1 = first->m_idx;
			if (q->m_base[idx1].m_id == id) {
				Rva004EE260B *b = second->m_b;
				if (b->m_b4 != 0)
					++m_8C;
				else
					++m_A4;
			}
		}
	}
}

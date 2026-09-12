// ?bfmeOneCGD@BfmeThingCGD@@QAEXXZ
// partial score=0.6 date=2026-09-11
// Standalone attempt body for ?bfmeOneCGD@BfmeThingCGD@@QAEXXZ @ 0x00758D10.
// Layout proven (all branch targets/structure byte-equal); register
// assignment is not: see the partial record in reverse/re_attempts.log.
struct BfmeCGDSub
{
	unsigned char _gap0[4];
	int m_val4; // +4
	unsigned char _gap1[8];
	int m_val10; // +0x10
};

struct BfmeCGDNode
{
	BfmeCGDSub *m_sub0; // +0
	BfmeCGDSub *m_sub4; // +4
	unsigned char _gap0[8]; // +8
	int m_val10; // +0x10
	unsigned char _gap1[0x2c - 0x14];
	BfmeCGDNode **m_prev; // +0x2c, points at the previous link (or the head)
	BfmeCGDNode *m_next; // +0x30
};

class BfmeThingCGD
{
public:
	void bfmeOneCGD();
	void *m_bfmeFirst; // +0
	unsigned char m_gap0[0xae10 - 4]; // +4
	BfmeCGDNode *m_buckets[0x493]; // +0xae10, ends at 0xc05c
	BfmeCGDNode *m_head; // +0xc05c, active list made of spliced nodes
	unsigned m_index; // +0xc060
	BfmeCGDNode *m_current; // +0xc064
	unsigned char m_gap1[0xc06d - 0xc068]; // +0xc068
	bool m_bfmeBusy; // +0xc06d
};

void BfmeThingCGD::bfmeOneCGD()
{
	m_index = 0;
	m_current = m_buckets[0];
	for (;;)
	{
		if (m_current == 0)
		{
			for (;;)
			{
				unsigned idx = m_index + 1;
				if (idx == 0x493)
					return;
				m_index = idx;
				m_current = m_buckets[idx];
				if (m_current != 0)
					break;
			}
		}
		BfmeCGDNode *cur = m_current;
		BfmeCGDNode *next = cur->m_next;
		m_current = next;
		if (cur == 0)
			return;
		if (cur->m_sub0->m_val10 == 0)
		{
			if (cur->m_sub4->m_val10 == 0)
				continue;
		}
		BfmeCGDSub *s0 = cur->m_sub0;
		if (s0->m_val4 != 0 && cur->m_sub4->m_val4 != 0)
		{
			cur->m_val10 = 0;
		}
		else
		{
			if (m_current == cur)
				m_current = m_current->m_next;
			BfmeCGDNode *nxt = cur->m_next;
			if (nxt != 0)
				nxt->m_prev = cur->m_prev;
			BfmeCGDNode **prv = cur->m_prev;
			*prv = cur->m_next;
			cur->m_prev = 0;
			cur->m_next = m_head;
			m_head = cur;
		}
	}
}

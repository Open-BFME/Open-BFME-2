// cl: /MD
// ?rva00531E74@Rva00531E74@@QAEXXZ @ 0x00531E74 (49B): __thiscall collect bucket chains 0..4000 onto list at +0x3E84 then clear buckets.
// Callers at 0x005320C4 0x00533C38. Owner unknown so honest address name.
void operator delete[](void *block);
struct Rva00531E74Node
{
	Rva00531E74Node *m_next;
	unsigned short m_unk04;
	unsigned short m_count;
	char *m_data;
};
class Rva00531E74
{
public:
	void rva00531E74();
	void rva005320C1();
	Rva00531E74Node *m_buckets[4002];
};
void Rva00531E74::rva00531E74()
{
	Rva00531E74Node **p = &m_buckets[4001];
	if (p == (Rva00531E74Node **)this)
		return;
	do
	{
		--p;
		Rva00531E74Node *head = *p;
		if (head != 0)
		{
			do
			{
				Rva00531E74Node *next = head->m_next;
				head->m_next = m_buckets[4001];
				m_buckets[4001] = head;
				head = next;
			} while (head != 0);
		}
		*p = 0;
	} while (p != (Rva00531E74Node **)this);
}
// ?rva005320C1@Rva00531E74@@QAEXXZ @ 0x005320C1 (67B): __thiscall drain list at +0x3E84 after collect via 0x00531E74 then delete nodes with array delete when count at +6 exceeds 1.
// Evidence: same +0x3E84 as m_buckets[4001] in this TU plus same-class callee 0x00531E74 plus caller at 0x00533BD1.
void Rva00531E74::rva005320C1()
{
	rva00531E74();
	if (m_buckets[4001] == 0)
		return;
	Rva00531E74Node *next;
	do
	{
		next = m_buckets[4001]->m_next;
		if (m_buckets[4001]->m_count > 1)
			delete[] m_buckets[4001]->m_data;
		delete m_buckets[4001];
		m_buckets[4001] = next;
	} while (next != 0);
}

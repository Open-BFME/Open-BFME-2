// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva00525611@Rva00525611@@QAEXXZ, retail 0x00525611 34B leaf via list clear.
// Clears +0xc down a sentinel list at m_10->+0x14 then clears +0x1da.
// Evidence: no callees; callers 0x00526FEE 0x0052703A; prev 0x005255E2 next 0x005258B2 same flags.
struct Rva00525611Node
{
	Rva00525611Node *m_next;
	unsigned char m_pad[8];
	unsigned char m_flag;
};

struct Rva00525611Mid
{
	unsigned char m_pad[0x14];
	Rva00525611Node *m_head;
};

class Rva00525611
{
public:
	unsigned char m_pad[0x10];
	Rva00525611Mid *m_10;
	unsigned char m_pad2[0x1da - 0x14];
	unsigned char m_1da;
	void rva00525611();
};

void Rva00525611::rva00525611()
{
	for (Rva00525611Node *cur = m_10->m_head->m_next; cur != m_10->m_head; cur = cur->m_next)
		cur->m_flag = 0;
	m_1da = 0;
}

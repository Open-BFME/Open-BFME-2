// cl: /MD
// ?rva004FF582@Rva004FF582@@QAEXPAURva004FF582Node@@@Z at 0x004FF582 (53B).
// Tree/list free: recurse on child +0xC, destroy Rva004FF2F4 at +0x10, _free node, iterate via next +8.
// Evidence: chain lane, callees rowed self plus ??1Rva004FF2F4 0x004FF2F4 plus _free 0x00030830, caller 0x004FF729.
class Rva004FF2F4 {
public:
	~Rva004FF2F4();
};
extern "C" void free(void *);

struct Rva004FF582Node {
	char m_00[8];
	Rva004FF582Node *m_next;
	Rva004FF582Node *m_child;
	Rva004FF2F4 m_10;
};

struct Rva004FF729Head {
	char m_00[4];
	Rva004FF582Node *m_04;
	Rva004FF729Head *m_08;
	Rva004FF729Head *m_0C;
};

class Rva004FF582 {
public:
	void rva004FF582(Rva004FF582Node *node);
	void rva004FF729();
private:
	Rva004FF729Head *m_head;
	int m_04;
};

void Rva004FF582::rva004FF582(Rva004FF582Node *node)
{
	if (!node)
		return;
	do {
		rva004FF582(node->m_child);
		Rva004FF582Node *next = node->m_next;
		node->m_10.~Rva004FF2F4();
		free(node);
		node = next;
	} while (node);
}

// ?rva004FF729@Rva004FF582@@QAEXXZ at 0x004FF729 (41B).
// List clear: if m_04!=0 free m_head->m_04 via rva004FF582 then reinit sentinel self-loop.
// Evidence: chain lane calls 0x004FF582 rowed, caller 0x004FFBEB.

void Rva004FF582::rva004FF729()
{
	if (m_04 == 0)
		return;
	rva004FF582(m_head->m_04);
	m_head->m_08 = m_head;
	m_head->m_04 = 0;
	m_head->m_0C = m_head;
	m_04 = 0;
}

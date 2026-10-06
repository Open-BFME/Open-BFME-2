// cl: /DNDEBUG /MD
//
// ?rva000FE001@Rva000FE001 (retail 0x000FE001, 100 bytes): intrusive list move
// that unlinks other (FeNode via +0xb0 next and +0xb4 prev) from its old list
// and prepends it to this container's head at +0x14 (tail at +0x10 when other
// was head). No calls; pure moves. Evidence: 4 callers pass node as stack arg
// with ecx=this (e.g. 0x000FE19B pushes eax after clearing [eax+0x3c]); callee
//-free body unblocks 0x000FE188/0x000FE1AC/0x000FE8FC/0x000FF448.
//
// ?rva000FE188@Rva000FE001 (retail 0x000FE188, 36 bytes): drains the list
// from +0x10, clearing each node's +0x3C flag and moving it with
// rva000FE001, then clears +0x10. Callers 0x000FF606, 0x000FFEF7 and a tail
// jump at 0x00082B81. Retail keeps this in ecx across the rva000FE001 call,
// which cl only does when that callee was compiled earlier in the same TU.

struct FeNode
{
	unsigned char m_pad0[0x3c];
	unsigned char m_flag3c;
	unsigned char m_pad1[0xb0 - 0x3d];
	FeNode *m_next;
	FeNode *m_prev;
};

class Rva000FE001
{
public:
	void rva000FE001(FeNode *other);
	void rva000FE8FC(FeNode *other);
	void rva000FE188();

private:
	unsigned char m_pad[0x10];
	FeNode *m_tail10;
	FeNode *m_head14;
};

void Rva000FE001::rva000FE001(FeNode *other)
{
	if (other == 0)
		return;
	FeNode *next = other->m_next;
	if (next != 0)
		next->m_prev = other->m_prev;
	FeNode **prevLink = &other->m_prev;
	FeNode *prev = *prevLink;
	if (prev != 0)
		prev->m_next = other->m_next;
	else
		m_tail10 = other->m_next;
	*prevLink = 0;
	other->m_next = m_head14;
	if (m_head14 != 0)
		m_head14->m_prev = other;
	m_head14 = other;
}

void Rva000FE001::rva000FE8FC(FeNode *other)
{
	other->m_flag3c = 0;
	rva000FE001(other);
}

void Rva000FE001::rva000FE188()
{
	FeNode *node = m_tail10;
	while (node != 0)
	{
		FeNode *next = node->m_next;
		node->m_flag3c = 0;
		rva000FE001(node);
		node = next;
	}
	m_tail10 = 0;
}

// ?find@Rva00053FD2@@QBEPAURva00053FD2Node@@PAURva00053FD2Key@@@Z
// partial score=0.85 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
struct Rva00053FD2Ref
{
	int m_pad0;
	int m_pad4;
	int m_id;
};

struct Rva00053FD2Key
{
	Rva00053FD2Ref *m_ref;
};

struct Rva00053FD2Node
{
	Rva00053FD2Node *m_next;
	Rva00053FD2Ref *m_key;
};

class Rva00053FD2
{
	int m_pad0;
	Rva00053FD2Node **m_first;
	Rva00053FD2Node **m_last;
	int m_padC;
	int m_count;
public:
	bool isEqual(const void *a, const void *b) const;
	Rva00053FD2Node *find(Rva00053FD2Key *key) const;
};

Rva00053FD2Node *Rva00053FD2::find(Rva00053FD2Key *key) const
{
	unsigned hash;
	Rva00053FD2Ref *ref = key->m_ref;
	if (ref == 0)
		hash = 0;
	else
		hash = ref->m_id;
	unsigned count = (unsigned)(m_last - m_first);
	Rva00053FD2Node **buckets = *(Rva00053FD2Node *** volatile)&m_first;
	Rva00053FD2Node *node = buckets[hash % count];
	while (node != 0)
	{
		if (((const Rva00053FD2 *)((const char *)this + 1))->isEqual(node->m_key, ref))
			break;
		node = node->m_next;
	}
	return node;
}

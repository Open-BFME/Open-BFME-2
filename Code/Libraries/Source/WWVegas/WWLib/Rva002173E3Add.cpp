// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva002173E3@Rva002173E3@@QAEXPAURva002173E3Node@@@Z @0x002173E3 23B: intrusive list prepend with count; head at +0xC, count at +0x10, node next at +0x04. Evidence: single caller at 0x00218682 in unclaimed FUN_0061857e; LINK BONUS via 0x0021857E; neighbours in stlport_pod_vector_bodies page.

struct Rva002173E3Node
{
	int m_pad;
	Rva002173E3Node *m_next;
};

class Rva002173E3
{
public:
	void rva002173E3(Rva002173E3Node *node);

private:
	char m_pad[0x0C];
	Rva002173E3Node *m_head; // +0x0C
	int m_count; // +0x10
};

void Rva002173E3::rva002173E3(Rva002173E3Node *node)
{
	if (node == 0)
		return;
	node->m_next = m_head;
	++m_count;
	m_head = node;
}

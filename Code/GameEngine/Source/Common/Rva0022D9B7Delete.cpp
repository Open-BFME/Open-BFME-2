// cl: /MD
// ?rva0022D9B7@Rva0022DB29@@QAEXPAURva0022D9B7Node@@@Z @0x0022D9B7 28B: node delete calls rowed ??1Rva0022CFE6 at 0x0022CFE6 for +4 then rowed _free 0x00030830. Evidence: chain packet you-just-landed callee plus 28B lea-ecx+4 call-test-je free shape; caller 0x0022DB29 passes own this in ecx plus node push for linked-list traversal via +0.
class Rva0022CFE6
{
public:
	~Rva0022CFE6();
};
extern "C" void __cdecl free(void *);
struct Rva0022D9B7Node
{
	Rva0022D9B7Node *m_next;
	Rva0022CFE6 m_val;
};
class Rva0022DB29
{
public:
	void rva0022D9B7(Rva0022D9B7Node *node);
	void rva0022DB29();
private:
	int m_unk0;
	Rva0022D9B7Node **m_buckets;
	Rva0022D9B7Node **m_bucketsEnd;
	int m_unkC;
	int m_count;
};
void Rva0022DB29::rva0022D9B7(Rva0022D9B7Node *node)
{
	node->m_val.~Rva0022CFE6();
	if (node)
		free(node);
}
// ?rva0022DB29@Rva0022DB29@@QAEXXZ @0x0022DB29 73B: hash clear walks buckets via rowed delete 0x0022D9B7 then zeroes buckets and count. Evidence: chain packet plus caller 0x0022DC62 dtor shape.
void Rva0022DB29::rva0022DB29()
{
	for (unsigned i = 0; i < (unsigned)(m_bucketsEnd - m_buckets); ++i)
	{
		Rva0022D9B7Node *cur = m_buckets[i];
		while (cur)
		{
			Rva0022D9B7Node *next = cur->m_next;
			rva0022D9B7(cur);
			cur = next;
		}
		m_buckets[i] = 0;
	}
	m_count = 0;
}

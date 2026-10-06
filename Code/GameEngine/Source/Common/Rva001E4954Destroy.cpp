// cl: /MD
//
// ?rva001E4954@Rva001E4954@@QAEXPAURva001E4954Node@@@Z @0x001E4954 45B
// __thiscall void (Node *): destroy a sibling-linked tree; for each node in the
// +8 chain, recurse on the +0xc child with the same this, then free the node.
// Evidence: self-recursive call; _free row 0x00030830; callers 0x00263FA7
// 0x002E74C6; neighbours Rva001E4912Init stlport_map_int_int_os.
struct Rva001E4954Node
{
	char _00[8];
	struct Rva001E4954Node *m_08;
	struct Rva001E4954Node *m_0c;
};
class Rva001E4954
{
public:
	void rva001E4954(Rva001E4954Node *p);
};
extern "C" void __cdecl free(void *);
void Rva001E4954::rva001E4954(Rva001E4954Node *p)
{
	if (!p)
		return;
	do {
		rva001E4954(p->m_0c);
		Rva001E4954Node *next = p->m_08;
		free(p);
		p = next;
	} while (p);
}

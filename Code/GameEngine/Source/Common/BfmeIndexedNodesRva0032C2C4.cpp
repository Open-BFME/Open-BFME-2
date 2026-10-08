// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0032C2C4@TeamsInfoRec@@QAEXXZ @0x0032C2C4 51B
// Release chained indexed nodes with a nonzero +6 link.
// Evidence: same-this call to rowed ?removeTeam@TeamsInfoRec@@QAEXH@Z
// @0x0032C26D; walks 16B nodes at +0xC via signed-short links;
// twin of clearChainedNodesAt00197860 in Bfme5IndexedNodeRelease.cpp
// but outlining the release through removeTeam; callers @0x003303C1
// and jmp @0x0032C9C1.
struct BfmeIndexedNodeFM
{
	short m_previous;
	short m_next;
	short m_chainNext;
	short m_chainPrevious;
	char m_rest[8];
};

class TeamsInfoRec
{
public:
	void rva0032C2C4();
	void removeTeam(int index);

private:
	char m_pad[0xC];
	BfmeIndexedNodeFM *m_nodes;
};

void TeamsInfoRec::rva0032C2C4()
{
	int index = m_nodes[0].m_previous;
	while (index)
	{
		int next = m_nodes[index].m_previous;
		if (m_nodes[index].m_chainPrevious)
			removeTeam(index);
		index = next;
	}
}

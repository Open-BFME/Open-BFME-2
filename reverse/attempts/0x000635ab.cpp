// ?rva000635AB@Rva000635AB@@QAEXPAHH@Z
// partial score=0.97 date=2026-10-05
// ?rva000635AB@Rva000635AB@@QAEXPAHH@Z
// partial score=0.97 date=2026-10-05
#define NULL 0
// ?rva000635AB@Rva000635AB@@QAEXPAHH@Z @0x000635AB (77B): W3DGhostObject
// orphan sweep after the slot38-leaf precedent — the donor TU's model does
// not cover it. Walk m_usedModules; per parentless node refresh shroud for
// m_localPlayer, and when its snapshot slot is clear delete the partition
// data through rowed bfmeGoCDE; advance-or-stop via the sbb-neg-and select
// idiom (self-loop terminates). Layout offsets (+0x0C parent, +0x7C
// partition, +0x80 snapshots[20], +0xE0 next, manager +0x04 local player
// and +0x10 used head) from the matched W3DGhostObjectScene TU. The rowed
// protected getShroudStatus is reached through an address-honest pin.
// Honest address name; owning class unproven.

struct BfmeThingCDE
{
	void bfmeGoCDE();
};

class RvaGhostNode
{
public:
	void getShroudStatus(int player);

	void *m_pad00; // +0
	void *m_pad04; // +4
	void *m_pad08; // +8
	void *m_parentObject; // +0x0C
	char m_pad10[0x6C];
	BfmeThingCDE *m_partitionData; // +0x7C
	void *m_parentSnapshots[20]; // +0x80
	char m_padD0[0x10];
	RvaGhostNode *m_nextSystem; // +0xE0
};

class Rva000635AB
{
public:
	void rva000635AB(int *a, int b);

private:
	int m_pad00; // +0
	int m_localPlayer; // +0x04
	int m_pad08; // +0x08
	int m_pad0C; // +0x0C
	RvaGhostNode *m_usedModules; // +0x10
};

// ?rva000635AB@Rva000635AB@@QAEXPAHH@Z
void Rva000635AB::rva000635AB(int *a, int b)
{
	RvaGhostNode *node = m_usedModules;
	if (node == NULL)
		return;
loop:
	{
		RvaGhostNode *next = node->m_nextSystem;
		if (node->m_parentObject == NULL) {
			node->getShroudStatus(m_localPlayer);
			if (node->m_parentSnapshots[m_localPlayer] == NULL) {
				if (node->m_partitionData != NULL)
					node->m_partitionData->bfmeGoCDE();
			}
		}
		node = (node != next) ? next : NULL;
		if (node != NULL)
			goto loop;
	}
}

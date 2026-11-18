// Rva00382077: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin. Same shape as its twin Rva0038201D.h:
// the clear at 0x00382908 reads the sentinel at +0 and the node count at +4.
#ifndef CANONICAL_RVA00382077_H
#define CANONICAL_RVA00382077_H

struct Rva0038201DNode;

class Rva00382077
{
	Rva0038201DNode *m_head;
	int m_count;
	unsigned char m_storage08[4];

public:
	~Rva00382077();
	void rva00382077(Rva0038201DNode *node);
	void rva00382908();
};

#endif // CANONICAL_RVA00382077_H

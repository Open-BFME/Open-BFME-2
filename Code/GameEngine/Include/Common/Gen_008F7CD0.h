// Gen_008F7CD0: canonical declarations for the members 13 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_GEN_008F7CD0_H
#define CANONICAL_GEN_008F7CD0_H

class BfmeCellFD;
struct BfmeCellOut;
struct BfmePointFD;

class Gen_008F7CD0
{
public:
	int bfmeCellSum(const BfmePointFD *pt, int a, unsigned int b) const;
	int bfmeCellX(float) const;
	int bfmeCellY(float) const;
	void rva0073A2A0(BfmeCellFD * *first, BfmeCellFD * *last, int x1, int x2, int y);
	void rva0073BC60(int mask, int index, BfmeCellOut *out) const;
	void rva0073CE90(int x, int y, int radius, int counter, int amount, int mask);
};

#endif // CANONICAL_GEN_008F7CD0_H

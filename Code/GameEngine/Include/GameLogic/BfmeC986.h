// BfmeC986: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMEC986_H
#define CANONICAL_BFMEC986_H

class BfmeC986
{
public:
	void bfmeGo986C(int, int, int, int);
	void groupGatherAndAttackInFormationToPosition(int a, int b, int c, int d);
	void groupGatherAndMoveInFormationToPosition(int pos, int a, int b, int c);
	char privateGatherAndMoveInFormationToPosition(int pos, int a, int b, int c, int d);
};

#endif // CANONICAL_BFMEC986_H

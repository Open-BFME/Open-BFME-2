// Gen_0018BC70: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_GEN_0018BC70_H
#define CANONICAL_GEN_0018BC70_H

class BfmeVecAK;
class BfmeVisitorBF;

class Gen_0018BC70
{
public:
	BfmeVecAK *bfmeCompact(bool restart);
	void bfmeVisitAll(BfmeVisitorBF *visitor);
};

#endif // CANONICAL_GEN_0018BC70_H

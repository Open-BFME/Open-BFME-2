// BfmeA1209: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMEA1209_H
#define CANONICAL_BFMEA1209_H

struct BfmeS1209;

class BfmeA1209
{
public:
	void bfmeOp1209(const BfmeS1209 *cxform);
};

#endif // CANONICAL_BFMEA1209_H

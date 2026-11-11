// BfmeResultForwardB: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMERESULTFORWARDB_H
#define CANONICAL_BFMERESULTFORWARDB_H

struct BfmeResultA;

class BfmeResultForwardB
{
public:
	BfmeResultA bfmeForwardResultB(int value);
};

#endif // CANONICAL_BFMERESULTFORWARDB_H

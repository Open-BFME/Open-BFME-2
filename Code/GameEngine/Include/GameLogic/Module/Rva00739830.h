// Rva00739830: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00739830_H
#define CANONICAL_RVA00739830_H

struct BfmePointFD;

class Rva00739830
{
public:
	int rva00739830(const BfmePointFD *pt, int a, unsigned int b) const;
};

#endif // CANONICAL_RVA00739830_H

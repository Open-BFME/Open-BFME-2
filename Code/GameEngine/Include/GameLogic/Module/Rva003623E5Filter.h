// Rva003623E5Filter: canonical declarations for the members 8 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA003623E5FILTER_H
#define CANONICAL_RVA003623E5FILTER_H

class BfmeFixedStorage0004543D;

class Rva003623E5Filter
{
public:
	~Rva003623E5Filter();
	void applyFilter(BfmeFixedStorage0004543D storage);
};

#endif // CANONICAL_RVA003623E5FILTER_H

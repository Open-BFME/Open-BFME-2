// Rva007EAServiceList: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA007EASERVICELIST_H
#define CANONICAL_RVA007EASERVICELIST_H

class Rva00803080;

class Rva007EAServiceList
{
public:
	void add(Rva00803080 *entry);
	void remove(Rva00803080 *owner);
};

#endif // CANONICAL_RVA007EASERVICELIST_H

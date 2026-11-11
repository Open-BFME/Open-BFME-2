// Rva00463509: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00463509_H
#define CANONICAL_RVA00463509_H

class Object;

class Rva00463509
{
public:
	void removeFromContain(Object *object, bool flag);
};

#endif // CANONICAL_RVA00463509_H

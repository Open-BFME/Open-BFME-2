// Rva0037E6E8: canonical declarations for the members 11 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0037E6E8_H
#define CANONICAL_RVA0037E6E8_H

class Object;

class Rva0037E6E8
{
public:
	int rva0037E649(int index, Object *obj);
	int rva0037E6E8(void *extra, void *object);
	float rva0037E815(int, Object *);
	float rva0037E898(int index, int *cost, Object *obj);
};

#endif // CANONICAL_RVA0037E6E8_H

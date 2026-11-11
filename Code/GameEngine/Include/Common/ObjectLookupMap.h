// ObjectLookupMap: canonical declarations for the members 18 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_OBJECTLOOKUPMAP_H
#define CANONICAL_OBJECTLOOKUPMAP_H

class Object;

class ObjectLookupMap
{
public:
	void eraseSlot(int *p);
	Object **findSlot(int *key);
};

#endif // CANONICAL_OBJECTLOOKUPMAP_H

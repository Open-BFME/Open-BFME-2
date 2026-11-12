// ObjectCreationList: canonical declarations for the members 22 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_OBJECTCREATIONLIST_H
#define CANONICAL_OBJECTCREATIONLIST_H

class ObjectCreationNugget;

class ObjectCreationList
{
public:
	ObjectCreationList();
	void addObjectCreationNugget(ObjectCreationNugget *nugget);
	void create(void *a, void *b, void *c);
	void create(void *a, void *b, void *c, int d);
	void rva001F0410(void *a, void *b);
	bool rva001F0434(void *, void *);
};

#endif // CANONICAL_OBJECTCREATIONLIST_H

// ObjectCreationListStore: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_OBJECTCREATIONLISTSTORE_H
#define CANONICAL_OBJECTCREATIONLISTSTORE_H

class ObjectCreationList;

class ObjectCreationListStore
{
public:
	const ObjectCreationList *findObjectCreationList(const char *name);
	const ObjectCreationList *findObjectCreationList(const char *name) const;
};

#endif // CANONICAL_OBJECTCREATIONLISTSTORE_H

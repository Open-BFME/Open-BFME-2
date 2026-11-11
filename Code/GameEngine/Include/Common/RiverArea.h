// RiverArea: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RIVERAREA_H
#define CANONICAL_RIVERAREA_H

class RiverArea
{
public:
	void *getTextureName(int index);
};

#endif // CANONICAL_RIVERAREA_H

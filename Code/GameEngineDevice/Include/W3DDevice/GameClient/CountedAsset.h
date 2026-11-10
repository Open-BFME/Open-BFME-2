// CountedAsset: canonical declarations for the members 9 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_COUNTEDASSET_H
#define CANONICAL_COUNTEDASSET_H

class CountedAsset
{
public:
	void Release_Ref();
};

#endif // CANONICAL_COUNTEDASSET_H

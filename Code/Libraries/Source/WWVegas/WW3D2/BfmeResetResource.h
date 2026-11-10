// BfmeResetResource: canonical declarations for the members 9 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMERESETRESOURCE_H
#define CANONICAL_BFMERESETRESOURCE_H

struct BfmeResetResource
{
	void Add_Ref();
	void Release_Ref();
};

#endif // CANONICAL_BFMERESETRESOURCE_H

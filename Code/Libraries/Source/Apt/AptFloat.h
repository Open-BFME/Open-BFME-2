// AptFloat: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTFLOAT_H
#define CANONICAL_APTFLOAT_H

class AptFloat
{
public:
	static void ClearPool();
	float GetFloat() const;
};

#endif // CANONICAL_APTFLOAT_H

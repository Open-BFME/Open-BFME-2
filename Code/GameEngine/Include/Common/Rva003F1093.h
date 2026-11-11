// Rva003F1093: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA003F1093_H
#define CANONICAL_RVA003F1093_H

class CreateAHeroData;

class Rva003F1093
{
public:
	CreateAHeroData *rva003F083A(void *arg);
	void rva003F1CA2(CreateAHeroData *, bool);
	void rva003F1CFE(void *, bool);
};

#endif // CANONICAL_RVA003F1093_H

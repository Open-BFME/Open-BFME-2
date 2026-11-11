// Rva00219251: canonical declarations for the members 10 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00219251_H
#define CANONICAL_RVA00219251_H

class CreateAHeroData;
class UnicodeString;

class Rva00219251
{
public:
	CreateAHeroData *rva00219251(int a1, int a2, int a3, const UnicodeString &a4, int a5, int a6, int a7);
	void rva0021929D(CreateAHeroData **data);
};

#endif // CANONICAL_RVA00219251_H

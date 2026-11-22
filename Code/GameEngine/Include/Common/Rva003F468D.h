// Rva003F468D: canonical declarations for the members 17 units call through private views of it;
// each call resolves to the unit's ledger row or pin. Only the owner of both rows, VslotSmallBodiesZ.cpp,
// reads its layout: 0x003F468D and 0x003F4DAE load the entry table pointer at +0x18; the rest stays opaque.
#ifndef CANONICAL_RVA003F468D_H
#define CANONICAL_RVA003F468D_H

struct Rva003F468DEntry;

class Rva003F468D
{
public:
	int rva003F468D(int a, int b);
	int rva003F4DAE(int side);
private:
	char m_pad00[0x18];
	Rva003F468DEntry *m_18;
};

#endif // CANONICAL_RVA003F468D_H

// Rva006D0A30List: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA006D0A30LIST_H
#define CANONICAL_RVA006D0A30LIST_H

class EAStringC;
class Rva006D07E0Key;

class Rva006D0A30List
{
public:
	Rva006D07E0Key findSpecial(const EAStringC *);
	Rva006D07E0Key rva006D0B40(const EAStringC &);
};

#endif // CANONICAL_RVA006D0A30LIST_H

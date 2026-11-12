// Rva005088CE: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA005088CE_H
#define CANONICAL_RVA005088CE_H

class MultiIniFieldParse;

class Rva005088CE
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

#endif // CANONICAL_RVA005088CE_H

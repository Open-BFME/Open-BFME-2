// Rva002246B1: canonical declarations for the members 8 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002246B1_H
#define CANONICAL_RVA002246B1_H

class AsciiString;

class Rva002246B1
{
public:
	int RemoveCustomRender(const AsciiString *name);
};

#endif // CANONICAL_RVA002246B1_H

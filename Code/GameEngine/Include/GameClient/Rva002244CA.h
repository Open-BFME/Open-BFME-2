// Rva002244CA: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002244CA_H
#define CANONICAL_RVA002244CA_H

class AsciiString;

class Rva002244CA
{
public:
	int RemoveExternHandler(const AsciiString *name);
};

#endif // CANONICAL_RVA002244CA_H

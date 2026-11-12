// Rva005C4212: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA005C4212_H
#define CANONICAL_RVA005C4212_H

class Rva005C4212Visitor;

class Rva005C4212
{
public:
	void rva005C4212(Rva005C4212Visitor *visitor);
	void rva005C4221(Rva005C4212Visitor *visitor);
};

#endif // CANONICAL_RVA005C4212_H

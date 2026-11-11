// Rva00223591: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00223591_H
#define CANONICAL_RVA00223591_H

class AsciiString;

class Rva00223591
{
public:
	int rva00223736(const AsciiString *key);
	void rva0022380B();
};

#endif // CANONICAL_RVA00223591_H

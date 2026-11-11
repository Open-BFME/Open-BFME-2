// Rva002DC74A: canonical declarations for the members 9 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002DC74A_H
#define CANONICAL_RVA002DC74A_H

class UnicodeString;

class Rva002DC74A
{
public:
	UnicodeString rva002DC74A(const UnicodeString &leaf) const;
};

#endif // CANONICAL_RVA002DC74A_H

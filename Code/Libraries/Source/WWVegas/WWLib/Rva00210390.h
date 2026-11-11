// Rva00210390: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00210390_H
#define CANONICAL_RVA00210390_H

class AsciiString;

class Rva00210390
{
public:
	void *rva00210390(const AsciiString *s);
};

#endif // CANONICAL_RVA00210390_H

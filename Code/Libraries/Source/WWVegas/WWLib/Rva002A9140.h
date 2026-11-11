// Rva002A9140: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002A9140_H
#define CANONICAL_RVA002A9140_H

class AsciiString;

class Rva002A9140
{
public:
	AsciiString &rva002A9140(const int &key);
};

#endif // CANONICAL_RVA002A9140_H

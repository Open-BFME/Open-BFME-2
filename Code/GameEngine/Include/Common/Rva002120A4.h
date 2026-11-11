// Rva002120A4: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002120A4_H
#define CANONICAL_RVA002120A4_H

class AsciiString;
struct Rva002120C2Entry;

class Rva002120A4
{
public:
	Rva002120C2Entry *rva002120C2(const AsciiString &key);
};

#endif // CANONICAL_RVA002120A4_H

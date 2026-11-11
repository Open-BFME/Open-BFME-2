// Rva0035B232: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0035B232_H
#define CANONICAL_RVA0035B232_H

class AsciiString;

class Rva0035B232
{
public:
	const AsciiString *rva0035B232(int index);
};

#endif // CANONICAL_RVA0035B232_H

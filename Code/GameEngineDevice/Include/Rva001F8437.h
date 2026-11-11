// Rva001F8437: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA001F8437_H
#define CANONICAL_RVA001F8437_H

class AsciiString;

class Rva001F8437
{
public:
	void *rva001F8437(const AsciiString &key);
};

#endif // CANONICAL_RVA001F8437_H

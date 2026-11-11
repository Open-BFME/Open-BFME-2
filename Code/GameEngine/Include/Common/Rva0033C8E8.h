// Rva0033C8E8: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0033C8E8_H
#define CANONICAL_RVA0033C8E8_H

class AsciiString;

class Rva0033C8E8
{
public:
	bool removeModuleInfo(const AsciiString &, AsciiString &);
};

#endif // CANONICAL_RVA0033C8E8_H

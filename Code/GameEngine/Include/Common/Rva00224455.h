// Rva00224455: canonical declarations for the members 8 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00224455_H
#define CANONICAL_RVA00224455_H

class AsciiString;

class Rva00224455
{
public:
	int RemoveCommandMap(const AsciiString *name);
};

#endif // CANONICAL_RVA00224455_H

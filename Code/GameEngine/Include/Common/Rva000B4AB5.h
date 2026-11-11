// Rva000B4AB5: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA000B4AB5_H
#define CANONICAL_RVA000B4AB5_H

class AsciiString;

class Rva000B4AB5
{
public:
	const AsciiString *rva000B4AB5(unsigned int index);
};

#endif // CANONICAL_RVA000B4AB5_H

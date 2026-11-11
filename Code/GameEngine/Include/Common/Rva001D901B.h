// Rva001D901B: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA001D901B_H
#define CANONICAL_RVA001D901B_H

class ArmorTemplate;
class AsciiString;

class Rva001D901B
{
public:
	const ArmorTemplate *rva001D901B(const AsciiString &name) const;
};

#endif // CANONICAL_RVA001D901B_H

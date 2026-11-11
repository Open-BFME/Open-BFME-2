// Rva001F4E1BSlot: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA001F4E1BSLOT_H
#define CANONICAL_RVA001F4E1BSLOT_H

struct RGBColor;

class Rva001F4E1BSlot
{
public:
	const RGBColor *get() const;
};

#endif // CANONICAL_RVA001F4E1BSLOT_H

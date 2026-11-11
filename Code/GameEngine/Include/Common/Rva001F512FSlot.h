// Rva001F512FSlot: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA001F512FSLOT_H
#define CANONICAL_RVA001F512FSLOT_H

struct RGBColor;

class Rva001F512FSlot
{
public:
	const RGBColor *get() const;
};

#endif // CANONICAL_RVA001F512FSLOT_H

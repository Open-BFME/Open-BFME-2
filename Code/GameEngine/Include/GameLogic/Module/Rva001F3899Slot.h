// Rva001F3899Slot: canonical declarations for the members 16 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA001F3899SLOT_H
#define CANONICAL_RVA001F3899SLOT_H

struct Rva001F3899Arg;

class Rva001F3899Slot
{
public:
	void set(const Rva001F3899Arg &arg);
};

#endif // CANONICAL_RVA001F3899SLOT_H

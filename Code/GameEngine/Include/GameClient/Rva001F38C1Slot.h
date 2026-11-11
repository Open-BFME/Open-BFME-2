// Rva001F38C1Slot: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA001F38C1SLOT_H
#define CANONICAL_RVA001F38C1SLOT_H

struct Rva001F38C1Arg;

class Rva001F38C1Slot
{
public:
	void set(const Rva001F38C1Arg &);
};

#endif // CANONICAL_RVA001F38C1SLOT_H

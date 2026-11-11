// Rva00549DCB: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00549DCB_H
#define CANONICAL_RVA00549DCB_H

struct Foo00549DCB;

struct Rva00549DCB
{
	bool rva00549DCB(Foo00549DCB *const &lhs, Foo00549DCB *const &rhs) const;
};

#endif // CANONICAL_RVA00549DCB_H

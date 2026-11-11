// Rva002D9C2F: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002D9C2F_H
#define CANONICAL_RVA002D9C2F_H

struct OpaqueRefElement4;

class Rva002D9C2F
{
public:
	OpaqueRefElement4 &rva002D9C2F(const OpaqueRefElement4 &other);
};

#endif // CANONICAL_RVA002D9C2F_H

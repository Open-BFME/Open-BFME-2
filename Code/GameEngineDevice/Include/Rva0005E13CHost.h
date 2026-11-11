// Rva0005E13CHost: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0005E13CHOST_H
#define CANONICAL_RVA0005E13CHOST_H

struct Rva0005E13CArg;
struct Rva0005E13CInner1;

class Rva0005E13CHost
{
public:
	bool helper(const Rva0005E13CInner1 *a);
	bool rva0005E13C(const Rva0005E13CArg *chainStart);
};

#endif // CANONICAL_RVA0005E13CHOST_H

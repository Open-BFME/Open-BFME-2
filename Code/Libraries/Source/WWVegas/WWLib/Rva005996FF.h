// Rva005996FF: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA005996FF_H
#define CANONICAL_RVA005996FF_H

struct Rva005996FFArg;

class Rva005996FF
{
public:
	void unRegisterDozer(Rva005996FFArg *arg, bool flag);
};

#endif // CANONICAL_RVA005996FF_H

// Rva005DDE01: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA005DDE01_H
#define CANONICAL_RVA005DDE01_H

struct BfmeStringRecord005DDD40;

class Rva005DDE01
{
public:
	void AddStat(unsigned int, unsigned int, const BfmeStringRecord005DDD40 &, bool);
};

#endif // CANONICAL_RVA005DDE01_H

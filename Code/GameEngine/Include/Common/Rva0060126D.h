// Rva0060126D: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0060126D_H
#define CANONICAL_RVA0060126D_H

struct Rva00600F9CElement;
struct Rva006013B7Pair;

class Rva0060126D
{
public:
	void *rva006012A2(const Rva00600F9CElement &val);
	Rva006013B7Pair rva006013B7(const Rva00600F9CElement &element);
};

#endif // CANONICAL_RVA0060126D_H

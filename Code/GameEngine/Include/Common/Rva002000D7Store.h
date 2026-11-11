// Rva002000D7Store: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002000D7STORE_H
#define CANONICAL_RVA002000D7STORE_H

struct Rva002000D7Config;

class Rva002000D7Store
{
public:
	Rva002000D7Config *get(int v);
};

#endif // CANONICAL_RVA002000D7STORE_H

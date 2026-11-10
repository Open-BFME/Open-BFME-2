// Rva0025BFF8: canonical declarations for the members 10 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0025BFF8_H
#define CANONICAL_RVA0025BFF8_H

class Object;
struct Rva005964B0Position;

class Rva0025BFF8
{
public:
	Object *rva0025BFF8(int index);
	int rva005964B0(int index);
	Rva005964B0Position rva005964C7(int index);
};

#endif // CANONICAL_RVA0025BFF8_H

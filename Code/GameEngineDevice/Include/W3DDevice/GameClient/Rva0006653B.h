// Rva0006653B: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0006653B_H
#define CANONICAL_RVA0006653B_H

class Vector3;

class Rva0006653B
{
public:
	unsigned short rva0006653B(int x, int y);
	void rva0006AA45(int x, int y, Vector3 *normal);
};

#endif // CANONICAL_RVA0006653B_H

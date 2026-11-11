// Rva00368C7A: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00368C7A_H
#define CANONICAL_RVA00368C7A_H

struct Coord3D;

class Rva00368C7A
{
public:
	void rva003681F2(const Coord3D *position, const unsigned char *mask, const Coord3D *lookAhead, bool b);
	unsigned char rva00368271();
	int rva00368B51(float distance, bool flag);
	void rva00368C7A(float amount, const Coord3D *position, bool argument);
};

#endif // CANONICAL_RVA00368C7A_H

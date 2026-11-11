// Rva000E016A: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA000E016A_H
#define CANONICAL_RVA000E016A_H

struct BfmeE12;
struct Coord3D;

class Rva000E016A
{
public:
	BfmeE12 *rva000E016A(unsigned int n, Coord3D *first, Coord3D *last);
};

#endif // CANONICAL_RVA000E016A_H

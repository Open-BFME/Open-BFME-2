// Rva002FFFCA: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002FFFCA_H
#define CANONICAL_RVA002FFFCA_H

struct Coord3D;
class Object;

class Rva002FFFCA
{
public:
	void *rva002FF07B(Object *me, const Coord3D *pos, float range, unsigned int qualifiers, int info, int optionalFilter, int bfmeArg);
	void *rva002FFFCA(Object *me, const Coord3D *pos, float range, unsigned int qualifiers, int a, int b, int c);
};

#endif // CANONICAL_RVA002FFFCA_H

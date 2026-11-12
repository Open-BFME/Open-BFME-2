// Rva002EBC34: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002EBC34_H
#define CANONICAL_RVA002EBC34_H

struct Coord3D;
struct ICoord2D;

class Rva002EBC34
{
public:
	ICoord2D *rva002EBC34(ICoord2D *a1, void *a2, const Coord3D *a3);
};

#endif // CANONICAL_RVA002EBC34_H

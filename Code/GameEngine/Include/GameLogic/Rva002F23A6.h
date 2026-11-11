// Rva002F23A6: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002F23A6_H
#define CANONICAL_RVA002F23A6_H

struct Coord3D;
class Object;

class Rva002F23A6
{
public:
	bool rva002F23A6(Object *source, int weapon, int locomotorSet, Coord3D *goalPos, Object *victim);
};

#endif // CANONICAL_RVA002F23A6_H

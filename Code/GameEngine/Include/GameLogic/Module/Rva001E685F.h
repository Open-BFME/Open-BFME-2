// Rva001E685F: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA001E685F_H
#define CANONICAL_RVA001E685F_H

struct Coord3D;
class Object;

class Rva001E685F
{
public:
	void rva001E685F(Object *obj, const Coord3D *pos, float *angle);
};

#endif // CANONICAL_RVA001E685F_H

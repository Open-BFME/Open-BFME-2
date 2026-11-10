// Rva005EE816: canonical declarations for the members 17 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA005EE816_H
#define CANONICAL_RVA005EE816_H

struct Coord3D;
class Object;

class Rva005EE816
{
public:
	unsigned int rva005D8C4C(Object *obj);
	unsigned int rva005D8F0F(Object *obj);
	unsigned int rva005D91D2(Object *obj);
	unsigned int rva005D9721(Object *obj);
	void rva005EE317(Coord3D *dir);
	unsigned int rva005EE3B0(Object *obj, bool flag);
	bool rva005EE8DD(const Coord3D *pos, Object *source);
};

#endif // CANONICAL_RVA005EE816_H

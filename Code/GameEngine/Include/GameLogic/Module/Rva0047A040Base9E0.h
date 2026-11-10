// Rva0047A040Base9E0: canonical declarations for the members 9 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0047A040BASE9E0_H
#define CANONICAL_RVA0047A040BASE9E0_H

struct Coord3D;
class Object;
class Rva00588E44Contain;

class Rva0047A040Base9E0
{
public:
	Rva0047A040Base9E0();
	void *rva00588B8A(void *obj);
	void rva00588BA8(Object *obj, bool flag);
	Rva00588E44Contain *rva00588BF3(void *owner, Object *obj);
	Object *rva00588C4E(void *contain, const Coord3D *pos);
	bool rva00588D24(void *a, Object *b);
	void rva00588D99(Object *obj);
	void rva00588E20(Object *obj);
	void rva00588E44(void *contain);
};

#endif // CANONICAL_RVA0047A040BASE9E0_H

// Rva001E46E1: canonical declarations for the members 21 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA001E46E1_H
#define CANONICAL_RVA001E46E1_H

struct Coord3D;
class Object;

class Rva001E46E1
{
public:
	bool rva001E4015(Object *, const Coord3D *);
	float rva001E46E1(Object *);
	float rva001E4845(Object *obj);
	float rva001E488A(Object *obj);
	void rva001E53D8(float speed, Object *obj);
	bool rva001E543F(Object *obj);
	void rva001E546B(Object *);
	bool rva001E5F1D(Object *, const Coord3D *, float *);
	void rva001E6007(Object *obj, const Coord3D *goal, float distance, float desiredSpeed);
};

#endif // CANONICAL_RVA001E46E1_H

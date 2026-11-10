// Rva002BF4F3: canonical declarations for the members 18 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002BF4F3_H
#define CANONICAL_RVA002BF4F3_H

class RenderObjClass;
class Vector3;

class Rva002BF4F3
{
public:
	void rva002BEA10(RenderObjClass *, bool);
	bool rva002BF2B7(int screen, Vector3 *world);
	bool rva002BF5B0(const Vector3 *in, Vector3 *out);
	bool rva002BF935(void *obj, const Vector3 *pos, Vector3 *result);
};

#endif // CANONICAL_RVA002BF4F3_H

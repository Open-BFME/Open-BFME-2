// Rva0046E6EA: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0046E6EA_H
#define CANONICAL_RVA0046E6EA_H

struct Rva0046E6EACoord;
struct Rva0046E6EAObject;

class Rva0046E6EA
{
public:
	bool rva0046E6EA(Rva0046E6EAObject *obj, const Rva0046E6EACoord *pos, Rva0046E6EACoord *out, bool flag);
};

#endif // CANONICAL_RVA0046E6EA_H

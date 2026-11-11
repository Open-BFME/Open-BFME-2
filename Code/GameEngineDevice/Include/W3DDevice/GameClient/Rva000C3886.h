// Rva000C3886: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA000C3886_H
#define CANONICAL_RVA000C3886_H

struct Rva000C3886Obj;
struct Rva000C3886Range;

class Rva000C3886
{
public:
	void rva000BE245(void *first, float value, Rva000C3886Obj *obj, void *last);
	void rva000C3886(void *first, float value, Rva000C3886Range *range, Rva000C3886Obj *obj, void *last);
};

#endif // CANONICAL_RVA000C3886_H

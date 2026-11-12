// Rva002C025AViewer: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002C025AVIEWER_H
#define CANONICAL_RVA002C025AVIEWER_H

class Rva002C025AViewer
{
public:
	void *rva002C025A(void *point, unsigned int kind, bool flag);
};

#endif // CANONICAL_RVA002C025AVIEWER_H

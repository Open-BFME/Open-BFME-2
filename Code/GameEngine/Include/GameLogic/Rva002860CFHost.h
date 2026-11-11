// Rva002860CFHost: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002860CFHOST_H
#define CANONICAL_RVA002860CFHOST_H

struct Rva002860CFIterator;

class Rva002860CFHost
{
public:
	void rva002860CF(Rva002860CFIterator it);
};

#endif // CANONICAL_RVA002860CFHOST_H

// Rva002E3766Holder: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002E3766HOLDER_H
#define CANONICAL_RVA002E3766HOLDER_H

class Rva002E3766Holder
{
public:
	void notifyObjectEntered(int obj);
	void notifyObjectExited(int obj);
	void set(int, int);
};

#endif // CANONICAL_RVA002E3766HOLDER_H

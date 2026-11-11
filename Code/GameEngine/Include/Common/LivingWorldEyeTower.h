// LivingWorldEyeTower: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_LIVINGWORLDEYETOWER_H
#define CANONICAL_LIVINGWORLDEYETOWER_H

class Rva003F936EHost;
class U4Target0060C2C0;

class LivingWorldEyeTower
{
public:
	void rva003F9B5A();
private:
	void rva003F935A(U4Target0060C2C0 *target, void *payload);
	void rva003F936E(Rva003F936EHost *host, float *f);
};

#endif // CANONICAL_LIVINGWORLDEYETOWER_H

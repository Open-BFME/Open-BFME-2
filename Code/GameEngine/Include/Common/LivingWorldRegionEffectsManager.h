// LivingWorldRegionEffectsManager: canonical declarations for the members 14 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_LIVINGWORLDREGIONEFFECTSMANAGER_H
#define CANONICAL_LIVINGWORLDREGIONEFFECTSMANAGER_H

class LivingWorldRegionEffectsManager
{
public:
	void SyncRegion(int value);
	void rva003EF13E(int value, int, int);
	void rva003EF2FF();
};

#endif // CANONICAL_LIVINGWORLDREGIONEFFECTSMANAGER_H

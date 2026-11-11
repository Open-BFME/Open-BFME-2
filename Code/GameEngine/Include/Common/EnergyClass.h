// Energy: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_ENERGY_H
#define CANONICAL_ENERGY_H

class Object;

class Energy
{
public:
	void adjustPower(int amount, bool incoming);
	float getEnergySupplyRatio() const;
	void objectEnteringInfluence(Object *obj);
	void objectLeavingInfluence(Object *obj);
};

#endif // CANONICAL_ENERGY_H

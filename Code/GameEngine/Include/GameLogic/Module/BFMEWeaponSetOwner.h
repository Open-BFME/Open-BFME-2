// BFMEWeaponSetOwner: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMEWEAPONSETOWNER_H
#define CANONICAL_BFMEWEAPONSETOWNER_H

class BFMEWeaponSetFlags;

class BFMEWeaponSetOwner
{
public:
	const BFMEWeaponSetFlags &getWeaponSetFlags() const;
};

#endif // CANONICAL_BFMEWEAPONSETOWNER_H

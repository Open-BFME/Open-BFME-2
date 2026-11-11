// Rva00397F45: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00397F45_H
#define CANONICAL_RVA00397F45_H

class Player;

class Rva00397F45
{
public:
	bool isPlayerAllowedToPackOrUnpack(Player *player, int flag);
};

#endif // CANONICAL_RVA00397F45_H

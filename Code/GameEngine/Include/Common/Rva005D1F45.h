// Rva005D1F45: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA005D1F45_H
#define CANONICAL_RVA005D1F45_H

class GameMessage;
struct IRegion2D;

class Rva005D1F45
{
public:
	int rva005D1F45(IRegion2D *region, int value);
	int rva005D1FD3(GameMessage *message);
};

#endif // CANONICAL_RVA005D1F45_H

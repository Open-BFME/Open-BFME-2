// Rva005E6817Mid: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA005E6817MID_H
#define CANONICAL_RVA005E6817MID_H

class GameMessage;

class Rva005E6817Mid
{
public:
	int fwd(GameMessage *msg);
};

#endif // CANONICAL_RVA005E6817MID_H

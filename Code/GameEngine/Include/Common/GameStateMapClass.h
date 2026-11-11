// GameStateMap: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_GAMESTATEMAP_H
#define CANONICAL_GAMESTATEMAP_H

class Xfer;

class GameStateMap
{
public:
	void DoXfer(Xfer *);
	void clearScratchPadMaps();
};

#endif // CANONICAL_GAMESTATEMAP_H

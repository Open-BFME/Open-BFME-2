// BfmeSinkSKA: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMESINKSKA_H
#define CANONICAL_BFMESINKSKA_H

class BfmeSinkSKA
{
public:
	void bfmeSendSKA(int category, int transactionId, int depth);
	void sendCreateGameRequest(int transactionId, int gameId, int maxPlayers, const char *userGameId);
};

#endif // CANONICAL_BFMESINKSKA_H

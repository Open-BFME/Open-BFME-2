// cl: /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerSB.c */

typedef struct PEERConnection
{
	unsigned char pad_0000[0x0BA0];
	int sbInitialized;
	unsigned char pad_0BA4[0x0D34];
	unsigned char autoMatchList[0x05CC];
	unsigned char autoMatchEngine[0x0048];
	int autoMatchBrowsing;
	unsigned char pad_1EF0[8];
	const char *autoMatchFilter;
	int autoMatchSBFailed;
} PEERConnection;

typedef PEERConnection *PEER;

void SBServerListDisconnect(void *serverList);
void SBEngineHaltUpdates(void *queryEngine);

void piSBStopListingAutoMatches(PEER peer)
{
	if (!peer->sbInitialized)
		return;

	peer->autoMatchBrowsing = 0;
	SBServerListDisconnect(&peer->autoMatchList);
	SBEngineHaltUpdates(&peer->autoMatchEngine);
}

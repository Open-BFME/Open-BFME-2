// cl: /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerAutoMatch.c */

typedef struct PEERConnection
{
	unsigned char pad_0000[0x1EF4];
	void *autoMatchReporting;
} PEERConnection;

typedef PEERConnection *PEER;

void qr2_shutdown(void *queryReport);

void piStopAutoMatchReporting(PEER peer)
{
	if (peer->autoMatchReporting)
	{
		qr2_shutdown(peer->autoMatchReporting);
		peer->autoMatchReporting = 0;
	}
}

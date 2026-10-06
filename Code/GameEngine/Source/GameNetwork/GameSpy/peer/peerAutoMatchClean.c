// cl: /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerAutoMatch.c */

typedef struct PEERConnection
{
	unsigned char pad_0000[0x1EF0];
	void *autoMatchOperation;
	unsigned char pad_1EF4[4];
	char *autoMatchFilter;
} PEERConnection;

typedef PEERConnection *PEER;

/* BFME2 links the CRT directly here (retail import slot is msvcr71!free);
   same gsifree->free mapping as the landed peerCallbacks.c sibling. */
#define gsifree free
extern __declspec(dllimport) void __cdecl free(void *memory);
void piRemoveOperation(PEER peer, void *operation);

static __declspec(noinline) void piCleanAutoMatch(PEER peer)
{
	gsifree(peer->autoMatchFilter);
	piRemoveOperation(peer, peer->autoMatchOperation);
	peer->autoMatchOperation = 0;
}

void piCleanAutoMatchCaller(PEER peer)
{
	piCleanAutoMatch(peer);
}

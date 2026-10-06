// cl: /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerHost.c */

typedef void *PEER;

typedef struct piConnection
{
	unsigned char pad_0000[0x0AF0];
	void *queryReporting;
} piConnection;

void qr2_shutdown(void *queryReport);

void piStopReporting(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	if (connection->queryReporting)
	{
		qr2_shutdown(connection->queryReporting);
		connection->queryReporting = 0;
	}
}

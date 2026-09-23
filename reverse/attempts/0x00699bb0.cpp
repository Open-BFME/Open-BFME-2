// _peerAuthenticateCDKey
// partial score=0.86 date=2026-09-23
// cl: /DNDEBUG /MD
/* GameSpy Peer SDK -- peerMain.c, 2007 release.
   peerAuthenticateCDKey, retail 0x00699BB0, 144 bytes.
   Verbatim source import: BFME1 attests the identical body shape (classic
   blocking-call pattern over piThink + PeerOperationsComplete, unlike the
   bfme-custom bfmePiThinkFromEsi + piIsOperationFinished wrappers the
   ChangeNick/JoinTitleRoom siblings use). All eight callees are rowed;
   the "Error starting CD Key check" literal is unique image-wide. */

typedef void *PEER;

typedef struct piConnection
{
	char unreconstructed_0000[0x1824];
	int callbackDepth;
	char unreconstructed_1828[0x1F08 - 0x1828];
	int shutdown;
} piConnection;

int piGetNextID(PEER peer);
int piNewAuthenticateCDKeyOperation(PEER peer, const char *cdkey,
	void *callback, void *param, int opID);
void piAddAuthenticateCDKeyCallback(PEER peer, int result,
	const char *message, void *callback, void *param, int opID);
void msleep(unsigned int milliseconds);
void bfmePiThinkFromEsi(int opID);
int PeerOperationsComplete(PEER peer, int opID);
int piIsCallbackFinished(PEER peer, int opID);
void peerShutdown(PEER peer);

void peerAuthenticateCDKey(PEER peer, const char *cdkey, void *callback,
	void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	int opID = piGetNextID(peer);

	if (!piNewAuthenticateCDKeyOperation(peer, cdkey, callback, param, opID))
		success = 0;
	if (!success)
		piAddAuthenticateCDKeyCallback(peer, 0,
			"Error starting CD Key check", callback, param, opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!PeerOperationsComplete(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}

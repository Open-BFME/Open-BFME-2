// cl: /DNDEBUG /MD
/* GameSpy Peer SDK -- peerMain.c */

/* peerStateChanged: the connection checks are asserts in the SDK, so the
   release body is the bare tail jump to piSendStateChanged (0x006A7610,
   peerSendStateChanged.c). PeerThread.cpp's Thread_Function 0x0038EDD7 and
   doQuickMatch 0x0038E684 call it where the Zero Hour source calls
   peerStateChanged. */

typedef void *PEER;

void piSendStateChanged(PEER peer);

void peerStateChanged(PEER peer)
{
	piSendStateChanged(peer);
}

// cl: /DNDEBUG /DWIN32 /MD -Ireference/shims/gamespy -Ireference/open-bfme-1/Code/GameEngine/Source/GameNetwork/GameSpy/ghttp
/* GameSpy SDK, ~2005 snapshot (BFME 2) -- upstream C source PLUS a reconstruction of
   the deltas between the carrier's text and retail's snapshot, inferred from
   retail's bytes -- most of them upstream's own later text, not EA's.  Not
   pristine: see PROVENANCE.txt, "What differs from upstream", which lists
   every such file, what changed, and which deltas the 2007 SDK confirms as
   upstream.  Each changed site is also marked in place.
   Carrier: the Area 51 (Inevitable Entertainment / Midway) source release,
   github.com/bisc67/Area51, Support/NetworkMgr/GameSpy -- the only public
   carrier with the pre-2006 SDK layout (top-level nonport.c, no common/),
   itself dated 08-02-2004 by nonport.h's marker.  game.dat's SDK is a later
   upstream snapshot than that carrier's and than lotrbfme.exe's (see
   PROVENANCE.txt, "Which SDK this is"); the 440-vs-51 count that dated
   BFME 1's tree was measured against lotrbfme.exe, not here.  What stands
   here is the gate: every row from this TU byte-verifies against game.dat.
   Retail linked the DLL CRT, so libc calls are __imp__ indirect -- /MD is what
   makes those call sites byte-exact -- and built the SDK __cdecl: /Gz collapses
   the qr2+GP+ghttp core from 108 exact hits to 6.
   Win32 headers come from reference/shims/gamespy (see its windows.h): the
   toolchain ships no PlatformSDK, and the sweep shim next door is C++-only.

   This TU (ghttpCallbacks.c) is not present in the Area51 carrier tree -- the
   three ghiCall*Callback() trampolines are declared in ghttpCallbacks.h but
   were never checked in as a standalone .c anywhere upstream that has been
   found. ghiCallProgressCallback is reconstructed from game.dat's
   disassembly at 0x006BAE90 (connection->progressCallback dispatch, matching
   the ghttpProgressCallback typedef in ghttp.h field-for-field).
   ghiCallCompletedCallback is reconstructed from game.dat's disassembly at
   0x006BAE30: only for GHIGET requests does it pass the getFileBuffer.data
   pointer and fileBytesReceived through to the callback (all other request
   types pass NULL/0, matching the ghttp.h contract that buffer is "only
   valid if ghttpGetFile[Ex] was used"); if a buffer was passed and the
   callback returns GHTTPFalse, getFileBuffer.dontFree is set per the
   documented "return false if the app will free the buffer" contract.
   ghiCallPostCallback is reconstructed from game.dat's disassembly at
   0x006BAEE0: it calls postingState.callback with (request, bytesPosted,
   totalBytes, index, ArrayLength(states), connection->callbackParam) --
   matching the ghttpPostCallback typedef's (request, bytesPosted,
   totalBytes, objectsPosted, totalObjects, param) field-for-field, with
   postingState.index doing double duty as "objects posted so far" and
   ArrayLength(postingState.states) as "total objects". */
/*
GameSpy GHTTP SDK
Dan "Mr. Pants" Schoenblum
dan@gamespy.com

Copyright 1999-2001 GameSpy Industries, Inc

18002 Skypark Circle
Irvine, California 92614
949.798.4200 (Tel)
949.798.4299 (Fax)
devsupport@gamespy.com
*/

#include "ghttpCallbacks.h"

// ghiCallProgressCallback present-unmatched
// Call the progress callback for this connection.
//////////////////////////////////////////////////
void ghiCallProgressCallback
(
	GHIConnection * connection,
	const char * buffer,
	GHTTPByteCount bufferLen
)
{
	if(connection->progressCallback)
	{
		connection->progressCallback(connection->request, connection->state,
			buffer, bufferLen, connection->fileBytesReceived,
			connection->totalSize, connection->callbackParam);
	}
}

// ghiCallCompletedCallback present-unmatched
// Call the completed callback for this connection.
///////////////////////////////////////////////////
void ghiCallCompletedCallback
(
	GHIConnection * connection
)
{
	if(connection->completedCallback)
	{
		char * buffer;
		GHTTPByteCount bufferLen;
		GHTTPBool result;

		if(connection->type != GHIGET)
		{
			buffer = NULL;
			bufferLen = 0;
		}
		else
		{
			buffer = connection->getFileBuffer.data;
			bufferLen = connection->fileBytesReceived;
		}

		result = connection->completedCallback(connection->request, connection->result,
			buffer, bufferLen, connection->callbackParam);

		if(buffer && !result)
			connection->getFileBuffer.dontFree = GHTTPTrue;
	}
}

// ghiCallPostCallback present-unmatched
// Call the post callback for this connection.
//////////////////////////////////////////////
void ghiCallPostCallback
(
	GHIConnection * connection
)
{
	if(connection->postingState.callback)
	{
		connection->postingState.callback(connection->request,
			connection->postingState.bytesPosted,
			connection->postingState.totalBytes,
			connection->postingState.index,
			ArrayLength(connection->postingState.states),
			connection->callbackParam);
	}
}

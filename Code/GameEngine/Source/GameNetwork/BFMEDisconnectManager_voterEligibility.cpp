// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameNetwork/BFMEDisconnectManager_voterEligibility.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: BFMEDisconnectManager::hasPlayerConnectionTimedOut 0x004D3B7E
// (55B). Callee addresses are read off retail's call sites
// (reverse/symbols.csv). Only the placed bodies are carried; the donor's other
// definitions are omitted.

typedef bool Bool;
typedef int Int;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
#include "../../Include/GameNetwork/ConnectionManager.h"

class BFMEDisconnectManager
{
public:
	Bool hasPlayerConnectionTimedOut(int slot, void *connectionManager);
	Int countVoters(void *connectionManager);
};


Bool BFMEDisconnectManager::hasPlayerConnectionTimedOut(int slot, void *connectionManager)
{
	ConnectionManager *manager = (ConnectionManager *)connectionManager;
	if ((unsigned int)slot < 8) {
		if (manager == 0)
			return false;
		if (manager->isPlayerConnected(slot) && manager->_bfme_slotIsLocalOrLive(slot))
			return false;
	}
	return true;
}


// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x004CEF58 -> ?rva004CEF58@BFMEConnectionManager@@QAEEH@Z
#pragma comment(linker, "/alternatename:?_bfme_slotIsLocalOrLive@ConnectionManager@@QAE_NH@Z=?rva004CEF58@BFMEConnectionManager@@QAEEH@Z")

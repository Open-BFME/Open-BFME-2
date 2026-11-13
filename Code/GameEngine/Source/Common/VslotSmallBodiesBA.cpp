// cl: /DNDEBUG /MD
//
// Vtable-slot bodies of the network object (vtable VA 0x00BF6040, class
// Rva0025E4CD after its destructor) that had no ledger owner, plus the one
// ConnectionManager forwarder two of them call. Each slot reads the
// ConnectionManager at +0x0C (the member Rva0025E4CDSlot47.cpp already calls
// ConnectionManager::getPlayerName through) and, when it is set, forwards to
// it or reads one of its fields. Field offsets follow the BFME2
// ConnectionManager view in reference/shims/connectionmanager; the object at
// ConnectionManager+0x12100 is the one ConnectionManagerCtor.cpp creates and
// initialises through DisconnectManager::init. Method names stay address
// derived: the bytes prove the hops, offsets and argument counts only.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class ConnectionManager;

class DisconnectManager
{
public:
	void voteForPlayerDisconnect(Int slot, ConnectionManager *conMgr);
private:
	char m_pad00[0x270];
public:
	Bool m_270;
};

// 0x004D0AA9 is rowed as BFMEConnectionManager::sendFrameInfo(bool).
#include "../../Include/GameNetwork/BFMEConnectionManager.h"

// The 0x2000-byte per-slot records at ConnectionManager+0x24; the method the
// slot query calls is the ICF-folded `xor eax,eax; ret` at 0x000D43D0.
#include "../../Include/Common/Rva0025DE76Slot.h"

struct Rva0025DBDCPair
{
	UnsignedInt m_first;
	UnsignedInt m_second;
};

#include "../../Include/GameNetwork/ConnectionManager.h"

#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Rva0025E4CD
{
public:
	virtual ~Rva0025E4CD();

	virtual void rva0025DBAE(Int value);
	void rva0025DBDC(const Rva0025DBDCPair &pair);
	virtual Int rva0025DC7A();
	virtual Int rva0025DC95();
	virtual Int rva0025DCB0();
	virtual Int rva0025DD25();
	virtual Int rva0025DE5C();
	virtual Int rva0025DE76(Int slot);
	virtual Int rva0025DEA2(Int slot);
	virtual void rva0025E20F(Int slot);
	virtual void rva0025E28E();
private:
	char m_pad04[8];
	ConnectionManager *m_mgr;	// +0x0C
	Int m_10;
};

// ConnectionManager+0x12100's 0x004D3DF4 with this manager, when that object exists.
void ConnectionManager::voteForPlayerDisconnect(Int slot)
{
	if (m_disconnectManager)
		m_disconnectManager->voteForPlayerDisconnect(slot, this);
}

// The slot query is the shared `xor eax,eax; ret` 0x000D43D0 (rowed as an
// identical-code-folded alias).
Int Rva0025DE76Slot::rva000D43D0()
{
	return 0;
}

// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;

class ConnectionManager;
class NetCommandMsg;

class NetProgressCommandMsg
{
public:
	unsigned char getPercentage();
};

#include "../../Include/GameNetwork/Rva004D38D8.h"

class GameLogic;
extern GameLogic *TheGameLogic;
// The data ledger records VA 0x00BBB8D4 as the pooled 0.25f literal; its
// existing C alias is used here only for the target threshold value.
// length_estimate_factor was the retail address alias (RVA 0x007BB8D4) of the pooled constant 0.25f; the literal is the source.

class DisconnectManager
{
protected:
	__declspec(noinline) void resetPlayerTimeout(int slot);
public:
	void processDisconnectKeepAlive(void *keepAliveMsg, ConnectionManager *a2);
	void processDisconnectPlayer(NetCommandMsg *msg, ConnectionManager *conMgr);
protected:
	void disconnectPlayer(int slot, ConnectionManager *conMgr); // rowed 0x004D41B3
public:
	void processDisconnectCommand(void *ref, ConnectionManager *conMgr);
protected:
	void processDisconnectVote(NetCommandMsg *msg, ConnectionManager *conMgr);
	void processDisconnectFrame(NetCommandMsg *msg, ConnectionManager *conMgr);
	char m_pad00[0x14];
private:
	long m_playerTimeouts[1]; // +0x14
};

// Target evidence: 0x004D46AF dispatches command type 0x1A here with
// (message, connection manager). This body reads a byte through the rowed
// 0x004C54EC getter; forwards it with the connection manager to 0x004D41B3;
// then checks the rowed ratio helper 0x004D38D8 at thresholds in target .rdata
// (0.1f and 0.25f); finally it writes TheGameLogic +0x2A4.
// The BFME1 DisconnectManager source at donor revision
// 6583b3c1ff21db4a561285717028fdafc780b7db supplies related ratio semantics,
// but its command mapping and callees differ; the target method stays RVA-named.
void DisconnectManager::processDisconnectPlayer(NetCommandMsg *msg, ConnectionManager *conMgr)
{
	disconnectPlayer(((NetProgressCommandMsg *)msg)->getPercentage(), conMgr);
	if (!((Rva004D38D8 *)this)->rva004D38D8(0.1f)) {
		*(Int *)((char *)TheGameLogic + 0x2A4) = 1;
		return;
	}
	if (!((Rva004D38D8 *)this)->rva004D38D8(0.25f)
		&& (*(Int *)((char *)TheGameLogic + 0x2A4) != 1)) {
		*(Int *)((char *)TheGameLogic + 0x2A4) = 0;
	}
}

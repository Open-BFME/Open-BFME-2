// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;

class ConnectionManager;
class NetCommandMsg;

class NetProgressCommandMsg
{
public:
	unsigned char getPercentage();
};

class Rva004D38D8
{
public:
	bool rva004D38D8(float f);
};

class GameLogic;
extern GameLogic *TheGameLogic;
extern float g_Va00BC2424;
// The data ledger records VA 0x00BBB8D4 as the pooled 0.25f literal; its
// existing C alias is used here only for the target threshold value.
extern "C" const float length_estimate_factor;

class DisconnectManager
{
public:
	void processDisconnectPlayer(NetCommandMsg *msg, ConnectionManager *conMgr);
	void rva004D41B3(Int slot, ConnectionManager *conMgr);
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
	rva004D41B3(((NetProgressCommandMsg *)msg)->getPercentage(), conMgr);
	if (!((Rva004D38D8 *)this)->rva004D38D8(g_Va00BC2424)) {
		*(Int *)((char *)TheGameLogic + 0x2A4) = 1;
		return;
	}
	if (!((Rva004D38D8 *)this)->rva004D38D8(length_estimate_factor)
		&& (*(Int *)((char *)TheGameLogic + 0x2A4) != 1)) {
		*(Int *)((char *)TheGameLogic + 0x2A4) = 0;
	}
}

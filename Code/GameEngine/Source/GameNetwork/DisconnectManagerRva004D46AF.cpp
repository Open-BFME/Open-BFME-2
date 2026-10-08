// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class ConnectionManager;
class NetCommandMsg;

class DisconnectManager
{
public:
	void rva004D3CA8(void *msg, ConnectionManager *conMgr);
	void processDisconnectPlayer(NetCommandMsg *msg, ConnectionManager *conMgr);
	void rva004D3F74(NetCommandMsg *msg, ConnectionManager *conMgr);
	void rva004D3FCB(NetCommandMsg *msg, ConnectionManager *conMgr);
	void processDisconnectCommand(void *ref, ConnectionManager *conMgr);
};

// Target evidence: Ghidra boundary 0x004D46AF..0x004D46FC (77 bytes); the
// function dereferences its first argument to get a NetCommandMsg pointer,
// reads the command dword at +0x14, and calls 0x004D3CA8 / 0x004D4637 /
// 0x004D3F74 / 0x004D3FCB for command values 0x19..0x1C. Callee names for the
// last two stay address-derived; their bodies are not claimed here.
void DisconnectManager::processDisconnectCommand(void *ref, ConnectionManager *conMgr)
{
	void *msg = *(void **)ref;
	int commandType = *(int *)((char *)msg + 0x14);
	if (commandType == 0x19) {
		rva004D3CA8(msg, conMgr);
	} else if (commandType == 0x1A) {
		processDisconnectPlayer((NetCommandMsg *)msg, conMgr);
	} else if (commandType == 0x1B) {
		rva004D3F74((NetCommandMsg *)msg, conMgr);
	} else if (commandType == 0x1C) {
		rva004D3FCB((NetCommandMsg *)msg, conMgr);
	}
}

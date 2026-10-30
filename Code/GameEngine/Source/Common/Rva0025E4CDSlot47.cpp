// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva0025E406@Rva0025E4CD@@UAE?AVUnicodeString@@H@Z @0x0025E406 103B
// Slot 47 (0xBC) of vtable 0x7F6040 (Rva0025E4CD). Returns player name via rowed
// ConnectionManager::getPlayerName or TheEmptyString when manager at +0xC is null.
// Layout from dtor 0x25E4CD (base 8B pad plus manager at +0xC). Evidence: vtable slot, callers, globals.
#include "unicode_string.h"

struct NetLocalAddress
{
	unsigned int m_addr;
	unsigned int m_port;
};

enum PlayerLeaveCode
{
	PLAYERLEAVECODE_UNKNOWN = 0
};
class AsciiString;
class GameMessage;
class ConnectionManager
{
public:
	void sendChat(UnicodeString text, int playerMask);
	void sendDisconnectChat(UnicodeString text);
	void sendFile(AsciiString path, unsigned char playerMask, unsigned short commandID);
	unsigned short sendFileAnnounce(AsciiString path, unsigned char playerMask);
	void rva004D0E8B(void);
	void SetLocalAddr(const NetLocalAddress &addr)
	{
		m_localAddr = addr.m_addr;
		m_localPort = addr.m_port;
	}
	int getFileTransferProgress(int pid, AsciiString path);
	UnicodeString getPlayerName(int pid);
	void sendLocalGameMessage(GameMessage *msg); // 0x004D0E06, sendLocalGameMessage
	void rva004D0A0A(); // 0x004D0A0A
	int getNumPlayers(); // 0x004CF926
	bool rva004CF3E1(); // 0x004CF3E1
	PlayerLeaveCode processPlayerLeave(unsigned char playerID); // 0x004D1D37
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	char m_pad04[0x1204C];
private:
	unsigned int m_localAddr; // +0x12050 +0x12050
	unsigned int m_localPort; // +0x12054 +0x12054
};

class GameEngineDeletingBase
{
public:
    virtual ~GameEngineDeletingBase();
private:
    char m_pad04[8];
};

class Rva0025E4CD : public GameEngineDeletingBase
{
public:
    virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40();
    virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45();
    virtual void v46();
    virtual UnicodeString rva0025E406(int pid);
private:
    ConnectionManager *m_mgr;
};

// ?rva0025E406@Rva0025E4CD@@UAE?AVUnicodeString@@H@Z
UnicodeString Rva0025E4CD::rva0025E406(int pid)
{
    return m_mgr ? m_mgr->getPlayerName(pid) : UnicodeString::TheEmptyString;
}

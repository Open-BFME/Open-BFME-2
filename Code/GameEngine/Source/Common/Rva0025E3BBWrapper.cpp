// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0025E3BB@Rva0025E3BB@@QAEHHVAsciiString@@@Z @0x0025E3BB 75B
// Wrapper over ConnectionManager::getFileTransferProgress at +0xc.
// Evidence: calls rowed 0x004D28C6 with int plus AsciiString by value; StringBase copy 0x365F0 plus releaseBuffer 0x36410; ret 8; chain from 0x004D28C6.
#include "ascii_string.h"

struct NetLocalAddress
{
	unsigned int m_addr;
	unsigned int m_port;
};

enum PlayerLeaveCode
{
	PLAYERLEAVECODE_UNKNOWN = 0
};
class UnicodeString;
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

class Rva0025E3BB
{
public:
	int rva0025E3BB(int pid, AsciiString path);
private:
	char m_pad[0xc];
	ConnectionManager *m_mgr;
};

int Rva0025E3BB::rva0025E3BB(int pid, AsciiString path)
{
	return m_mgr->getFileTransferProgress(pid, path);
}

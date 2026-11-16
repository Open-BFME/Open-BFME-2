// BFMEConnectionManager: the BFME2 spelling of retail's connection manager object (allocated 0x121B0 bytes in 0x0025DF01).
// Field offsets come from constructor 0x004D274B's stores; names from Zero Hour's ConnectionManager, offset names otherwise.
// Each method resolves to its ledger row; offset +0 holds the vptr retail stores there, kept opaque because no slot is declared.
#ifndef CANONICAL_BFMECONNECTIONMANAGER_H
#define CANONICAL_BFMECONNECTIONMANAGER_H

class Connection;
class DisconnectManager;
class FrameDataManager;
class NetCommandList;
class NetCommandMsg;
class NetCommandWrapperList;
class Transport;

class BFMEConnectionManager
{
public:
	void attachTransport(Transport *transport);
	bool areFrameCommandsComplete(unsigned int frame, bool debugSpewage);
	void broadcastRouterFallbackPlan();
	unsigned int getNextPacketRouterSlot(unsigned int playerID);
	bool hasPacketRouterFrameStall();
	void init();
	bool isDuplicateCommand(NetCommandMsg *msg);
	bool isPacketRouter();
	bool isPlayerConnected(int slot);
	bool isPlayerInGame(int slot);
	int isPlayerSlotActive(int slot);
	void processAck(NetCommandMsg *msg);
	void processAckCommand(void *msg);
	void processGameSpyStatsAuthKeyCommand(void *command);
	void processInformPlayerLeaveFrameCommand(void *msg);
	void processRequestFrameDataCommand(void *command);
	void relayCommand(void *ref);
	void resendFrameRangeToPlayer(int playerID, unsigned int startFrame, unsigned int endFrame);
	unsigned char rva004CEF58(int firstValue);
	unsigned char rva004CEFC2(int slot, unsigned int timeout);
	void sendDisconnectFrameCommand();
	void sendFrameInfo(bool flag);
	void SendFinishedLogicFrame();
	void sendGameSpyStatsAuthKey(void *msg);
	void sendKeepAliveCommand();

protected:
	void processAckStage1(NetCommandMsg *msg);

public:
	char m_pad00000[4];
	Connection *m_connections[8];
	char m_pad00024[0x12000];
	Transport *m_transport;
	unsigned int m_localSlot;
	unsigned int m_packetRouterSlot;
	unsigned int m_packetRouterFallback[8];
	unsigned int m_12050;
	unsigned short m_12054;
	char m_pad12056[2];
	char m_pad12058[4];
	unsigned int m_1205C;
	unsigned int m_12060[8];
	int m_12080[8];
	unsigned int m_120A0[8];
	unsigned int m_120C0[8];
	unsigned int m_120E0[8];
	DisconnectManager *m_disconnectManager;
	FrameDataManager *m_frameData[8];
	NetCommandList *m_pendingCommands;
	NetCommandList *m_relayedCommands;
	NetCommandWrapperList *m_netCommandWrapperList;
	unsigned int m_12130;
	bool m_12134;
	bool m_12135;
	char m_pad12136[2];
	char m_pad12138[0x78];
};

#endif // CANONICAL_BFMECONNECTIONMANAGER_H

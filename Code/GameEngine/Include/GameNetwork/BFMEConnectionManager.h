// BFMEConnectionManager: canonical declarations for the members 9 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMECONNECTIONMANAGER_H
#define CANONICAL_BFMECONNECTIONMANAGER_H

class NetCommandMsg;
class Transport;

class BFMEConnectionManager
{
public:
	void attachTransport(Transport *transport);
	bool isDuplicateCommand(NetCommandMsg *msg);
	bool isPacketRouter();
	bool isPlayerInGame(int slot);
	int isPlayerSlotActive(int slot);
	void processAck(NetCommandMsg *msg);
	void processGameSpyStatsAuthKeyCommand(void *command);
	void processInformPlayerLeaveFrameCommand(void *msg);
	void processRequestFrameDataCommand(void *command);
	void relayCommand(void *ref);
	unsigned char rva004CEF58(int firstValue);
	void sendDisconnectFrameCommand();
	void sendFrameInfo(bool flag);
	void sendGameSpyStatsAuthKey(void *msg);
	void sendKeepAliveCommand();
};

#endif // CANONICAL_BFMECONNECTIONMANAGER_H

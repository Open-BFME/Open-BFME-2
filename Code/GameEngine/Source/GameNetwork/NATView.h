#ifndef BFME2_NAT_VIEW_H
#define BFME2_NAT_VIEW_H

// Private NAT view shared by the NAT.cpp TU and its not-yet-merged donors.
// Unknown fields keep padding; each named field cites the body that proves it.

#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
class AsciiString;

class PortNegotiationSchema
{
public:
	void handleNegotiationResult(unsigned short first, unsigned short second, int cookie, int result);
	bool isConnectionDone(unsigned short slot1, unsigned short slot2);	// 0x005DBBC1
	int getTimeToSendPing(unsigned short slot);				// 0x005DBBA5
	void *peekPing(unsigned short slot1, unsigned short slot2);		// 0x005DB98E
	bool sentAPingPacket(unsigned short slot1, unsigned short slot2);	// 0x005DBF2D
	int getActionID(unsigned short slot1, unsigned short slot2);		// 0x005DBCA6
	void playerJoin(unsigned short idx);					// 0x005DC291
	void playerLeave(unsigned short idx);
	void attachSlotList(void *slotList, unsigned short localSlot);
	bool isRetryConnectingOverLimit(unsigned short i, unsigned short j);	// 0x005DBC2E
	void reconnectPlayers(unsigned short slot1, unsigned short slot2, bool resetRetries);	// 0x005DC187
	unsigned char m_bytes[0x8E4 - 0x28];
};

// A slot's address (+0x38 in each slot of the list at NAT +0x08; also the
// pointee of NAT's +0x90C table).
struct NetPacketAddress
{
	unsigned int ip;
	unsigned short port;			// +4 (gotTargetMangledPort stores a short)
	unsigned short padding;
};

// A slot of the list at NAT +0x08: the player name at +0x30 (translated and
// compared by processGlobalMessage) and the address at +0x38.
class GameSlot
{
public:
	bool isHuman() const;			// 0x003FF0F1
	unsigned char m_pad00[0x30];
	UnicodeString m_name;			// +0x30
	unsigned char m_pad34[0x38 - 0x34];
	NetPacketAddress m_address;		// +0x38
	unsigned char m_flags40;		// +0x40 (bit 3 tested by targetNotifyMeIWasProbed)
};

class GameInfo
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12();
	virtual int getLocalSlotNum() const;	// slot 13 (+0x34)
	const unsigned int &getLocalIP() const { return m_localIP; }
	unsigned char m_pad04[0x18 - 4];
	GameSlot *m_slots[8];			// +0x18 (attachSlotList)
	unsigned int m_localIP;			// +0x38
};

class Transport;

// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva005A6732@NAT@@QBE_NXZ @0x005A6732 92B. Unlock lane: range plus
// table-null checks on m_14/m_18 via m_8, then m_94C/m_950 must be 0/4/5.
// Evidence: callers 0x005A8ABF/0x005A8F57, neighbours Rva005A6709Predicate and
// Disp8CmpBoolGetters (0x94C field), no callees. Class renamed from the
// address-derived Rva005A6732 to the ledger's NAT: the two views are the same
// retail class (this body's m_8 at +0x08, the two slot ints at +0x14/+0x18
// and the state bytes at +0x94C/+0x950 are NAT's m_slotList, m_localSlot,
// m_targetSlot and m_state94c, as the NAT views in NATProcessGlobalMessage.cpp
// and NATUpdateBfme.cpp spell them), and 27 ledger rows already name the class
// NAT, so the rowed name is this spelling's owner.
// NAT is spelled struct: the data ledger binds TheNAT as ?TheNAT@@3PAUNAT@@A.
struct NAT
{
public:
	bool rva005A6732() const;
	void setConnectionState(int a, int b, int expected, int val);
	void rva005A6C90(int val);
	void rva005A6A4C();
	void probeMangler();
	AsciiString rva005A6E7A(int state);
	void rva005A7974(unsigned short port, void *info);
	void processGlobalMessage(int slotNum, const char *options);
	void attachSlotList(GameInfo *game, int localSlot, unsigned int localIP, unsigned int arg, bool isHost);
	void targetNotifyMeIWasProbed(int slot);
	void gotTargetMangledPort(int slot, unsigned short port, int addr);
	void notifyHostMyNATCreated(int cookie);
	void StartNegotiationAction(int slot, int value);
	void sendAProbeToTarget();
	void sendPings();
	void reconnectPlayers(int slot1, int slot2, int resetRetries);
	void rva005A6CA5();
	void rva005A6D47();
	void processPlayerJoin(int idx);
	void processPlayerLeave(int idx);
protected:
	void generatePortNumbers(GameSlot **slotList, int localSlot);
private:
	int m_0;
	Transport *m_04;
	GameSlot **m_slotList;		// +0x08
	int m_hostSlot;				// +0x0C
	int m_mode;				// +0x10
	int m_localSlot;			// +0x14
	int m_targetSlot;			// +0x18
	unsigned int m_localIP;			// +0x1C
	int m_cookie;				// +0x20
	unsigned char m_24;			// +0x24
	unsigned char m_25;			// +0x25
	unsigned char m_pad26[2];
	PortNegotiationSchema m_schema;		// +0x28
	unsigned char m_hostKnown[8];		// +0x8E4
	int m_slotCookie[8];			// +0x8EC
	NetPacketAddress *m_addresses[8];	// +0x90C
	char m_pad92C[0x934 - 0x92C];
	unsigned short m_port934;		// +0x934 (probeMangler)
	unsigned short m_port936;		// +0x936
	unsigned long m_time938;		// +0x938
	char m_pad93C[0x942 - 0x93C];
	unsigned char m_942;			// +0x942
	char m_pad943[0x944 - 0x943];
	unsigned long m_addr944;		// +0x944
	char m_pad948[0x94C - 0x948];
	int m_state94c;				// +0x94C
	int m_950;				// +0x950
	char m_pad954[0x958 - 0x954];
	unsigned short m_startingPortNumber;	// +0x958
	char m_pad95A[0x968 - 0x95A];
	unsigned int m_timeoutTime;		// +0x968
	char m_pad96C[0x970 - 0x96C];
	unsigned char m_970;			// +0x970
};

// The readiness gate 0x005A6709 is rowed as int Rva005A6709::rva005A6709()
// const (Rva005A6709Predicate.cpp); its callers test al, so they keep the
// bool call shape through a member-pointer cast (as Rva005A6903Box.cpp does).
class Rva005A6709
{
public:
	int rva005A6709() const;
};

typedef bool (Rva005A6709::*Rva005A6709BoolShape)() const;
#define NAT_READY(p) ((((Rva005A6709 *)(p))->*reinterpret_cast<Rva005A6709BoolShape>(&Rva005A6709::rva005A6709))())

#endif

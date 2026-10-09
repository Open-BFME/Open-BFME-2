// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /EHsc /MD
//
// NAT::processGlobalMessage, retail 0x005A8ABF (1176B, ret 8). WorldBuilder's
// debug build names it (NAT.cpp); Zero Hour's NAT::processGlobalMessage is the
// donor for the whitespace skip and the strncmp/sscanf dispatch over PROBED,
// CONNDONE, CONNFAILED and PORT. BFME 2 adds NATHOST and NATINITED (slot,
// cookie and the sender's name checked against the slot's translated name),
// NEGO, carries the session cookie (+0x20) in every message, attaches the slot
// list from TheGameSpyGame on the first NATHOST and reports CONNDONE /
// CONNFAILED to the port-negotiation schema at +0x28.
// Target evidence: the native body (formats "%d %d %s", "%d %d %X", "%d %X",
// "%d %d %08X %X"), the rowed NAT callees and the slot list layout shared with
// NATSendNegotiationRequests.cpp. 0x005A7829 / 0x005A89C2 / 0x005A6732 are
// address-named NAT members.
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

class GameInfo
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12();
	virtual Int getLocalSlotNum() const;	// slot 13 (+0x34)
	const UnsignedInt &getLocalIP() const { return m_localIP; }
	unsigned char m_pad04[0x38 - 4];
	UnsignedInt m_localIP;			// +0x38
};

class GameSpyStagingRoom : public GameInfo
{
};
extern GameSpyStagingRoom *TheGameSpyGame;

struct NATSlotView
{
	unsigned char m_pad00[0x30];
	UnicodeString m_name;			// +0x30
	unsigned char m_pad34[4];
	UnsignedInt m_ip;			// +0x38
};

struct NATAddressView
{
	UnsignedInt m_ip;
};

class Rva005DC3C1
{
public:
	void rva005DC3C1(UnsignedShort first, UnsignedShort second, Int cookie, Int result);
	unsigned char m_bytes[0x8E4 - 0x28];
};

struct NAT
{
	Int m_0;
	void *m_04;
	NATSlotView **m_slotList;		// +0x08
	Int m_hostSlot;				// +0x0C
	Int m_mode;				// +0x10
	Int m_localSlot;			// +0x14
	Int m_targetSlot;			// +0x18
	Int m_1c;
	Int m_cookie;				// +0x20
	Int m_24;
	Rva005DC3C1 m_schema;			// +0x28
	unsigned char m_hostKnown[8];		// +0x8E4
	Int m_slotCookie[8];			// +0x8EC
	NATAddressView *m_addresses[8];		// +0x90C
	unsigned char m_pad92c[0x94C - 0x92C];
	Int m_state94c;				// +0x94C

	void processGlobalMessage(Int slotNum, const char *options);
	void attachSlotList(GameInfo *game, Int localSlot, UnsignedInt localIP, UnsignedInt arg, Bool isHost);
	void setConnectionState(Int a, Int b, Int c, Int state);
	void rva005A6C90(Int state);
	void targetNotifyMeIWasProbed(Int slot);
	void gotTargetMangledPort(Int slot, UnsignedShort port, Int addr);
	Bool rva005A6732() const;
	void rva005A7829(Int cookie);
	void rva005A89C2(Int slot, Int value);
};
extern NAT *TheNAT;

void NAT::processGlobalMessage(Int slotNum, const char *options)
{
	const char *ptr = options;
	while (isspace(*ptr))
		++ptr;

	if (!strncmp(ptr, "NATHOST", strlen("NATHOST")))
	{
		if (TheGameSpyGame->getLocalSlotNum() < 0)
			return;
		if (m_slotList == 0)
			TheNAT->attachSlotList(TheGameSpyGame, TheGameSpyGame->getLocalSlotNum(), TheGameSpyGame->getLocalIP(), 0,
				TheGameSpyGame->getLocalSlotNum() == 0);
		char name[200];
		name[0] = 0;
		UnsignedInt slot;
		Int cookie;
		const char *c = ptr + strlen("NATHOST");
		sscanf(c, "%d %d %s", &slot, &cookie, name);
		if (slot >= 8 || m_slotList == 0 || m_slotList[slot] == 0)
			return;
		NATSlotView *local = m_slotList[m_localSlot];
		if (local == 0 || local->m_ip == 0)
			return;
		AsciiString hostName;
		hostName.translate(m_slotList[slot]->m_name);
		if (hostName.compare(name) == 0)
		{
			m_hostSlot = (UnsignedShort)slot;
			m_hostKnown[m_hostSlot] = 1;
			rva005A7829(cookie);
			m_addresses[m_localSlot]->m_ip = m_slotList[m_localSlot]->m_ip;
		}
	}
	else if (!strncmp(ptr, "NATINITED", strlen("NATINITED")))
	{
		char name[200];
		name[0] = 0;
		UnsignedInt slot;
		Int cookie;
		const char *c = ptr + strlen("NATINITED");
		sscanf(c, "%d %d %s", &slot, &cookie, name);
		if (slot >= 8 || m_slotList == 0 || m_slotList[slot] == 0 || m_slotCookie[slot] != cookie)
			return;
		AsciiString senderName;
		senderName.translate(m_slotList[slot]->m_name);
		if (senderName.compare(name) == 0)
			m_hostKnown[slot] = 1;
	}
	else if (!strncmp(ptr, "NEGO", strlen("NEGO")))
	{
		Int first, second, value;
		const char *c = ptr + strlen("NEGO");
		sscanf(c, "%d %d %X", &first, &second, &value);
		Int local = m_localSlot;
		if ((first == local || second == local) && !rva005A6732())
			m_state94c = 5;
		Int other = second;
		if (first != local)
			other = first;
		rva005A89C2(other, value);
	}
	else if (!strncmp(ptr, "PROBED", strlen("PROBED")))
	{
		Int slot, cookie;
		sscanf(ptr + strlen("PROBED"), "%d %X", &slot, &cookie);
		if (cookie == m_cookie && slot == m_targetSlot)
			targetNotifyMeIWasProbed(slot);
	}
	else if (!strncmp(ptr, "PORT", strlen("PORT")))
	{
		const char *c = ptr + strlen("PORT");
		Int slot;
		Int intport = 0;
		Int addr = 0;
		Int cookie = 0;
		sscanf(c, "%d %d %08X %X", &slot, &intport, &addr, &cookie);
		UnsignedShort port = (UnsignedShort)intport;
		if (slot < 0 || slot >= 8 || m_cookie != cookie)
			return;
		if (port < 1024)
			port += 1024;
		gotTargetMangledPort(slot, port, addr);
	}
	else if (!strncmp(ptr, "CONNDONE", strlen("CONNDONE")))
	{
		Int first, second, cookie;
		const char *c = ptr + strlen("CONNDONE");
		sscanf(c, "%d %d %X", &first, &second, &cookie);
		if (first == m_localSlot && second == m_targetSlot && cookie == m_cookie)
			rva005A6C90(4);
		m_schema.rva005DC3C1(first, second, cookie, 3);
	}
	else if (!strncmp(ptr, "CONNFAILED", strlen("CONNFAILED")))
	{
		Int first, second, cookie;
		const char *c = ptr + strlen("CONNFAILED");
		sscanf(c, "%d %d %X", &first, &second, &cookie);
		if (first == m_targetSlot && second == m_localSlot && cookie == m_cookie)
			setConnectionState(first, second, cookie, 5);
		m_schema.rva005DC3C1(first, second, cookie, 4);
	}
}

// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Retail 0x0044B7A9, 364 bytes. The body trims the by-value name, updates
// LANAPI state, emits a type-2 lobby message, and updates the local LANPlayer.
// Target field offsets and virtual slots below come from this retail body;
// the operation's purpose and player update sequence follow BFME1's
// LANAPI::RequestSetName and LANAPI::handleLobbyAnnounce.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef unsigned char UnsignedByte;
typedef bool Bool;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

#include "ascii_string.h"


#include "unicode_string.h"

struct BfmeNetAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

class LANPlayer
{
public:
	LANPlayer() : m_lastHeard(0), m_next(0)
	{
		m_address.ip = 0;
		m_address.port = 0;
	}

	UnicodeString m_name;
	UnicodeString m_login;
	UnicodeString m_host;
	UnsignedInt m_lastHeard;
	LANPlayer *m_next;
	BfmeNetAddress m_address;
};

struct LANMessage
{
	UnsignedInt type;
	UnsignedByte m_remainder[0x1D8 - sizeof(UnsignedInt)];
};

class LANAPI
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void RequestSetName(UnicodeString newName);	// slot 24
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot41(void) = 0;
	virtual void slot42(void) = 0;
	virtual void slot43(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot45(void) = 0;
	virtual void slot46(void) = 0;
	virtual void slot47(void) = 0;
	virtual void OnNameChange(BfmeNetAddress *from, UnicodeString newName);	// slot 48
	virtual void slot49(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot51(void) = 0;
	virtual void slot52(void) = 0;
	virtual void slot53(void) = 0;
	virtual void slot54(void) = 0;
	virtual void slot55(void) = 0;
	virtual void slot56(void) = 0;
	virtual void fillInLANMessage(LANMessage *message);	// slot 57
	virtual void slot58(void) = 0;
	virtual void slot59(void) = 0;
	virtual void slot60(void) = 0;
	virtual void slot61(void) = 0;
	virtual void slot62(void) = 0;
	virtual LANPlayer *LookupPlayer(const BfmeNetAddress *address);	// slot 63
	virtual BfmeNetAddress *getLocalAddress(void);	// slot 64

	void Rva004495A2(LANMessage *message, UnsignedInt address);

protected:
	void addPlayer(LANPlayer *player);
	void removePlayer(LANPlayer *player);
	UnsignedByte m_beforeName[0x14 - 4];
	UnicodeString m_name;		// +0x14
	AsciiString m_userName;		// +0x18
	AsciiString m_hostName;		// +0x1C
	UnsignedByte m_beforePendingAction[0x28 - 0x20];
	UnsignedInt m_pendingAction;	// +0x28
	UnsignedByte m_beforeResendTime[0x3C - 0x2C];
	UnsignedInt m_lastResendTime;	// +0x3C
	UnsignedByte m_beforeLobby[0x41 - 0x40];
	Bool m_inLobby;			// +0x41
};

typedef char PlayerSizeCheck[sizeof(LANPlayer) == 0x1C ? 1 : -1];
typedef char MessageSizeCheck[sizeof(LANMessage) == 0x1D8 ? 1 : -1];

void LANAPI::RequestSetName(UnicodeString newName)
{
	newName.trim();
	if (m_pendingAction != 0)
	{
		OnNameChange(getLocalAddress(), newName);
		return;
	}

	m_lastResendTime = timeGetTime();

	if (m_inLobby && m_pendingAction == 0)
	{
		m_name.set(newName);

		LANMessage message;
		fillInLANMessage(&message);
		message.type = 2;
		Rva004495A2(&message, 0);

		LANPlayer *player = LookupPlayer(getLocalAddress());
		if (!player)
		{
			player = new LANPlayer;
			player->m_address = *getLocalAddress();
		}
		else
		{
			removePlayer(player);
		}

		player->m_name.set(m_name);
		player->m_host.translate(m_hostName);
		player->m_login.translate(m_userName);
		player->m_lastHeard = timeGetTime();

		addPlayer(player);
		OnNameChange(&player->m_address, player->m_name);
	}
}

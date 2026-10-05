// ?rva0024A0C7@LANAPI@@UAEXVUnicodeString@@@Z
// partial score=0.99 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Retail 0x0024A0C7, 177 bytes. LANAPI vtable slot 37 (vtable 0x0083E680,
// class of ??1LANAPI@@UAE@XZ).
// ?rva0024A0C7@LANAPI@@UAEXVUnicodeString@@@Z
// Honest address name: __thiscall (ret 4: by-value UnicodeString, destroyed
// in the EH epilogue via rowed releaseBuffer). Guards on m_inLobby +0x41 and
// current-game holder +0x44 (null and flag byte +0x11); when m_name +0x14
// matches the argument via rowed StringBase compare, dispatches on globals
// g_Va00A03354/g_Va00A01E48 to rowed Shell 0x35BEC7 (plus g_00E03364=1) or
// rowed GameEngine 0x444E8A; else validates holder+0x114 against virtual
// slot64 via rowed Rva00248CBF, clears +0x3C, calls rowed Rva00248D84Enable,
// then virtual slot26(1, zero address). Layout follows
// LANAPICompleteDestructor and slot35 Rva002493BC.
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#include "ascii_string.h"
#include "unicode_string.h"

struct BfmeNetAddress
{
	UnsignedInt ip;
	UnsignedShort port;
	Bool Rva00248CBF(const BfmeNetAddress *other) const;
};

struct Outer00446A77;
struct GlobalA01E48;
extern Outer00446A77 *g_Va00A03354;
extern GlobalA01E48 *g_Va00A01E48;
extern UnsignedByte g_00E03364;

class Shell
{
public:
	void rva0035BEC7();
};

class GameEngine
{
public:
	void rva00444E8A();
};

void Rva00248D84Enable();

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface(void);

private:
	UnsignedByte m_baseFields[8];
};

class LANAPIInterface : public SubsystemInterface
{
public:
	virtual ~LANAPIInterface(void) {}
};

class Transport
{
public:
	~Transport(void);
};

struct LANMessage
{
	UnsignedInt type;
	UnsignedByte payload[0x1D8 - sizeof(UnsignedInt)];
};

class LANPlayer;

class LANGameInfo
{
public:
	char _00[0x11];
	UnsignedByte m_11;
	char _12[0x114 - 0x12];
	BfmeNetAddress m_address;
};

class LANAPI : public LANAPIInterface
{
public:
	virtual ~LANAPI(void);
	virtual void reset(void);
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
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(int code, BfmeNetAddress *query) = 0;
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
	virtual void rva0024A0C7(UnicodeString arg);
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
	virtual void slot48(void) = 0;
	virtual void slot49(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot51(void) = 0;
	virtual void slot52(void) = 0;
	virtual void slot53(void) = 0;
	virtual void slot54(void) = 0;
	virtual void slot55(void) = 0;
	virtual void slot56(void) = 0;
	virtual void slot57(void) = 0;
	virtual void slot58(void) = 0;
	virtual void slot59(void) = 0;
	virtual void slot60(void) = 0;
	virtual void slot61(void) = 0;
	virtual void slot62(void) = 0;
	virtual void slot63(void) = 0;
	virtual BfmeNetAddress *slot64(void) = 0;

protected:
	LANPlayer *m_lobbyPlayers;
	LANGameInfo *m_games;
	UnicodeString m_name;
	AsciiString m_userName;
	AsciiString m_hostName;
	UnsignedByte m_beforePending[0x28 - 0x20];
	UnsignedInt m_pendingAction;
	UnsignedInt m_expiration;
	UnsignedByte m_beforeDirectConnect[0x34 - 0x30];
	BfmeNetAddress m_directConnectAddress;
	UnsignedInt m_resend;
	Bool m_isInLANMenu;
	Bool m_inLobby;
	UnsignedByte m_beforeCurrentGame[0x44 - 0x42];
	LANGameInfo *m_currentGame;
	UnsignedByte m_beforeTransport[0x50 - 0x48];
	Transport *m_transport;
};

// ?rva0024A0C7@LANAPI@@UAEXVUnicodeString@@@Z present-unmatched
void LANAPI::rva0024A0C7(UnicodeString arg)
{
	LANGameInfo *game = m_currentGame;
	if (m_inLobby || game == 0 || game->m_11 != 0)
		goto done;
	if (m_name.compare(arg) == 0)
	{
		if (g_Va00A03354 == 0)
		{
			((Shell *)g_Va00A01E48)->rva0035BEC7();
			g_00E03364 = 1;
		}
		else
			((GameEngine *)g_Va00A03354)->rva00444E8A();
		goto done;
	}
	BfmeNetAddress *base = &game->m_address;
	if (!base->Rva00248CBF(slot64()))
		goto done;
	m_resend = 0;
	Rva00248D84Enable();
	BfmeNetAddress query;
	query.ip = 0;
	query.port = 0;
	slot26(1, &query);
done:;
}

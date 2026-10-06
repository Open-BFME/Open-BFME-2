// ?rva00582EB0@LANAPI@@QAEXPAULANMessage@@PBUBfmeNetAddress@@_N@Z
// partial score=0.99 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
//
// ?rva00582EB0@LANAPI@@QAEXPAULANMessage@@PBUBfmeNetAddress@@_N@Z
// Retail 0x00582EB0, 273 bytes. The target reads LANAPI fields at +0x41/+0x44;
// its caller invokes this on the same LANAPI object as two matched handlers.
// Keep the address-based name: donor semantics are not established.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef int Int;
typedef bool Bool;

#include "ascii_string.h"
#include "unicode_string.h"

struct BfmeNetAddress
{
	UnsignedInt ip;
	UnsignedShort port;
	Bool Rva00248CBF(const BfmeNetAddress *other) const;
};

struct LANMessage
{
	Int type;
	UnsignedByte payload[0x1D8 - sizeof(Int)];
};

class LANGameInfo
{
public:
	virtual void *slot00(Bool deleteStorage) = 0;
	Bool inProgress(void) const { return m_inProgress; }
	const BfmeNetAddress *getAddress(void) const { return &m_address; }

private:
	UnsignedByte m_beforeInProgress[0x11 - 4];
	Bool m_inProgress;
	UnsignedByte m_beforeAddress[0x114 - 0x12];
	BfmeNetAddress m_address;
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
	virtual void slot24(void) = 0;
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
	virtual void slot37(UnicodeString value) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot41(void) = 0;
	virtual void slot42(void) = 0;
	virtual void slot43(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot45(void) = 0;
	virtual UnsignedByte slot46(const BfmeNetAddress *address, Bool flag, const void *payload, UnsignedInt size) = 0;
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
	virtual void slot61(Bool active) = 0;

	void rva00582EB0(LANMessage *message, const BfmeNetAddress *address, Bool flag);

protected:
	void removeGame(LANGameInfo *game);

private:
	UnsignedByte m_beforeName[0x14 - 4];
	UnicodeString m_name;
	UnsignedByte m_beforeLobby[0x41 - 0x18];
	Bool m_inLobby;
	UnsignedByte m_beforeCurrentGame[0x44 - 0x42];
	LANGameInfo *m_currentGame;
};

extern AsciiString __cdecl GenerateGameOptionsString(void);
void __cdecl operator delete(void *memory);

void LANAPI::rva00582EB0(LANMessage *message, const BfmeNetAddress *address, Bool flag)
{
	if (m_inLobby)
		return;

	LANGameInfo *game = m_currentGame;
	if (!game || !game->getAddress()->Rva00248CBF(address) || game->inProgress())
		return;

	AsciiString gameOptions = GenerateGameOptionsString();
	UnsignedByte no = 0;
	UnsignedByte reply = slot46(address, no, message->payload + 0x1A, 0x186);
	if (reply != no)
	{
		{
			AsciiString receivedOptions = GenerateGameOptionsString();
			gameOptions.compare(receivedOptions);
		}
		slot61(false);
		if (flag)
		{
			slot43();
		}
		else
			slot42();
		return;
	}

	slot37(m_name);
	removeGame(m_currentGame);
	LANGameInfo *gameToDelete = m_currentGame;
	void *memory = gameToDelete ? gameToDelete->slot00(false) : 0;
	::operator delete(memory);
	m_currentGame = 0;
	m_inLobby = true;
}

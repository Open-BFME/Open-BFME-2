// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ConnectionManager::processChat, retail 0x004D10F1, 449 bytes.
//
// Reference: Zero Hour GameEngine/Source/GameNetwork/ConnectionManager.cpp
// processChat (name, the "[name] text" line, the sender Player lookup by name
// key, the plain message when there is none, and the coloured message for a
// recipient who can see the chat). It directly follows processDisconnectChat
// 0x004D1023, which formats the same line the same way.
// BFME 2 differences read from this body: the name comes from getPlayerName
// 0x004D0198 rather than the connection's user; the body returns early for a
// sender slot of 8 or more; the Player's name key is the AsciiString at
// GameSlot +0x34 (Zero Hour formatted "player%d"); there is no observer test,
// only the slot's mute flag at +0x0A; both branches first call the chat
// notification sound 0x004CF145; and the coloured branch also adds the line to
// the chat history through 0x00381C82 with the Player's colour (+0x280).
// InGameUI::message and messageColor are the varargs virtuals at +0x4C/+0x44.

#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva004D6119
{
public:
	UnicodeString rva004D6119() const;
};

// Text at +0x1C (read through the ledger's Rva004D6119 getter) and the
// recipient mask at +0x20 (the folded +0x20 getter 0x0030D377, held in the
// ledger as NetWrapperCommandMsg::getDataLength).
class NetChatCommandMsg : public Rva004D6119
{
public:
	Int getPlayerID() const { return m_playerID; }

private:
	void *m_vptr;
	Int m_timestamp;
	Int m_executionFrame;
	Int m_playerID;
};

class NetWrapperCommandMsg
{
public:
	unsigned int getDataLength();
};

class GameSlot
{
public:
	Bool isMuted() const { return m_isMuted; }
	const AsciiString &getPlayerNameKey() const { return m_playerNameKey; }

private:
	char m_pad00[0x0a];
	Bool m_isMuted;
	char m_pad0B[0x34 - 0x0b];
	AsciiString m_playerNameKey;
};

class GameInfo
{
public:
	GameSlot *getSlot(Int index);
	const GameSlot *getConstSlot(Int index) const;
};

#include "../../Include/Common/NameKeyGenerator.h"

class Player
{
public:
	__declspec(dllimport) __forceinline Int getPlayerColor() const { return m_color; }

private:
	char m_pad000[0x280];
	Int m_color;
};

#include "../../Include/Common/PlayerList.h"

#include "../../../Libraries/Include/Lib/RGBColor.h"

#include "../../Include/GameClient/InGameUI.h"

extern GameInfo *TheGameInfo;
extern NameKeyGenerator *TheNameKeyGenerator;
extern PlayerList *ThePlayerList;
extern InGameUI *TheInGameUI;

void Rva004CF145();
void Rva00381C82AddChatText(Int type, const UnicodeString &text, Int color);

#include "../../Include/GameNetwork/ConnectionManager.h"

void ConnectionManager::processChat(NetChatCommandMsg *msg)
{
	UnicodeString unitext;
	unitext.format(L"[%ls] %ls", getPlayerName(msg->getPlayerID()).str(), msg->rva004D6119().str());

	if ((unsigned int)msg->getPlayerID() >= 8)
		return;

	AsciiString playerName = TheGameInfo->getSlot(msg->getPlayerID())->getPlayerNameKey();
	const Player *player = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(playerName));
	if (!player)
	{
		Rva004CF145();
		TheInGameUI->message(UnicodeString(L"%ls"), unitext.str());
		return;
	}

	Bool canSeeChat = !TheGameInfo->getConstSlot(msg->getPlayerID())->isMuted();
	if (((1 << m_localSlot) & ((NetWrapperCommandMsg *)msg)->getDataLength()) && canSeeChat)
	{
		Rva004CF145();
		RGBColor rgb;
		rgb.setFromInt(player->getPlayerColor());
		TheInGameUI->messageColor(&rgb, UnicodeString(L"%ls"), unitext.str());
		Rva00381C82AddChatText(1, unitext, player->getPlayerColor());
	}
}

// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BFME2's in-game chat screen (InGameChat.apt, built by the 0x288-byte
// factory at 0x002D1F3D): its constructor, which becomes the open chat
// screen and binds its callbacks by name (InitGadgets, OnInitialized and
// OnClosed are in AptLobbyScreenInitCallbacks.cpp), the opener that picks
// the receiver type, the slash-command filter and the Send command. BFME
// 1's AptScreenFactories.cpp (BfmeAptScreenInGameChat) is the donor.

#include "ascii_string.h"
#include "unicode_string.h"

extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);

class GameWindow
{
protected:
	virtual ~GameWindow();

private:
	unsigned char m_pad004[0x218 - 4];
};

// The Apt callback functors (Rva0057BC63FunctorHolder.cpp, as in
// AptScoreScreenCallbacks.cpp).
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	FunctorBinding(FunctorMethod method, FunctorTarget *target) : m_target(target), m_method(method) {}

	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

class FunctorWrapperHead
{
public:
	void *m_vtbl;
	int m_refCount; // +0x04
};

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}

	FunctorWrapperHead *m_ptr;
};

__forceinline FunctorBinding MakeBinding(FunctorMethod method, FunctorTarget *target)
{
	FunctorBinding binding(method, target);
	return binding;
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(const FunctorBinding &binding) : Rva0057BC63FunctorHolder(binding) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

class AptCommandMap;
class AptExternHandler;

class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

private:
	unsigned char m_names[12]; // an STLport vector<AsciiString>
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);

private:
	unsigned char m_names[12]; // an STLport vector<AsciiString>
};

class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

// The Apt screen base (BfmeAptGameWindowDestructor.cpp): a 0x218-byte
// GameWindow and, at +0x218, the 0x58-byte callback registry.
class Rva005248D0
{
public:
	virtual ~Rva005248D0();

	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10

private:
	unsigned char m_pad01C[0x58 - 0x1C];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();

private:
	AsciiString m_filename; // +0x270
	int m_274;
	char m_278;
};

// The Apt window manager (VA 0x00DFE4CC).
class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool placeholder);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class GameWindow;
UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);
void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);

// Runs a console command line.
void Rva00060820(const char *command);

class GameMessage
{
public:
	void appendIntegerArgument(int value);
};

class MessageStream
{
public:
#define STREAM_SLOT(N) virtual void slot##N();
	STREAM_SLOT(00) STREAM_SLOT(01) STREAM_SLOT(02) STREAM_SLOT(03) STREAM_SLOT(04) STREAM_SLOT(05)
	STREAM_SLOT(06) STREAM_SLOT(07) STREAM_SLOT(08) STREAM_SLOT(09) STREAM_SLOT(10) STREAM_SLOT(11)
	STREAM_SLOT(12) STREAM_SLOT(13) STREAM_SLOT(14) STREAM_SLOT(15) STREAM_SLOT(16) STREAM_SLOT(17)
#undef STREAM_SLOT
	virtual GameMessage *appendMessage(int type);
};

extern MessageStream *MessageStreamSubsystem;

class LanguageFilter
{
public:
	void filterLine(UnicodeString &line);
};

extern LanguageFilter *TheLanguageFilter;

class NetworkInterface
{
public:
#define NET_SLOT(N) virtual void slot##N();
	NET_SLOT(00) NET_SLOT(01) NET_SLOT(02) NET_SLOT(03) NET_SLOT(04) NET_SLOT(05) NET_SLOT(06)
	NET_SLOT(07) NET_SLOT(08) NET_SLOT(09) NET_SLOT(10) NET_SLOT(11) NET_SLOT(12) NET_SLOT(13)
	NET_SLOT(14) NET_SLOT(15) NET_SLOT(16) NET_SLOT(17) NET_SLOT(18) NET_SLOT(19) NET_SLOT(20)
	NET_SLOT(21) NET_SLOT(22) NET_SLOT(23) NET_SLOT(24) NET_SLOT(25)
#undef NET_SLOT
	virtual void sendChat(UnicodeString text, int playerMask);
};

extern NetworkInterface *TheNetwork;

// The open in-game chat screen (VA 0x00E04478).
extern int g_Va00E04478;

// Rva004E8220Method.cpp's view of this screen: Close, bound by its name,
// moves the +0x27C state from 1 to 2.
class Rva004E8220
{
public:
	void rva004E8220(int unused);
};

class AptInGameChat : public _bfme_AptGameWindow
{
public:
	AptInGameChat(void *context);
	virtual ~AptInGameChat();

	// AptLobbyScreenInitCallbacks.cpp.
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void OnInitialized(const char *unused);
	void rva004E8213(const char *unused);
	void Send(const char *unused);
	bool rva004E8670(UnicodeString text);

private:
	int m_state; // +0x27C
	int m_chatType; // +0x280
	GameWindow *m_entry; // +0x284

	friend void rva004E8258(int chatType);
};

// Retail 0x004E8B38, 518 bytes: the screen's constructor. The first one
// becomes the open chat screen and binds InitGadgets as its screen
// reference and the OnInitialized, OnClosed, Close and Send commands.
#pragma pointers_to_members(full_generality, multiple_inheritance)
AptInGameChat::AptInGameChat(void *context)
	: _bfme_AptGameWindow(context),
	  m_state(0),
	  m_entry(0)
{
	if (g_Va00E04478 != 0)
		return;
	g_Va00E04478 = (int)this;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptInGameChat::InitGadgets);
		AsciiString screen("AptInGameChat::InitGadgets");
		_bfme_setAptScreenRef(screen, AptRef<AptScreenInitGadgets>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptInGameChat::OnInitialized);
		AsciiString name("AptInGameChat::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptInGameChat::rva004E8213);
		AsciiString name("AptInGameChat::OnClosed");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva004E8220::rva004E8220);
		AsciiString name("AptInGameChat::Close");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptInGameChat::Send);
		AsciiString name("AptInGameChat::Send");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
}

// TheGameLogic (0x00DFE78C): the game mode at +0x110 (3 is a replay) and a
// pointer at +0x120 that blocks the chat while set.
class GameLogic
{
public:
	unsigned char m_pad000[0x110];
	int m_gameMode; // +0x110
	unsigned char m_pad114[0x120 - 0x114];
	void *m_120; // +0x120
};

extern GameLogic *TheGameLogic;

// TheInGameUI (0x00DFEDF0): vslot 95 reports the quit menu up.
class InGameUI
{
public:
#define UI_SLOT(N) virtual void slot##N();
	UI_SLOT(00) UI_SLOT(01) UI_SLOT(02) UI_SLOT(03) UI_SLOT(04) UI_SLOT(05) UI_SLOT(06) UI_SLOT(07)
	UI_SLOT(08) UI_SLOT(09) UI_SLOT(10) UI_SLOT(11) UI_SLOT(12) UI_SLOT(13) UI_SLOT(14) UI_SLOT(15)
	UI_SLOT(16) UI_SLOT(17) UI_SLOT(18) UI_SLOT(19) UI_SLOT(20) UI_SLOT(21) UI_SLOT(22) UI_SLOT(23)
	UI_SLOT(24) UI_SLOT(25) UI_SLOT(26) UI_SLOT(27) UI_SLOT(28) UI_SLOT(29) UI_SLOT(30) UI_SLOT(31)
	UI_SLOT(32) UI_SLOT(33) UI_SLOT(34) UI_SLOT(35) UI_SLOT(36) UI_SLOT(37) UI_SLOT(38) UI_SLOT(39)
	UI_SLOT(40) UI_SLOT(41) UI_SLOT(42) UI_SLOT(43) UI_SLOT(44) UI_SLOT(45) UI_SLOT(46) UI_SLOT(47)
	UI_SLOT(48) UI_SLOT(49) UI_SLOT(50) UI_SLOT(51) UI_SLOT(52) UI_SLOT(53) UI_SLOT(54) UI_SLOT(55)
	UI_SLOT(56) UI_SLOT(57) UI_SLOT(58) UI_SLOT(59) UI_SLOT(60) UI_SLOT(61) UI_SLOT(62) UI_SLOT(63)
	UI_SLOT(64) UI_SLOT(65) UI_SLOT(66) UI_SLOT(67) UI_SLOT(68) UI_SLOT(69) UI_SLOT(70) UI_SLOT(71)
	UI_SLOT(72) UI_SLOT(73) UI_SLOT(74) UI_SLOT(75) UI_SLOT(76) UI_SLOT(77) UI_SLOT(78) UI_SLOT(79)
	UI_SLOT(80) UI_SLOT(81) UI_SLOT(82) UI_SLOT(83) UI_SLOT(84) UI_SLOT(85) UI_SLOT(86) UI_SLOT(87)
	UI_SLOT(88) UI_SLOT(89) UI_SLOT(90) UI_SLOT(91) UI_SLOT(92) UI_SLOT(93) UI_SLOT(94)
#undef UI_SLOT
	virtual bool isQuitMenuVisible();
};

extern InGameUI *TheInGameUI;

// The disconnect menu (VA 0x00E048D0).
extern int g_Va00E048D0;

// TheGameInfo (0x00E02EEC): vslot 19 lets a chat other than the console
// open while TheWritableGlobalData's +0xA44 flag is set.
class GameSlot
{
public:
	unsigned char m_pad000[0xA];
	bool m_0A; // +0x0A
	unsigned char m_pad00B[0x34 - 0xB];
	AsciiString m_playerName; // +0x34
};

class GameInfo
{
public:
	int getSlotNum(AsciiString name) const;
	GameSlot *getSlot(int index);
	const GameSlot *getConstSlot(int index) const;

#define INFO_SLOT(N) virtual void slot##N();
	INFO_SLOT(00) INFO_SLOT(01) INFO_SLOT(02) INFO_SLOT(03) INFO_SLOT(04) INFO_SLOT(05) INFO_SLOT(06)
	INFO_SLOT(07) INFO_SLOT(08) INFO_SLOT(09) INFO_SLOT(10) INFO_SLOT(11) INFO_SLOT(12) INFO_SLOT(13)
	INFO_SLOT(14) INFO_SLOT(15) INFO_SLOT(16) INFO_SLOT(17) INFO_SLOT(18)
#undef INFO_SLOT
	virtual bool slot19();
};

extern GameInfo *TheGameInfo;

class GlobalData
{
public:
	unsigned char m_pad000[0xA44];
	int m_A44; // +0xA44
};

extern GlobalData *TheWritableGlobalData;

// What TheWindowManager's slot 32 makes of an Apt file (as in
// Rva00511730Save.cpp); slot 0 is run on it with 0.
class Rva005116C2Screen
{
public:
	virtual void v00(int value) = 0;
};

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
#undef V
	virtual Rva005116C2Screen *v32(AsciiString filename) = 0;
};

extern GameWindowManager *TheWindowManager;

class Team;

enum Relationship
{
	ENEMIES,
	NEUTRAL,
	ALLIES
};

class Player
{
public:
	bool isPlayerActive() const;
	Relationship getRelationship(const Team *team) const;

	unsigned char m_pad000[0x54];
	int m_playerIndex; // +0x54
	unsigned char m_pad058[0x2EC - 0x58];
	Team *m_defaultTeam; // +0x2EC
};

enum NameKeyType
{
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);

	unsigned char m_pad000[0x10];
	Player *m_local; // +0x10
};

extern PlayerList *ThePlayerList;

class GameTextInterface
{
public:
#define TEXT_SLOT(N) virtual void slot##N();
	TEXT_SLOT(00) TEXT_SLOT(01) TEXT_SLOT(02) TEXT_SLOT(03) TEXT_SLOT(04) TEXT_SLOT(05) TEXT_SLOT(06)
	TEXT_SLOT(07) TEXT_SLOT(08) TEXT_SLOT(09) TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13)
#undef TEXT_SLOT
	// Overloaded virtuals are laid out in reverse declaration order: the
	// AsciiString fetch is vslot 14, the char one vslot 15.
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
	virtual void slot16();
	// The localized format string itself.
	virtual const UnicodeString *slot17(const char *label, bool *exists);
};

extern GameTextInterface *TheGameText;

// Retail 0x004E8258, 403 bytes: opens the chat screen for a receiver type
// (0 allies, 1 everyone, 2 players, 3 the console, 4 observers) unless in a
// replay, under the quit or disconnect menu, while TheGameLogic's +0x120 is
// set or, except for the console, while TheWritableGlobalData's +0xA44 is
// set and TheGameInfo's vslot 19 refuses; the open screen keeps the type
// at +0x280 and "APT:InGameChatReceivers" names it. BFME 1's
// Rva00511CC0InGameChat.cpp is the donor.
void rva004E8258(int chatType)
{
	if (TheGameLogic->m_gameMode == 3)
		return;
	if (TheInGameUI->isQuitMenuVisible())
		return;
	if (g_Va00E048D0 != 0)
		return;
	if (TheGameLogic != 0 && TheGameLogic->m_120 != 0)
		return;
	if (chatType != 3)
	{
		if (!TheGameInfo->slot19() && TheWritableGlobalData->m_A44 != 0)
			return;
	}
	if (g_Va00E04478 != 0)
		return;
	TheWindowManager->v32(AsciiString("InGameChat.apt"))->v00(0);
	AptInGameChat *chat = (AptInGameChat *)g_Va00E04478;
	if (chat == 0)
		return;
	chat->m_chatType = chatType;
	AsciiString label;
	if (chatType == 1)
	{
		if (ThePlayerList->m_local->isPlayerActive())
			label = "Chat:Everyone";
		else
			label = "Chat:Observers";
	}
	else if (chatType == 4)
		label = "Chat:Observers";
	else if (chatType == 0)
		label = "Chat:Allies";
	else if (chatType == 2)
		label = "Chat:Players";
	else if (chatType == 3)
		label = "Chat:Console";
	AsciiString name("APT:InGameChatReceivers");
	g_bfmeAptWindowManager->bfmeSetText(name, TheGameText->fetch(label, 0), false);
}

// Retail inlines AsciiString::getCharAt(0) and UnicodeString::isEmpty here
// (the shared headers call them out of line); both read the string data
// header {int refCount; unsigned short length; unsigned short capacity;}.
static inline char firstChar(const AsciiString &text)
{
	const char *data = *(const char *const *)&text;
	return data ? data[8] : 0;
}

static inline bool isEmptyText(const UnicodeString &text)
{
	const char *data = *(const char *const *)&text;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

// Retail 0x004E8670, 432 bytes: the chat line's slash commands. A line
// starting with '/' is a command and is not sent; "/tribute <amount>
// <player>" appends message 0x466 (from, to, amount) when the amount is
// positive and the name is a slot's player.
bool AptInGameChat::rva004E8670(UnicodeString text)
{
	AsciiString message;
	message.translate(text);
	if (firstChar(message) != '/')
		return false;
	AsciiString remainder = message.str() + 1;
	AsciiString token;
	remainder.nextToken(&token);
	token.toLower();
	if (token.compare("tribute") == 0)
	{
		UnicodeString unused;
		remainder.nextToken(&token);
		int amount = atoi(token.str());
		if (amount <= 0)
			return true;
		remainder.nextToken(&token);
		int from = ThePlayerList->m_local->m_playerIndex;
		int slotNum = TheGameInfo->getSlotNum(token);
		if (slotNum < 0)
			return true;
		GameSlot *slot = TheGameInfo->getSlot(slotNum);
		if (slot == 0)
			return true;
		Player *to = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(slot->m_playerName));
		if (to == 0)
			return true;
		int toIndex = to->m_playerIndex;
		GameMessage *msg = MessageStreamSubsystem->appendMessage(0x466);
		msg->appendIntegerArgument(from);
		msg->appendIntegerArgument(toIndex);
		msg->appendIntegerArgument(amount);
		return true;
	}
	return false;
}

// Retail 0x004E8820, 792 bytes: the Send command. Takes the entry's text
// and clears the entry; text that is not a command runs on the console
// (receiver type 3) or is sent as the receiver type's chat line to the
// matching players. Either way the screen then closes (+0x27C 2).
// ?AptInGameChat::Send present-unmatched
void AptInGameChat::Send(const char *unused)
{
	if (m_state != 1)
		return;
	UnicodeString text;
	text.set(GadgetTextEntryGetText(m_entry));
	GadgetTextEntrySetText(m_entry, UnicodeString::TheEmptyString);
	text.trim();
	if (!isEmptyText(text) && !rva004E8670(text))
	{
		if (m_chatType == 3)
		{
			m_state = 2;
			AsciiString command(text);
			Rva00060820(command.str());
			return;
		}
		Player *local = ThePlayerList->m_local;
		AsciiString name;
		int playerMask = 0;
		UnicodeString message(L"Unknown");
		for (int i = 0; i < 8; ++i)
		{
			name = TheGameInfo->getSlot(i)->m_playerName;
			Player *player = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(name));
			if (player == 0 || local == 0)
				continue;
			switch (m_chatType)
			{
			case 0:
				if ((player->getRelationship(local->m_defaultTeam) == ALLIES && local->getRelationship(player->m_defaultTeam) == ALLIES) || player == local)
					playerMask |= 1 << i;
				message.format(TheGameText->slot17("APT:TeamChat", 0), text.str());
				break;
			case 1:
				if (!TheGameInfo->getConstSlot(i)->m_0A)
					playerMask |= 1 << i;
				message.format(TheGameText->slot17("APT:GlobalChat", 0), text.str());
				break;
			case 2:
				if (player == local)
					playerMask |= 1 << i;
				message.format(TheGameText->slot17("APT:PrivateChat", 0), text.str());
				break;
			case 3:
				message.format(TheGameText->slot17("APT:ConsoleCommand", 0), text.str());
				break;
			case 4:
				if (!player->isPlayerActive())
					playerMask |= 1 << i;
				message.format(TheGameText->slot17("APT:ObserverChat", 0), text.str());
				break;
			}
		}
		TheLanguageFilter->filterLine(message);
		TheNetwork->sendChat(message, playerMask);
	}
	m_state = 2;
}
